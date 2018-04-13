#include <set>
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
    int * col_min, row_min, * pos;
    col_min = new int[A.m];
    pos = new int[A.n];

    for (int j = 0; j < A.m; j ++) {                      // init
        col_min[j] = inf;
        for (int i = 0; i < A.n; i ++)
            col_min[j] = min(col_min[j], A.a[i][j]);
    }

    for (int i = 0, cnt; i < A.n; i ++) {
        row_min = inf, cnt = 0;
        for (int j = 0; j < A.m; j ++) {
            if (row_min > A.a[i][j])
                row_min = A.a[i][j], cnt = 1, pos[0] = j;
            else if (row_min == A.a[i][j])
                pos[cnt ++] = j;
        }

        for (int j = 0; j < cnt; j ++)
            if (A.a[i][pos[j]] == col_min[pos[j]])        // found
                cout << "pos (" << i << ", " << pos[j] << ") is a saddle point" << endl;
    }
}

int main() {
    Mat A(2, 3);
    A.a[0][0] = 1;
    A.a[0][1] = 2;
    A.a[0][2] = 3;
    A.a[1][0] = 4;
    A.a[1][1] = 5;
    A.a[1][2] = 2;

    find_saddle_point(A);
}
