#define PRON "matrix_chain"
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MAXN = 100 + 10;

int n, s[MAXN], dp[MAXN][MAXN], rec[MAXN][MAXN];


int main() {
	// input
	n = 3;
	s[0] = 10; s[1] = 11; s[2] = 12; s[3] = 13;
	
	// init
	memset(dp, 0x3f, sizeof dp);
	for (int i = 0; i < MAXN; i ++)
		dp[i][i] = 0;

	// dp
	for (int j_start = 2; j_start <= n; j_start ++)
		for (int i = 1; i <= n - j_start + 1; i ++) {
			int j = i + j_start - 1;

			for (int k = i + 1, t; k < j; k ++) {
				t = dp[i][k] + dp[k + 1][j] + s[i] * s[j] * s[k];

				if (t < dp[i][j]) dp[i][j] = t, s[i][j] = k;
			}
		}

	cout << dp[1][n] << endl;
}
