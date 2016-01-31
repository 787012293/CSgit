#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

const int MAXN = 51;

int n, m, t;
string s;

int dp[MAXN][MAXN][2];
int r[MAXN * MAXN], f[MAXN * MAXN];
int c[MAXN];

int ans;

int main()
{
	while (cin >> n >> m >> t) {
		for (int k = 0; k < n; k++) {
			cin >> s;
			memset(dp, 0, sizeof(dp));
			memset(r, 0, sizeof(r));
			for (int j = 0; j < m; j++) {
				if (s[j] == '0')
					c[j + 1] = 0;
				else
					c[j + 1] = 1;
			}

			// step 1:
			for (int i = 1; i <= m; i++)
				for (int j = 1; j <= m; j++) {
					int w = c[i];
					dp[i][j][w] = max(dp[i - 1][j - 1][!w], dp[i - 1][j][w]) + 1;
					dp[i][j][!w] = max(dp[i - 1][j][!w], dp[i - 1][j - 1][w]);
					r[j] = max(r[j], dp[i][j][w]);
					r[j] = max(r[j], dp[i][j][!w]);
				}

			// step 2:
			for (int i = t; i > 0; i--)
				for (int j = 1; j <= m; j++)
					if (r[j] > 0 && i >= j) {
						f[i] = max(f[i], f[i - j] + r[j]);
						ans = max(ans, f[i]);
					}
		}
		cout << ans << endl;
	}
	return 0;
}
/*
windy有 N 条木板需要被粉刷。 每条木板被分为 M 个格子。 每个格子要被刷成红色或蓝色。 windy每次粉刷，只能选择一条木板上一段连续的格子，然后涂上一种颜色。 每个格子最多只能被粉刷一次。 如果windy只能粉刷 T 次，他最多能正确粉刷多少格子？ 一个格子如果未被粉刷或者被粉刷错颜色，就算错误粉刷。
*/