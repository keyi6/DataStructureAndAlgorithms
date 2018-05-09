#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100;

int vex_num;
bool g[MAXN][MAXN];

void dfs(int cur, int dest, bool & flag) {
	if (flag) return;
	if (dest == cur || g[cur][dest]) { flag = true; return; } // 找到

	for (int i = 0; i < vex_num; i ++)
		if (i != cur && g[cur][i])                            // 如果有边
			dfs(cur, dest, flag);
}

bool is_path(int f, int to) {
	bool flag = false;
	dfs(f, to, flag);
	return flag;
}

int main() {
}
