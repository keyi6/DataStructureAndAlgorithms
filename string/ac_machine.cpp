#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxk = 26 + 2;
const int maxn = 10000 + 2;
const int maxl = 1000000 + 2;

struct Node {
	int count; Node * next[maxk], * fail;
	Node() { count = 0, fail = NULL; for (int i = 0; i < 26; i ++) next[i] = NULL; }
};

void insert_word(Node * root, char * s){
	Node * p = root; int i = 0, temp;
	while (s[i]) {
		temp = s[i] - 'a';
		if (p -> next[temp] == NULL) p -> next[temp] = new Node;
		p = p -> next[temp], i ++;
	}
	p -> count ++;
}

queue< Node * > q;
void bfs(Node * root) {
	Node * temp, * p;
	q.push(root);
	while (not q.empty()) {
		temp = q.front(); q.pop(); p = NULL;
		for (int i = 0; i < 26; i ++)
			if (temp -> next[i]) {
				if (temp == root) temp -> next[i] -> fail = root;
				else {
					p = temp -> fail;
					while (p) {
						if (p -> next[i]) { temp -> next[i] -> fail = p -> next[i]; break; }
						p = p -> fail;
					}
					if (p == NULL) temp -> next[i] -> fail = root;
				}
				q.push(temp -> next[i]);
			}
	}
}

int query(Node * root, char * str) {
	int ret = 0, i = 0, temp; Node * p = root, * t;
	while (str[i]) {
		temp = str[i] - 'a';
		while (p -> next[temp] == NULL && p != root) p = p -> fail;
		p = p -> next[temp];
		if (p == NULL) p = root;
		t = p;
		while (t != root && t -> count != -1) { ret += t -> count; t -> count = -1; t = t -> fail; }
		i ++;
	}

	return ret;
}

int n;
char word[maxk << 1], str[maxl];

int main() {
	Node * root = new Node;
	scanf("%d", &n);
	for (int i = 0; i < n; i ++){ scanf("%s", word); insert_word(root, word); }
	scanf("%s", str); bfs(root);
	printf("%d\n", query(root, str));
/* 3
cj cjha cjhahaha
cjhaha
----------------
4 */
}
