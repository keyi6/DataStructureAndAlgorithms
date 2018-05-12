#include <stack>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

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


void in_order_traverse(Node * root) {   // 中序遍历
	stack< Node * > s;
	Node * p = root;
	while (not s.empty() || p) {
		while (p) { 
			s.push(p);
			p = p -> l;
		} 
		if (not s.empty()) {
			p = s.top(); s.pop();
			cout << p -> data; p = p -> r;
		}
	}
} 


int count_tree(Node  * root) {
	int ret = 0;
	Node * tree_root = root;
	while (tree_root)
		tree_root = tree_root -> r, ret ++;

	return ret;
}


int count_leaf(Node * root) {
	int ret = 0;
	Node * cur = root;
	queue<Node *> q;

	q.push(root);

	while (not q.empty()) {
		cur = q.front(); q.pop();

		if (cur -> r) q.push(cur -> r);
		if (cur -> l) q.push(cur -> l);

		if (cur -> l == NULL) ret ++;
	}

	return ret;
}


int get_depth(Node * root) {
	int ret = 1, cur_d;
	Node * cur = root -> l;
	if (! cur) return ret;

	queue< pair<Node *, int> > q;
	q.push(make_pair(cur, 2));

	while (not q.empty()) {
		cur = q.front().first;
		cur_d = q.front().second;
		q.pop();

		ret = max(ret, cur_d);

		if (cur -> l) q.push(make_pair(cur -> l, cur_d + 1));
		if (cur -> r) q.push(make_pair(cur -> r, cur_d));
	}

	return ret;
}


int main() {
	freopen("test_tree2", "r", stdin);

	Node * root = NULL;
	build_tree(root);

	cout         << "[in order]       ";
	in_order_traverse(root);
	cout << endl << "[leaf]           " << count_leaf(root);
	cout << endl << "[tree]           " << count_tree(root);
	cout << endl << "[1st tree depth] " << get_depth(root) << endl;
}
