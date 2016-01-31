#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

const int INF = 0x3f3f3f3f;

const int MAXN = 302;
int v, p;
int a[MAXN];
int dp[MAXN][MAXN], cost[MAXN][MAXN];

// dp[i][n] = the minimum cost to build n post offices in villages 0 to i
// cost[i][j] = the minimum cost if there is only 1 post office among villages i to j
// dp[i][n] = min(dp[k][n - 1] + cost[k + 1][i]) for k = 0, 1, ... , i - 1
//
// cost[i][j] is the cost among villages i to j when the post office is built at (i + j) / 2
// cost[i][j] = cost[i][j - 1] + a[j] - a[(i + j) / 2]
// all post offices are presumed to be built at village (i + j) / 2 + 1 when i + j is odd

int main()
{
	while (cin >> v >> p) {
		for (int i = 0; i < v; i++)
			cin >> a[i];

		for (int i = 0; i < v; i++) {
			cost[i][i] = 0;
			for (int j = i + 1; j < v; j++)
				cost[i][j] = cost[i][j - 1] + a[j] - a[(i + j) / 2];
		}

		/*for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
		cout << setiosflags(ios::right) << setw(3) << cost[i][j] << ' ';
		}
		cout << endl;
		}*/

		for (int n = 1; n <= p; n++) {
			for (int i = 0; i < v; i++) {
				if (n == 1)
					dp[i][n] = cost[0][i];
				else {
					int min = INF;
					for (int k = 0; k < i; k++)
						if (dp[k][n - 1] + cost[k + 1][i] < min)
							min = dp[k][n - 1] + cost[k + 1][i];
					dp[i][n] = min;
				}
			}
		}

		/*for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
		cout << setiosflags(ios::right) << setw(3) << dp[i][j] << ' ';
		}
		cout << endl;
		}*/

		cout << dp[v - 1][p] << endl;
	}
	return 0;
}
/*

There is a straight highway with villages alongside the highway. The highway is represented as an integer axis, and the position of each village is identified with a single integer coordinate. There are no two villages in the same position. The distance between two positions is the absolute value of the difference of their integer coordinates.

Post offices will be built in some, but not necessarily all of the villages. A village and the post office in it have the same position. For building the post offices, their positions should be chosen so that the total sum of all distances between each village and its nearest post office is minimum.

You are to write a program which, given the positions of the villages and the number of post offices, computes the least possible sum of all distances between each village and its nearest post office.
*/