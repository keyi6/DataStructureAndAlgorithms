#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
class Node {
    public:
        T data;
        Node * next;

        // constructor
        Node(Node * _next = NULL) {
            next = _next;
        }

        // constructor
        Node(T _data) : data(_data) {
            next = NULL;
        }

        // constructor
        Node(T _data, Node * _next) : data(_data) {
            next = _next;
        }
};


template<typename T>
class LinkList {
    protected:
        Node<T> * head;

    public:
        // constructor
        LinkList() {
            head = new Node<T>;
        }

        // insert node in the front
        void insert_in_front(T _data) {
            Node<T> * temp = head -> next;
            head -> next = new Node<T>(_data, temp);
        }

        // insert node in the end
        void insert_in_end(T _data) {
            Node<T> * temp = head;

            while (temp -> next)
                temp = temp -> next;

            temp -> next = new Node<T>(_data);
        }

        // A - B ^ C
        friend void A_substract_B_union_C(LinkList<T> & A, const LinkList<T> & B, const LinkList<T> & C) {
            Node<T> * ha = A.head -> next, * hb = B.head -> next, * hc = C.head -> next, * pre = A.head;

            while (ha && hb && hc) {
                if (hb -> data == hc -> data) {
                    // delete
                    if (ha -> data == hb -> data) {
                        pre -> next = ha -> next;
                        ha = ha -> next;
                        hb = hb -> next, hc = hc -> next;
                    }
                    else if (ha -> data < hb -> data)
                        pre = ha, ha = ha -> next;
                    else
                        hb = hb -> next, hc = hc -> next;
                }
                else if (hb -> data < hc -> data)
                    hb = hb -> next;
                else
                    hc = hc -> next;
            }

        }

        friend ostream & operator << (ostream & out, const LinkList & pn) {
            Node<T> * temp = pn.head -> next;
            while (temp) {
                out << temp -> data;
                temp = temp -> next;

                if (temp)
                    out << " -> ";
            }

            return out;
        }
};


int main() {
    LinkList<int> a, b, c;

    for (int i = 1; i <= 12; i ++)
        a.insert_in_end(i);
    for (int i = 2; i <= 12; i += 2)
        b.insert_in_end(i);
    for (int i = 3; i <= 12; i += 3)
        c.insert_in_end(i);

    // a = {1, 2, 3, ..., 12}
    // b = {2, 4, 6, ..., 12}
    // c = {3, 6, 9, ..., 12}

    A_substract_B_union_C(a, b, c);
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
    cout << "\na - b ^ c = " << a << endl;
}
