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



### 解法1

`dp[n][m]`表示**用最大为m的数**对n进行划分的个数，那么最终答案就是`dp[n][n]`，初始状态是`dp[i][1] = 1`。

考虑`dp[n][m]`的状态转移方程，由于用最大为`m-1`的数进行划分的方案已经得出（为`dp[n][m - 1]`），所以只用加上用最大为`m`的划分。`dp[n][m] = dp[n][m - 1] + dp[n - m][m]`。

有两个细节需要注意：

1. `n < m`时，`dp[n][m] = dp[n][n]`。所以状态转移方程改为`dp[n][m] = dp[n][m - 1] + dp[n - m][min(m, n - m)]`。

2. `n == m`时，`dp[n][m] = dp[n][n-1] + dp[0][n]`。其实最大用n划分n的划分数只有1，所以把`dp[0][n]`初始化为1就少了，结合第1点，初始化`dp[0][0] = 1`即可。



代码见`./integer_division.cpp`中的`dp_1`

```cpp
//input 
cin >> n;

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
cout << dp[n][n];
```



### 解法2

`dp[n][m]`表示**用m个数**对n进行划分的个数，那么最终答案就是$\sum_{i=1}^{n}$`dp[n][i]`，初始状态是`dp[i][1] = 1`。

考虑`dp[n][m]`的状态转移方程，将划分分成两种来考虑，用1的和不用1的。用1的总划分显然是`dp[n - 1][m - 1]`；不用1的，每个都大于1，就想做把先取m个1分别放到每个划分中，然后对剩下的n-m进行m划分，即`dp[n - m][m]`。那么`dp[n][m] = dp[n - 1][m - 1] + dp[n - m][m]`。（当然分成用2和不用2的也可以，1是处理起来最方便的。



代码见`./integer_division.cpp`中的`dp_2`

```cpp
//input 
cin >> n;

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
```

