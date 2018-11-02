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


int main() {
	//input 
	cin >> n;

	// init
	memset(dp, 0, sizeof dp);
	dp[0][0] = 1;
	for (int i = 0; i <= n; i ++)
		dp[i][1] = 1;

	// dp
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= i; j ++)
			dp[i][j] = dp[i][j - 1] + dp[i - j][min(j, i - j)];

	// output
	cout << dp[n][n];
}
