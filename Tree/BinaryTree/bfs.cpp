#include <queue>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
	char data;
	Node * l, * r;

	Node(char _data = ' ') { data = _data; l = r = NULL; }
};


Node * bfs(Node * root, char data) {
	queue<Node *> q; q.push(root);
	while (not q.empty()) {
		Node * cur = q.front(); q.pop();
		if (cur -> data == data) return cur;
		if (cur -> l) q.push(cur -> l);
		if (cur -> r) q.push(cur -> r);
	}
	return NULL;
}

int main() {

}
