#define PRON "chessboard_cover"
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;
typedef long long ll;

const int maxn = 100 + 10;


int n, occ_x, occ_y, Idx;
int res[maxn][maxn];

void solve(int start_i, int start_j, int len, int x, int y) {
	if (len == 2) {
		// place one tile
		for (int i = start_i; i < start_i + len; i ++)
			for (int j = start_j; j < start_j + len; j ++) {
				if (i == x && j == y)
					continue;
				else
					res[i][j] = Idx;
			}

		Idx ++;
		return;
	}

	/*
	 * | 0 | 1 |
	 * | 2 | 3 |
	 */
	int mid_i = start_i + len / 2, mid_j = start_j + len / 2;
	int _x[4] = { mid_i - 1, mid_i - 1, mid_i, mid_i };
	int _y[4] = { mid_j - 1, mid_j, mid_j - 1, mid_j };
	int flag = int(x >= mid_i) * 2 + int(y >= mid_j);

	// place one tile
	for (int i = 0; i < 4; i ++)
		if (i != flag)
			res[_x[i]][_y[i]] = Idx;
		else
			_x[i] = x, _y[i] = y;
	Idx ++;

	// recursive
	for (int i = 0; i < 4; i ++)
		solve(i < 2 ? start_i : mid_i,
			  i % 2 == 0 ? start_j : mid_j,
			  len / 2, _x[i], _y[i]);
}

void init() {
	memset(res, 0, sizeof res);
	Idx = 1;

	res[occ_x][occ_y] = -1;
}


void output() {
	for (int i = 0; i < n; i ++) {
		for (int j = 0; j < n; j ++)
			cout << setw(4) << setfill(' ') << res[i][j] << " ";
		cout << endl;
	}
}


int main() {
	// input
	// cin >> n >> occ_y >> occ_y;
	n = 8, occ_x = 3, occ_y = 5;

	init();
	solve(0, 0, n, occ_x, occ_y);
	output();
}
