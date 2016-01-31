#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 102;
const int MAXM = 100000;
const int pwr[11] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };

int n, m;
int a[MAXN], c[MAXN]; // a is the value and c is the number of coins

int v[MAXN * 10];
int vcnt;

int dp[MAXM];

// multi-knapsack problem
// turn into 0-1 knapsack problem using binomial optimization
// dp[i][j] is the maximum possible value with the first i objects under weight constraint j
// the value and weight are the same in this problem
// dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - v[i]] + v[i]);
// if dp[vcnt][m] == m then cnt++

int main()
{
	while (cin >> n >> m) {
		if (n == 0 && m == 0) break;

		int cnt = 0;

		for (int i = 0; i < n; i++)
			cin >> a[i];
		for (int i = 0; i < n; i++)
			cin >> c[i];

		vcnt = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; c[i] > pwr[j]; j++) {
				v[vcnt] = pwr[j] * a[i];
				c[i] -= pwr[j];
				vcnt++;
			}
			v[vcnt] = c[i] * a[i];
			vcnt++;
		}

		/*for (int i = 0; i < vcnt; i++)
		cout << v[i] << ' ';
		cout << endl;*/

		int p;
		for (p = 0; v[0] > p && p <= m; p++)
			dp[p] = 0;
		for (; p <= m; p++)
			dp[p] = v[0];

		/*for (int i = 0; i <= m; i++)
		cout << dp[i] << ' ';
		cout << endl;

		cout << vcnt << endl;*/
		for (int i = 1; i < vcnt; i++) {
			for (int j = m; j >= v[i]; j--)
				dp[j] = max(dp[j], dp[j - v[i]] + v[i]);

			/*for (int i = 0; i <= m; i++)
			cout << dp[i] << ' ';
			cout << endl;*/
		}

		for (int i = 1; i <= m; i++)
			if (dp[i] == i)
				cnt++;

		cout << cnt << endl;
	}
	return 0;
}
/*
5 15
3 5 7 11 13 45 100 6 12 3

Whuacmers use coins.They have coins of value A1,A2,A3...An Silverland dollar. One day Hibix opened purse and found there were some coins. He decided to buy a very nice watch in a nearby shop. He wanted to pay the exact price(without change) and he known the price would not more than m.But he didn't know the exact price of the watch.

You are to write a program which reads n,m,A1,A2,A3...An and C1,C2,C3...Cn corresponding to the number of Tony's coins of value A1,A2,A3...An then calculate how many prices(form 1 to m) Tony can pay use these coins.
*/