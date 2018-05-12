#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

struct Node {
    char data;
    Node * l, * r;

    Node(char _data = ' ') { data = _data; l = r = NULL; }
};

void build_tree(Node * & root) {
    char ch;
    cin >> ch;

    if (ch == '#') return;
    root = new Node(ch);

    build_tree(root -> l);
    build_tree(root -> r);
}


void pre_order_traverse(Node * root) {  // 先序遍历
	stack< Node * > s;
	Node * p = root;

	while (not s.empty() || p) {
		while (p) {
			cout << p -> data;
			s.push(p);
			p = p -> l;
		}

		if (not s.empty()) {
			p = s.top();
			s.pop();
			p = p -> r;
		}
	}
}


void in_order_traverse(Node * root) {   // 中序遍历
	stack< Node * > s;
	Node * p = root;

	while (not s.empty() || p) {
		while (p) {
			s.push(p);
			p = p -> l;
		}

		if (not s.empty()) {
			p = s.top();
			s.pop();
			cout << p -> data;
			p = p -> r;
		}
	}
}

void post_order_traverse(Node * root) { // 后续遍历
	stack< Node * > s;
	Node * p = NULL, * pre = NULL;

	s.push(root);
	while (not s.empty()) {
		p = s.top();
		if ((p -> l == NULL && p -> r == NULL) || (p -> l == pre || p -> r == pre)) {
			s.pop(), pre = p;
			cout << p -> data;
		}
		else {
			if (p -> r) s.push(p -> r);
			if (p -> l) s.push(p -> l);
		}
	}
}


int main() {
	freopen("test_tree_3", "r", stdin);
    Node * root = NULL;
    build_tree(root);

	cout << "[pre order]  ";
	pre_order_traverse(root);
	cout << endl << "[in order]   ";
	in_order_traverse(root);
	cout << endl << "[post order] ";
	post_order_traverse(root);
	cout << endl;
}
