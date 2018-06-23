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

bool is_complete_binary_tree(Node * root) {
	bool flag = false;
	queue<Node *> q;
	q.push(root);
	while (not q.empty()) {
		Node * cur = q.front();
		q.pop();

		if (cur -> r && ! cur -> l) return false;
		if (! flag && cur -> r == NULL) flag = true;
		else if (flag && (cur -> l == NULL || cur -> r == NULL)) return false;

		if (cur -> l) q.push(cur -> l);
		if (cur -> r) q.push(cur -> r);
	}

	return true;
}


int main() {
	freopen("test_tree_1", "r", stdin);
	Node * root = NULL;
	build_tree(root);
	cout << (is_complete_binary_tree(root) ? "Yes" : "No") << endl;
	root = NULL;
	build_tree(root);
	cout << (is_complete_binary_tree(root) ? "Yes" : "No") << endl;
}
