#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXM = 105;
const int MAXN = 10005;
const int MAXE = 200000;
const int INF = 0x3f3f3f3f;
const int source = 0, sink = MAXN - 1;

int n, m, k;
int G[MAXM][MAXM];

struct DINIC {
	struct edge {
		int u, v;
		int cap, flow;
		int next;
		edge() {}
		edge(int u, int v, int cap, int flow, int next) {
			this->u = u;
			this->v = v;
			this->cap = cap;
			this->flow = flow;
			this->next = next;
		}
	};

	edge E[MAXE];
	int cnte;
	int head[MAXN];
	int d[MAXN];

	void Dinic_init()
	{
		cnte = 0;
		memset(head, -1, sizeof(head));
	}

	inline void add(int u, int v, int cap)
	{
		E[cnte] = edge(u, v, cap, 0, head[u]);
		head[u] = cnte;
		cnte++;
		E[cnte] = edge(v, u, 0, 0, head[v]);
		head[v] = cnte;
		cnte++;
	}

	bool Dinic_BFS()
	{
		bool vis[MAXN];
		memset(vis, 0, sizeof(vis));
		queue<int> Q;
		Q.push(source);
		d[source] = 0;
		vis[source] = true;
		while (!Q.empty()) {
			int u = Q.front(); Q.pop();
			for (int i = head[u]; i != -1; i = E[i].next) {
				edge &e = E[i];
				if (!vis[e.v] && e.cap > e.flow) {
					vis[e.v] = true;
					d[e.v] = d[u] + 1;
					Q.push(e.v);
				}
			}
		}
		return vis[sink]; // not connected if sink is not visited
	}

	// f is the maximum possible flow from source to u
	// if u == sink, then DFS will return the maximum flow from source to sink
	int Dinic_DFS(int u, int f)
	{
		if (u == sink || f == 0) return f;
		int result = 0;
		for (int i = head[u]; i != -1 && result < f; i = E[i].next) {
			edge &e = E[i];
			int temp = min(f - result, e.cap - e.flow);
			// if v is deeper than u and there exists an augmenting path 
			if (d[u] == d[e.v] - 1 && e.cap > e.flow) {
				temp = Dinic_DFS(e.v, temp);
				e.flow = e.flow + temp;
				E[i ^ 1].flow = E[i ^ 1].flow - temp;
				result = result + temp;
			}
		}
		if (result == 0) d[u] = -2;
		return result;
	}

	int execute()
	{
		int flow = 0;
		while (Dinic_BFS())
			while (true) {
				int val = Dinic_DFS(source, INF);
				if (val == 0) break;
				flow += val;
			}

		return flow;
	}
} dinic;

// calculate vertex number of G[i][j]
inline int calc(int i, int j)
{
	return (m * (i - 1) + j);
}

int main()
{
	while (cin >> n >> m) {
		memset(G, -1, sizeof(G));
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf("%d", &G[i][j]);

		dinic.Dinic_init();

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				// source to wolf, wolf to sheep, wolf to blank
				if (G[i][j] == 1) {
					dinic.add(source, calc(i, j), INF);
					if (G[i][j - 1] == 0 || G[i][j - 1] == 2)
						dinic.add(calc(i, j), calc(i, j - 1), 1);
					if (G[i][j + 1] == 0 || G[i][j + 1] == 2)
						dinic.add(calc(i, j), calc(i, j + 1), 1);
					if (G[i - 1][j] == 0 || G[i - 1][j] == 2)
						dinic.add(calc(i, j), calc(i - 1, j), 1);
					if (G[i + 1][j] == 0 || G[i + 1][j] == 2)
						dinic.add(calc(i, j), calc(i + 1, j), 1);
				}
				// sheep to blank, sheep to sink
				if (G[i][j] == 2) {
					dinic.add(calc(i, j), sink, INF);
					if (G[i][j - 1] == 0)
						dinic.add(calc(i, j - 1), calc(i, j), 1);
					if (G[i][j + 1] == 0)
						dinic.add(calc(i, j + 1), calc(i, j), 1);
					if (G[i - 1][j] == 0)
						dinic.add(calc(i - 1, j), calc(i, j), 1);
					if (G[i + 1][j] == 0)
						dinic.add(calc(i + 1, j), calc(i, j), 1);
				}
				// blank to blank
				if (G[i][j] == 0) {
					if (G[i][j - 1] == 0)
						dinic.add(calc(i, j - 1), calc(i, j), 1);
					if (G[i][j + 1] == 0)
						dinic.add(calc(i, j + 1), calc(i, j), 1);
					if (G[i - 1][j] == 0)
						dinic.add(calc(i - 1, j), calc(i, j), 1);
					if (G[i + 1][j] == 0)
						dinic.add(calc(i + 1, j), calc(i, j), 1);
				}
			}

		cout << dinic.execute() << endl;
	}
	return 0;
}
/*
3 4
1 2 1 1
2 0 1 2
0 1 1 0

3 4
1 2 0 0
0 1 2 1
0 0 0 1

2 4
1 2 0 0
0 1 2 1
*/