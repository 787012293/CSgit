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
windy�� N ��ľ����Ҫ����ˢ�� ÿ��ľ�屻��Ϊ M �����ӡ� ÿ������Ҫ��ˢ�ɺ�ɫ����ɫ�� windyÿ�η�ˢ��ֻ��ѡ��һ��ľ����һ�������ĸ��ӣ�Ȼ��Ϳ��һ����ɫ�� ÿ���������ֻ�ܱ���ˢһ�Ρ� ���windyֻ�ܷ�ˢ T �Σ����������ȷ��ˢ���ٸ��ӣ� һ���������δ����ˢ���߱���ˢ����ɫ����������ˢ��
*/