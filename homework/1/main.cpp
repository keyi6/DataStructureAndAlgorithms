#include <map>
#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;


// -------------------- LinkList.h --------------------

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

        // reverse the linklist
        void reverse() {
            Node<T> * temp = head -> next, * pre = NULL, * backup = NULL;

            // there is only one node
            if (temp -> next == NULL)
                return;

            while (temp -> next) {
                backup = temp -> next;
                temp -> next = pre;
                pre = temp;

                head -> next = temp = backup;
            }

            head -> next -> next = pre;
        }
};


// -------------------- Polynomial.h --------------------

template<typename T>
class PolynomialTerm {
    public:
        int exp;
        T coef;

        // constructor
        PolynomialTerm(int _exp = 0, T _coef = 0) {
            exp = _exp, coef = _coef;
        }

        // output stream
        friend ostream & operator << (ostream & out, const PolynomialTerm & pn) {
            if (pn.coef != 0)
                out << pn.coef << "*x^" << pn.exp;
            return out;
        }
};


template<typename T>
class Polynomial : public LinkList< PolynomialTerm<T> > {
    private:
        // quick pow, O(log n)
        static T quick_pow(T base, int exp) {
            if (exp < 0)
                return pow(base, exp);

            T ret = 1;
            while (exp) {
                if (exp & 1)
                    ret *= base;
                exp >>= 1, base *= base;
            }

            return ret;
        }

    public:
        // constructor
        Polynomial() : LinkList< PolynomialTerm<T> >() { }

        // calculate value
        T calc(T x) {
            Node< PolynomialTerm<T> > * temp = this -> head -> next;

            // if the polynomial is empty
            if (temp == NULL)
                return 0;

            int cur_exp = 0;
            T base = 1, ret = 0;
            while (temp) {
                base *= quick_pow(x, temp -> data.exp - cur_exp);
                cur_exp = temp -> data.exp;

                if (temp -> data.coef != 0)
                    ret += base * temp -> data.coef;

                temp = temp -> next;
            }

            return ret;
        }

        // a + b
        friend Polynomial<T> operator + (const Polynomial<T> & a, const Polynomial<T> & b) {
            Polynomial<T> ret;
            Node< PolynomialTerm<T> > * ha = a.head -> next, * hb = b.head -> next;

            while (ha || hb) {
                if (ha && hb && ha -> data.exp == hb -> data.exp) {
                    ret.insert_in_front(PolynomialTerm<T>(ha -> data.exp, ha -> data.coef + hb -> data.coef));
                    ha = ha -> next, hb = hb -> next;
                }
                else if ((!ha && hb) || (ha && hb && ha -> data.exp > hb -> data.exp)) {
                    ret.insert_in_front(PolynomialTerm<T>(hb -> data.exp, hb -> data.coef));
                    hb = hb -> next;
                }
                else {
                    ret.insert_in_front(PolynomialTerm<T>(ha -> data.exp, ha -> data.coef));
                    ha = ha -> next;
                }
            }

            ret.reverse();
            return ret;
        }

        // output
        friend ostream & operator << (ostream & out, const Polynomial<T> & pn) {
            Node< PolynomialTerm<T> > * temp = pn.head -> next;
            while (temp) {
                out << temp -> data;
                temp = temp -> next;

                if (temp)
                    out << " + ";
            }

            return out;
        }

        // input
        friend istream & operator >> (istream & in, Polynomial<T> & pn) {
            T _coef;
            int n, _exp;
            vector< pair<int, T> > p;

            cout << "Please input the number of terms:\n";
            in >> n;

            for (int i = 0; i < n; i ++) {
                cout << endl << "[Input polynomial] the coefficient of No." << i + 1 << " term:\n";
                in >> _coef;
                cout << "[Input polynomial] the exponent of No." << i + 1 << " term:\n";
                in >> _exp;

                p.push_back(make_pair(_exp, _coef));
            }

            sort(p.begin(), p.end());

            for (pair<int, T> i: p)
                pn.insert_in_front(PolynomialTerm<T>(i.first, i.second));

            pn.reverse();

            return in;
        }
};


// -------------------- Menu.cpp --------------------

template<typename T>
class Menu {
    private:
        int opt;
        map< string, Polynomial<T> > mp;

    public:
        // display menu
        void display() {
            static int max_opt = 6;
            static string menu[] = {
                " Create a new polynomial         " ,
                " Output a polynomial             " ,
                " Reverse and output              " ,
                " Input x and calculate the value " ,
                " Add 2 polynomials               " ,
                " Quit                            "
            };
            cout << "\n\n\n\n--------------------MENU--------------------\n";
            for (int i = 0; i < max_opt; i ++)
                cout << "|   " << "[" << i + 1 << "]  " << menu[i] << " |\n";
            cout << "--------------------------------------------\n\n[Input operation] ";
        }

        void main_loop() {
            string s;
            while (true) {
                display();
                cin >> opt;

                switch (opt) {
                    // create a new polynomial
                    case 1: {
                        cout << "\n\n[Input polynomial] name of the new polynomial\n";
                        cin >> s >> mp[s];

                        cout << "[Input polynomial] " << s << " = " << mp[s];
                        break;
                    }
                    // output a polynomial
                    case 2: {
                        cout << "\n\n[Output polynomial] name of the polynomial\n";
                        cin >> s;
                        if (mp.count(s) < 0) {
                            cout << "[Output polynomial] there is no polynomial named " << s << endl;
                            break;
                        }
                        cout << s << " = " << mp[s];
                        break;
                    }
                    // reverse and output
                    case 3: {
                        cout << "\n\n[Reverse polynomial] name of the polynomial\n";
                        cin >> s;
                        if (mp.count(s) < 0) {
                            cout << "[Reverse polynomial] there is no polynomial named " << s << endl;
                            break;
                        }
                        mp[s].reverse();
                        cout << "[Reverse polynomial] " << s << " = " << mp[s];
                        break;
                    }
                    // Input x and calculate the value
                    case 4: {
                        cout << "\n\n[Calulate value] name of the polynomial\n";
                        cin >> s;
                        if (mp.count(s) < 0) {
                            cout << "[Calulate value] there is no polynomial named " << s << endl;
                            break;
                        }
                        
                        cout << "[Calulate value] input x\n";
                        T x;
                        cin >> x;

                        cout << "\n" << s << "(" << x << ") = " << mp[s];
                        cout << " = " << mp[s].calc(x);
                        break;
                    }
                    // add 2 polynomial
                    case 5: {
                        string sa, sb;
                        cout << "\n\n[Add polynomial] name of the first polynomial\n";
                        cin >> sa;
                        if (mp.count(sa) < 0) {
                            cout << "[Add polynomial] there is no polynomial named " << sa << endl;
                            break;
                        }
                        cout << sa << " = " << mp[sa] << endl;

                        cout << "\n\n[Add polynomial] name of the second polynomial\n";
                        cin >> sb;
                        if (mp.count(sb) < 0) {
                            cout << "[Add polynomial] there is no polynomial named " << sb << endl;
                            break;
                        }
                        cout << sb << " = " << mp[sb] << endl;
                        
                        Polynomial<T> c;
                        c = mp[sa] + mp[sb];
                        cout << endl << sa << " + " << sb << " = " << c;
                        break;
                    }
                    // quit
                    case 6:
                        exit(0);
                    default:
                        cout << "[Input operation] invalid operation\n";
                }
            }
        }
};


// -------------------- main.cpp --------------------

int main() {
    Menu<int> menu;
    menu.main_loop();
}
