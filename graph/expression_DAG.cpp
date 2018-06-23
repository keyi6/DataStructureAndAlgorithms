#define PRON "expression_DAG"
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100 + 10;
const int MAXM = 10000;

struct Edge {
	int to;
	Edge * next;
} * head[MAXN], e[MAXM];

int ne = 0;
void add_edge(int f, int to) {
	e[ne].to = to;
	e[ne].next = head[f];
	head[f] = e + ne ++;
}

struct Node {
	char ch;
	int num;
} node[MAXN];

bool is_symbol(char ch) {				   // 判断是不是符号
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')';
}

void expression_DAG_to_RPN(int cur) {
	for (Edge * p = head[cur]; p; p = p -> next) {
		Node to = node[p -> to];
		if (is_symbol(to.ch))			   // 如果是符号
			expression_DAG_to_RPN(to.num);
		else							   // 如果是字母/数字
			cout << to.ch;
	}

	cout << node[cur].ch;
}

int main() {
	char s[] = "+*+-abcd";
	for (int i = 0; i < 8; i ++)
		node[i].num = i, node[i].ch = s[i];
	int f[]  = {0, 0, 1, 1, 2, 2, 3, 3};
	int to[] = {1, 4, 2, 3, 4, 5, 6, 7};
	for (int i = 0; i < 8; i ++)
		add_edge(f[i], to[i]);

	expression_DAG_to_RPN(0);
}
