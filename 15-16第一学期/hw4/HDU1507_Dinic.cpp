#include <iostream>
#include <queue>
using namespace std;

const int MAXM = 105;
const int MAXN = 10005;
const int MAXE = 2000000;
const int INF = 0x3f3f3f3f;
const int source = 0, sink = MAXN - 1;

int n, m, k;
int G[MAXM][MAXM];
int H[MAXN][2];

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

	void print()
	{
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				if (G[i][j] != -1 && (i + j) % 2 == 0)
					for (int k = head[G[i][j]]; k != -1; k = E[k].next)
						if (E[k].flow == 1)
							printf("(%d,%d)--(%d,%d)\n", H[E[k].v][0], H[E[k].v][1], i, j);


	}
} dinic;

int main()
{
	while (cin >> n >> m) {
		if (n == 0 && m == 0) break;
		cin >> k;
		memset(G, 0, sizeof(G));
		for (int i = 0; i < k; i++) {
			int x, y;
			cin >> x >> y;
			G[x][y] = -1;
		}

		dinic.Dinic_init();

		// number the vertices
		int cnt = 1;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				if (G[i][j] != -1) { // if it is not a pond
					G[i][j] = cnt;
					H[cnt][0] = i;
					H[cnt][1] = j;
					cnt++;
				}

		// For u == G[x][y], if (x + y) % 2 == 0, then there is arc from u to the four squares around it.
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				if (G[i][j] != -1 && (i + j) % 2 == 0) {
					// not a pond and not on the edge
					if (G[i - 1][j] != -1 && G[i - 1][j] != 0)
						dinic.add(G[i][j], G[i - 1][j], 1);
					if (G[i + 1][j] != -1 && G[i + 1][j] != 0)
						dinic.add(G[i][j], G[i + 1][j], 1);
					if (G[i][j - 1] != -1 && G[i][j - 1] != 0)
						dinic.add(G[i][j], G[i][j - 1], 1);
					if (G[i][j + 1] != -1 && G[i][j + 1] != 0)
						dinic.add(G[i][j], G[i][j + 1], 1);
				}

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				if (G[i][j] != -1) {
					if ((i + j) % 2 == 0)
						dinic.add(source, G[i][j], 1);
					else
						dinic.add(G[i][j], sink, 1);
				}

		cout << dinic.execute() << endl;
		dinic.print();
		cout << endl;


	}
	return 0;
}
/*
Your old uncle Tom inherited a piece of land from his great-great-uncle. Originally, the property had been in the shape of a rectangle. A long time ago, however, his great-great-uncle decided to divide the land into a grid of small squares. He turned some of the squares into ponds, for he loved to hunt ducks and wanted to attract them to his property. (You cannot be sure, for you have not been to the place, but he may have made so many ponds that the land may now consist of several disconnected islands.)

Your uncle Tom wants to sell the inherited land, but local rules now regulate property sales. Your uncle has been informed that, at his great-great-uncle's request, a law has been passed which establishes that property can only be sold in rectangular lots the size of two squares of your uncle's property. Furthermore, ponds are not salable property.

Your uncle asked your help to determine the largest number of properties he could sell (the remaining squares will become recreational parks).
*/