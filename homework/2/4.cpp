#include <iostream>
#include <algorithm>
using namespace std;

const int inf = 0x3f3f3f3f;

struct Mat {
	int n, m, ** a;

	Mat (int _n, int _m) {
		n = _n, m = _m;
		a = new int* [n];
		for (int i = 0; i < n; i ++)
			a[i] = new int[m];
	}
};

void find_saddle_point(Mat A) {
	int * col_min, * row_min;
	col_min = new int[A.m];
	row_min = new int[A.n];

	for (int i = 0; i < n; i ++) {
		row_min[i] = inf;
		for (int j = 0; j < m; j ++)
			row_min[i] = min(row_min[i], A.a[i][j]);
	}

	for (int j = 0; j < m; j ++) {
		col_min[j] = inf;
		for (int i = 0; i < n; i ++)
			col_min[j] = min(col_min[j], A.a[i][j]);
	}

	for (int i = 0; i < min(n, m); i ++)
}

int main() {
	Mat A(3, 3);

}
