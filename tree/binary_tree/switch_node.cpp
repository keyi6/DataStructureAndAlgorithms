#include <queue>
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
	Node(const Node & _) { data = _.data, l = _.l, r = _.r; }
};


void build_tree(Node * & root) {
	char ch;
	cin >> ch;

	if (ch == '#') return;
	root = new Node(ch);

	build_tree(root -> l);
	build_tree(root -> r);
}


void bfs(Node * root) {
	queue<Node *> q;
	q.push(root);
	while (not q.empty()) {
		Node * cur = q.front();
		q.pop();

		cout << cur -> data;

		if (cur -> l) q.push(cur -> l);
		if (cur -> r) q.push(cur -> r);
	}
}


void dfs_switch(Node * & root) {
	if (root -> l && root -> r) swap(*(root -> l), *(root -> r));
	else if (root -> l) { root -> r = new Node(*(root -> l)); root -> l = NULL; }
	else if (root -> r) { root -> l = new Node(*(root -> r)); root -> r = NULL; }

	if (root -> l) dfs_switch(root -> l);
	if (root -> r) dfs_switch(root -> r);
}


int main() {
	Node * root = NULL;
	build_tree(root);
	bfs(root);
	cout << endl;

	dfs_switch(root);

	bfs(root);
}
