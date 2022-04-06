#define PRON "loop_table"
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MAXN = 100 + 10;

int n, res[MAXN][MAXN];


void schedule(int n) {
	// init
	memset(res, 0, sizeof res);
	for (int i = 1; i <= n; i ++)
		res[1][i] = res[i][1] = i;

	for (int width = 2, gap = 1; width <= n; width <<= 1, gap <<= 1)
		for (int i = 1; i <= gap; i ++)
			for (int t = 0; t < n / width; t ++)
				for (int j = t * width + 1; j <= t * width + gap; j ++)
					res[i + gap][j + gap] = res[i][j],
					res[i + gap][j]			  = res[i][j + gap];
}


void output() {
	cout << "Result:";
	for (int i = 1; i <= n; i ++) {
		cout << endl << res[i][1] << "  |  ";
		for (int j = 2; j <= n; j ++)
			cout << setw(4) << setfill(' ') << res[i][j] << " ";
	}
}


int main() {
	// input
	// cin >> n;
	n = 8;

	schedule(n);
	output();
}
