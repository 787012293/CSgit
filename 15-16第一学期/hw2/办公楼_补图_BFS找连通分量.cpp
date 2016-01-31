#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

enum { NUM, NEXT };
#define NIL -1

const int MAXN = 100001;

vector<int> a[MAXN];
int vis[MAXN];
int node[MAXN][2]; // head is stored in node[0][NEXT];
int result[MAXN];
int rcnt;
queue<int> q;
bool flag[MAXN];

void init(int n)
{
	for (int i = 1; i <= n; i++)
		a[i].clear();
	memset(vis, 0, sizeof(int) * (n + 1));
	for (int i = 0; i <= n; i++) {
		node[i][NUM] = i;
		node[i][NEXT] = i + 1;
	}
	node[n][NEXT] = NIL;
	rcnt = 0;
	while (!q.empty())
		q.pop();
}

int BFS(int u)
{
	int cnt = 0;
	q.push(u);
	//cout << "qpush" << u << endl;
	while (!q.empty()) {
		int r = q.front();
		q.pop();
		cnt++;

		memset(flag, 0, sizeof(flag));
		for (int i = 0; i < (int)a[r].size(); i++)
			flag[a[r][i]] = true;
		flag[u] = true;

		int i = 0, j = node[0][NEXT];
		while (j != NIL) {
			if (!flag[node[j][NUM]]) {
				q.push(node[j][NUM]);
				node[i][NEXT] = node[j][NEXT];
				j = node[j][NEXT];
			}
			else
				i = node[i][NEXT], j = node[j][NEXT];
		}
	}
	return cnt;
}

int main()
{
	int n, m;
	while (cin >> n >> m) {
		init(n);
		for (int i = 0; i < m; i++) {
			int p, q;
			scanf("%d%d", &p, &q);
			a[p].push_back(q);
			a[q].push_back(p);
		}
		while (node[0][NEXT] != NIL) {
			int p = node[node[0][NEXT]][NUM];
			node[0][NEXT] = node[node[0][NEXT]][NEXT];
			result[rcnt] = BFS(p);
			rcnt++;
		}
		sort(result, result + rcnt);
		int i;
		printf("%d\n", rcnt);
		for (i = 0; i < rcnt; i++)
			printf("%d ", result[i]);
		printf("\n");
	}
	return 0;
}