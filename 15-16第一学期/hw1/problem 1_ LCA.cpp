#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXM = 16;
const int MAXN = 1 << MAXM;

struct edge {
	int v, len;
};

int depth[MAXN];

// LCA
struct LCA {
	vector<edge> e[MAXN];
	int d[MAXN], p[MAXN][MAXM];

	void dfs_(int v, int f) {
		p[v][0] = f;
		for (int i = 1; i < MAXM; ++i) {
			p[v][i] = p[p[v][i - 1]][i - 1];
		}
		for (int i = 0; i < (int)e[v].size(); ++i) {
			int w = e[v][i].v;
			if (w != f) {
				d[w] = d[v] + 1;
				depth[w] = depth[v] + e[v][i].len;
				// cout << depth[w] << endl;
				dfs_(w, v);
			}
		}
	}

	int up_(int v, int m) {
		for (int i = 0; i < MAXM; ++i) {
			if (m & (1 << i)) {
				v = p[v][i];
			}
		}
		return v;
	}

	int lca(int a, int b) {
		if (d[a] > d[b]) {
			swap(a, b);
		}
		b = up_(b, d[b] - d[a]);
		if (a == b) {
			return a;
		}
		else {
			for (int i = MAXM - 1; i >= 0; --i) {
				if (p[a][i] != p[b][i]) {
					a = p[a][i];
					b = p[b][i];
				}
			}
			return p[a][0];
		}
	}

	void init(int n) {
		for (int i = 0; i < n; ++i) {
			e[i].clear();
		}
		depth[0] = 0;
	}

	void add(int a, int b, int len) {
		edge A, B;
		A.v = a, B.v = b;
		A.len = B.len = len;
		e[a].push_back(B);
		e[b].push_back(A);
	}

	void build() {
		d[0] = 0;
		dfs_(0, 0);
	}
} lca;

int main()
{
	int T;
	cin >> T;
	for (int i = 0; i < T; ++i) {
		int n, m;
		cin >> n >> m;
		lca.init(40000);
		for (int j = 0; j < n - 1; ++j) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			lca.add(a - 1, b - 1, c);
		}
		lca.build();
		for (int j = 0; j < m; ++j) {
			int a, b, fa;
			scanf("%d%d", &a, &b);
			fa = lca.lca(a - 1, b - 1);
			/*cout << a << " " << b << " " << fa << endl;
			cout << depth[a] << " " << depth[b] << " " << depth[fa] << endl;*/
			printf("%d\n", (depth[a - 1] + depth[b - 1] - depth[fa] * 2));
		}
		/*for (int i = 0; i < n; i++)
		cout << depth[i] << " ";
		cout << endl;*/
	}
	return 0;
}

/*
1
11 6
1 2 5
1 3 5
2 4 10
2 5 6
3 6 4
3 7 3
4 8 3
4 9 2
6 10 1
6 11 5
*/