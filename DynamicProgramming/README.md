# 动态规划





## 整数划分问题

> 对于整数n，求n的划分数。

sample input:

> 4

sample output:

> 5

解释

> 4 = 1 + 1 + 1 + 1
>
>    = 1 + 1 +  2
>
>    = 2 + 2
>
>    = 3 + 1
>
>    = 4



`dp[n][m]`表示用最大为m的数对n进行划分的个数，那么最终答案就是`dp[n][n]`，初始状态是`dp[i][1] = 1`。

考虑`dp[n][m]`的状态转移方程，由于用最大为`m-1`的数进行划分的方案已经得出（为`dp[n][m - 1]`），所以只用加上用最大为`m`的划分。`dp[n][m] = dp[n][m - 1] + dp[n - m][m]`。

有两个细节需要注意：

1. `n < m`时，`dp[n][m] = dp[n][n]`。所以状态转移方程改为`dp[n][m] = dp[n][m - 1] + dp[n - m][min(m, n - m)]`。

2. `n == m`时，`dp[n][m] = dp[n][n-1] + dp[0][n]`。其实最大用n划分n的划分数只有1，所以把`dp[0][n]`初始化为1就少了，结合第1点，初始化`dp[0][0] = 1`即可。



代码见`./integer_division.cpp`

```cpp
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
```

