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


int get_depth(Node * root) {
	if (! root) return 0;

	Node * cur = NULL;
	int depth = 1, cur_d;
	queue< pair<Node *, int> > q;
	
	q.push(make_pair(root, 1));

    while (not q.empty()) {
        cur = q.front().first; 
		cur_d = q.front().second;
		q.pop();

		depth = max(depth, cur_d);

		if (cur -> l) q.push(make_pair(cur -> l, cur_d + 1));
		if (cur -> r) q.push(make_pair(cur -> r, cur_d + 1));
    }

	return depth;
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
	cout << endl << "depth = " << get_depth(root) << endl;
}
