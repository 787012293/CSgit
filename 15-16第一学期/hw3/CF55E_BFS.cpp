#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <set>

using namespace std;

const int MAXN = 3005;

struct Node
{
	int x, y;
} dq, dq2, fa[MAXN][MAXN];

map<long long, int> mp;
queue<Node> q;
long long now;
int n, m, k, x, y, z;
int dist[MAXN][MAXN];
bool vis[MAXN][MAXN];
int num, a[50000];
int nxt[50000];
int b[5000];
void add(int x, int y)
{
	++num; a[num] = y; nxt[num] = b[x]; b[x] = num;
}

int main()

{
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; ++i)
	{
		scanf("%d%d", &x, &y);
		add(x, y);
		add(y, x);
	}
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= n; ++j) vis[i][j] = false;
	for (int i = 1; i <= k; ++i)
	{
		scanf("%d%d%d", &x, &y, &z);
		now = x;
		now = now * 3000;
		now = now + y;
		now = now * 3000;
		now = now + z;
		mp[now] = 1;
	}
	vis[0][1] = true; dist[0][1] = 0;
	dq.x = 0; dq.y = 1;
	while (!q.empty()) q.pop();
	q.push(dq);
	bool flag = false;
	while (!q.empty())
	{
		dq = q.front(); q.pop();
		if (dq.y == n)
		{
			flag = true;
			break;
		}
		for (int i = b[dq.y]; i != 0; i = nxt[i])
		{
			y = a[i];
			long long now;
			now = dq.x;
			now = now * 3000;
			now = now + dq.y;
			now = now * 3000;
			now = now + y;
			if (mp.count(now) != 0) continue;
			if (vis[dq.y][y]) continue;
			vis[dq.y][y] = true;
			fa[dq.y][y] = dq;
			dq2.x = dq.y; dq2.y = y;
			dist[dq2.x][dq2.y] = dist[dq.x][dq.y] + 1;
			q.push(dq2);
		}
	}
	if (!flag)
	{
		printf("-1\n");
		return 0;
	}
	int ans[MAXN];
	printf("%d\n", dist[dq.x][dq.y]);
	int len = dist[dq.x][dq.y] + 1;
	int now = dist[dq.x][dq.y] + 1;
	while (!(dq.x == 0 && dq.y == 1))
	{
		ans[now] = dq.y;
		dq = fa[dq.x][dq.y];
		now--;
	}
	ans[1] = 1;
	for (int i = 1; i <= len; ++i) printf("%d ", ans[i]);

	return 0;

}
/*
In Ancient Berland there were n cities and m two-way roads of equal length. The cities are numbered with integers from 1 to n inclusively. According to an ancient superstition, if a traveller visits three cities ai, bi, ci in row, without visiting other cities between them, a great disaster awaits him. Overall there are k such city triplets. Each triplet is ordered, which means that, for example, you are allowed to visit the cities in the following order: ai, ci, bi. Vasya wants to get from the city 1 to the city n and not fulfil the superstition. Find out which minimal number of roads he should take. Also you are required to find one of his possible path routes.
The first line contains three integers n, m, k (2 ≤ n ≤ 3000, 1 ≤ m ≤ 20000, 0 ≤ k ≤ 105) which are the number of cities, the number of roads and the number of the forbidden triplets correspondingly.

Then follow m lines each containing two integers xi, yi (1 ≤ xi, yi ≤ n) which are the road descriptions. The road is described by the numbers of the cities it joins. No road joins a city with itself, there cannot be more than one road between a pair of cities.

Then follow k lines each containing three integers ai, bi, ci (1 ≤ ai, bi, ci ≤ n) which are the forbidden triplets. Each ordered triplet is listed mo more than one time. All three cities in each triplet are distinct.

City n can be unreachable from city 1 by roads.
If there are no path from 1 to n print -1. Otherwise on the first line print the number of roads d along the shortest path from the city 1 to the city n. On the second line print d + 1 numbers — any of the possible shortest paths for Vasya. The path should start in the city 1 and end in the city n.
*/