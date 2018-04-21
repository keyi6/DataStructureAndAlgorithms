#include <queue>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
	char ch;
	double v;
	Node * l, * r;

	Node(char _ch = ' ', double _v = 0, Node * _l = NULL, Node * _r = NULL) {
		ch = _ch, v = _v;
		l = _l, r = _r;
	}
};

struct Cmp {
	bool operator()(Node * a, Node * b) {
		return a -> v > b -> v;
	}
};

void dfs(Node * cur, string s, double & score) {
	if (! cur) return;
	if (cur -> ch != ' ') {
		cout << cur -> ch << " -> " << s << endl;
		score += (double)s.length() * cur -> v;
		return;
	}
	if (cur -> l) dfs(cur -> l, s + "0", score);
	if (cur -> r) dfs(cur -> r, s + "1", score);
}

void Huffman_encode(double * v, char * ch, int n) {
	priority_queue<Node *, vector<Node *>, Cmp> q;
	Node * t1, * t2, * cur = NULL;

	for (int i = 0; i < n; i ++) {
		t1 = new Node(ch[i], v[i]);
		q.push(t1);
	}

	while (not q.empty()) {
		t1 = q.top(); q.pop();
		t2 = q.top(); q.pop();

		cur = new Node(' ', t1 -> v + t2 -> v, t1, t2);
		if (not q.empty()) q.push(cur);
	}

	double score = 0;
	dfs(cur, "", score);
	cout << "score = " << score << endl;
}

int main() {
	char ch[] = "ABCDEFG"; 
	double v[] = {0.17, 0.09, 0.12, 0.06, 0.32, 0.03, 0.21};

	Huffman_encode(v, ch, 7);
}
