#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
struct Node {
	T data;
	int balance_factor;
	Node<T> * l, * r, * parent;

	Node () { l = r = NULL, balance_factor = 0; }
	Node (T _data) : data(_data) { l = r = parent = NULL, balance_factor = 0; }
	Node (T _data, Node<T> * _parent) : data(_data) { l = r = NULL, parent = _parent, balance_factor = 0; }
};


template<typename T>
class AVL {
	private:
		Node<T> * root;

		void left_rotate(Node<T> * & parent) {
			Node<T> * rl = parent -> r -> l;
			Node<T> * r = parent -> r;
			Node<T> * p = parent -> parent;

			// step 1: move rl to parent's right child
			parent -> r = rl;
			if (rl) rl -> parent = parent;

			// step 2: move parent to r's left child
			r -> l = parent;
			parent -> parent = r;

			// step 3: link parent's parent to r
			if (p == NULL) root = r;
			else if (p -> l == parent) p -> l = r;
			else if (p -> r == parent) p -> r = r;
			r -> parent = p;

			parent -> balance_factor = r -> balance_factor = 0;
		}

		void right_rotate(Node<T> * & parent) {
			Node<T> * lr = parent -> l -> r;
			Node<T> * l = parent -> l;
			Node<T> * p = parent -> parent;

			// step 1: move lr to parent's left child
			parent -> l = lr;
			if (lr) lr -> parent = parent;

			// step 2: move parent to l's right child
			l -> r = parent;
			parent -> parent = l;

			// step 3: link parent's parent to l
			if (p == NULL) root = l;
			else if (p -> l == parent) p -> l = l;
			else if (p -> r == parent) p -> r = l;
			l -> parent = p;

			parent -> balance_factor = l -> balance_factor = 0;
		}

		void left_right_rotate(Node<T> * & parent) {
			Node<T> * lr = parent -> l -> r;
			Node<T> * l = parent -> l;
			int lr_bf = lr -> balance_factor;

			left_rotate(parent -> l);
			right_rotate(parent);

			if (lr_bf == 1)
				l -> balance_factor = -1, parent -> balance_factor = 0;
			else if (lr_bf == -1)
				l -> balance_factor = 0, parent -> balance_factor = 1;
			else
				l -> balance_factor = parent -> balance_factor = 0;

			lr -> balance_factor = 0;
		}

		void right_left_rotate(Node<T> * & parent) {
			Node<T> * rl = parent -> r -> l;
			Node<T> * r = parent -> r;
			int rl_bf = rl -> balance_factor;

			right_rotate(parent -> r);
			left_rotate(parent);

			if (rl_bf == -1)
				r -> balance_factor = 1, parent -> balance_factor = 0;
			else if (rl_bf == 1)
				r -> balance_factor = 0, parent -> balance_factor = -1;
			else
				r -> balance_factor = parent -> balance_factor = 0;

			rl -> balance_factor = 0;

		}

		void delete_leaf(Node<T> * & cur) {
			Node<T> * parent = cur -> parent;
			if (parent -> l == cur)
				parent -> l = NULL, parent -> balance_factor ++;
			else
				parent -> r = NULL, parent -> balance_factor --;

			if (! parent -> l && ! parent -> r && parent -> parent)
				parent -> parent -> balance_factor += (parent -> parent -> l == parent ? -1 : 1);

			delete cur;
		}

		void delete_left(Node<T> * & cur) {
		
		}

		void delete_right(Node<T> * & cur) {
		
		}

		void in_order_traverse(Node<T> * cur) {
			if (! cur) return;

			if (cur -> l) in_order_traverse(cur -> l);
			cout << cur -> data << " ";
			if (cur -> r) in_order_traverse(cur -> r);
		}

	public:
		AVL() { root = NULL; }

		Node<T> * find_data(Node<T> * cur, T data) {
			if (! cur || cur -> data == data)
				return cur;
			if (cur -> data > data)
				return find_data(cur -> l, data);
			if (cur -> data < data)
				return find_data(cur -> r, data);

			return NULL;
		}

		bool insert_data(T data) {
			if (! root) {
				root = new Node<T> (data);
				return true;
			}

			// step 1: find place to insert
			Node<T> * cur = root, * parent;
			while (cur) {
				if (data > cur -> data)
					parent = cur, cur = cur -> r;
				else if (data < cur -> data)
					parent = cur, cur = cur -> l;
				else
					return false;
			}

			// step 2: insert data, link parent
			cur = new Node<T> (data, parent);
			(parent -> data > data ? parent -> l : parent -> r) = cur;


			// step 3: update balance factor
			while (parent) {
				parent -> balance_factor += (parent -> l == cur ? -1 : 1);

				if (parent -> balance_factor == 0) return true;

				if (abs(parent -> balance_factor) == 1)
					cur = parent, parent = cur -> parent;
				else if (parent -> balance_factor == 2) {
					if (cur -> balance_factor == 1) left_rotate(parent);
					else right_left_rotate(parent);
					return true;
				}
				else if (parent -> balance_factor == -2) {
					if (cur -> balance_factor == -1) right_rotate(parent);
					else left_right_rotate(parent);
					return true;
				}
			}
			return false;
		}

		void delete_data(T data) {
			Node<T> * cur = find_data(root, data);
			if (! cur) return;

			if (! cur -> l && ! cur -> r) delete_leaf(cur);
			else if (cur -> l && ! cur -> r) delete_left(cur);
			else if (! cur -> l && cur -> r) delete_right(cur);
		}

		void print_sorted() {
			in_order_traverse(root);
			cout << endl;
		}

		void print() { //debug/////////////////////
			queue< pair< Node<T> *, int > > q; q.push(make_pair(root, 0));
			while (not q.empty()) {
				Node<T> * cur = q.front().first; int depth = q.front().second; q.pop();
				cout << cur -> data << "  parent "; if (cur -> parent) cout << cur->parent->data;cout << "   bf = " << cur -> balance_factor <<endl;
				if (cur -> l) q.push(make_pair(cur -> l, depth + 1)); if (cur -> r) q.push(make_pair(cur -> r, depth + 1)); }
			cout << endl; 
		}
};


int main() {
	int arr[] = {4, 6, 23, 54, 29, 10, 0, 1, 42, 3, 9};
	AVL<int> a;

	for (int i = 0; i < 10; i ++)
		a.insert_data(arr[i]);
	a.print_sorted();
	cout << endl;
	a.print();
	cout << endl;
	
	a.delete_data(10);
	a.print();
}
