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

		Node(T _data) : data(_data) {
			next = NULL;
		}

		Node(T _data, Node * _next) : data(_data) {
			next = _next;
		}
};


template<typename T>
class LinkList {
	public:
		Node<T> * head;

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

		// output nodes
		void output(string separator = " -> ") {
			Node<T> * temp = head -> next;
			while (temp) {
				cout << temp -> data;
				temp = temp -> next;

				if (temp)
					cout << separator;
				else
					cout << endl;
			}
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
class PolynomialNode {
	public:
		int exp;
		T coef;

		// constructor
		PolynomialNode(int _exp = 0, T _coef = 0) {
			exp = _exp, coef = _coef;
		}

		// output stream
		friend ostream & operator << (ostream & out, const PolynomialNode & pn) {
			if (pn.coef != 0)
				out << pn.coef << "*x^" << pn.exp;
			return out;
		}
};


template<typename T>
class Polynomial {
	private:
		LinkList< PolynomialNode<T> > l;

		T quick_pow(T base, int exp) {
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
		Polynomial() {}

		// calculate value
		T calc(T x) {
			Node< PolynomialNode<T> > * temp = l.head -> next;

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

			PolynomialNode<T> * ha = a.l.head -> next, * hb = b.l.head -> next;

			while (ha || hb) {
				if (ha && hb && ha -> exp == hb -> exp) {
					ret.l.insert_in_front(PolynomialNode<T>(ha -> exp, ha -> coef + hb -> coef));
					ha = ha -> next, hb = hb -> next;
				}
				else if ((!ha && hb) || (ha && hb && ha -> exp > hb -> exp)) {
					ret.l.insert_in_front(PolynomialNode<T>(hb -> exp, hb -> coef));
					hb = hb -> next;
				}
				else {
					ret.l.insert_in_front(PolynomialNode<T>(ha -> exp, ha -> coef));
					ha = ha -> next;
				}
			}

			ret.l.reverse();
			return ret;
		}


		void input() {
			T _coef;
			int n, _exp;
			vector< pair<int, T> > p;

			cout << "Please input the number of terms:\n";
			cin >> n;

			for (int i = 0; i < n; i ++) {
				cout << endl << "[Input] the coefficient of No." << i + 1 << " term:\n";
				cin >> _coef;
				cout << "[Input] the exponent of No." << i + 1 << " term:\n";
				cin >> _exp;
			
				p.push_back(make_pair(_exp, _coef));
			}

			sort(p.begin(), p.end());

			for (pair<int, T> i: p)
				l.insert_in_front(PolynomialNode<T>(i.first, i.second));
			l.reverse();


			cout << endl << "[Input Finished]";
			l.output(" + ");
		}
};


// -------------------- main.cpp --------------------

int main() {
	Polynomial<int> a;
	a.input();

	int x;
	cin >> x;
	cout << a.calc(x);
}
