#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100;

int n = 0;

struct Node {
	char data;
	int parent;
} node[MAXN];

void build_tree() {
	Node t;
	while (cin >> t.data >> t.parent)
		node[n ++] = t;
}

int get_depth(int root) {
	int ret = 0, cur, cur_depth;
	for (int i = 0; i < n; i ++) {
		cur = i, cur_depth = 0;
		while (cur != -1)
			cur = node[cur].parent, cur_depth ++;

		ret = max(ret, cur_depth);
	}

	return ret;
}

int main() {
	freopen("test_tree_4", "r", stdin);

	build_tree();
	cout << "[depth] " << get_depth(0);
}
