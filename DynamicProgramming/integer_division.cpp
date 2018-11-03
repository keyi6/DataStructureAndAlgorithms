#define PRON "integer_division"
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MAXN = 100 + 10;

int n, dp[MAXN][MAXN];


void dp_1(int n) {
	// init
	memset(dp, 0, sizeof dp);
	dp[0][0] = 1;
	for (int i = 0; i <= MAXN; i ++)
		dp[i][1] = 1;

	// dp
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= i; j ++)
			dp[i][j] = dp[i][j - 1] + dp[i - j][min(j, i - j)];

	// output
	cout << dp[n][n] << endl;
}


void dp_2(int n) {
	// init
	memset(dp, 0, sizeof dp);
	for (int i = 0; i <= MAXN; i ++)
		dp[i][1] = 1;

	// dp
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= i; j ++)
			dp[i][j] = dp[i - 1][j - 1] + dp[i - j][j]; 

	// output
	int res = 0;
	for (int i = 1; i <= n; i ++)
		res += dp[n][i];
	cout << res << endl;
}


int main() {
	//input
	cin >> n;

	dp_1(n);
	dp_2(n);
}
