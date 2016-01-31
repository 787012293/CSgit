#include <iostream>
#include <stack>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 1000001;
int a[MAXN], pi[MAXN], od[MAXN]; // out-degree
int vis[MAXN];
int ans;

int head[MAXN], cnte;

struct EDGE {
	int u, v, next;
}e[MAXN << 1];

void addedge(int u, int v) {
	e[cnte].u = u, e[cnte].v = v;
	e[cnte].next = head[u];
	head[u] = cnte++;
}

void dfs(int u)
{
	vis[u] = -1;
	if (vis[a[u]] == 0) {
		dfs(a[u]);
	}
	else if (vis[a[u]] == -1) {
		od[u]--;
		a[u] = -1;
	}
	vis[u] = 1;
}

bool DFS(int u)
{
	bool color = true; // the color is true for choosing the agent
	for (int i = head[u]; i != -1; i = e[i].next) {
		color = color & DFS(e[i].v);
	}
	color = !color;
	if (color) ans++;
	return color;
}


int main()
{
	int n;
	while (cin >> n) {
		memset(e, 0, sizeof e);
		memset(head, -1, sizeof head);
		cnte = 0;
		memset(pi, -1, sizeof(int) * (n + 1));
		memset(od, 0, sizeof(int) * (n + 1));
		memset(vis, 0, sizeof(bool) * (n + 1));

		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			od[i]++;
		}

		for (int i = 1; i <= n; i++) {
			if (vis[i] == 0) {
				dfs(i);
			}
		}

		for (int i = 1; i <= n; i++)
			if (a[i] != -1)
				addedge(a[i], i);

		ans = 0;
		for (int i = 1; i <= n; i++)
			if (od[i] == 0) {
				DFS(i);
			}

		printf("%d\n", ans);
	}
	return 0;
}