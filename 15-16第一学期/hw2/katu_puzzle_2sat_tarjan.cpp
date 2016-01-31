#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

struct SCCTarjan {
	int n;
	vector<vector<int>> e;
	vector<int> id;
	vector<vector<int>> scc;

	vector<int> dfn, low;
	int timestamp;
	stack<int> s;

	void init(int n) {
		this->n = n;
		vector<vector<int>>(n).swap(e); // free memory
		id.resize(n);
		dfn.resize(n);
		low.resize(n);
	}

	void add(int a, int b) {
		e[a].push_back(b);
	}

	void dfs(int v) {
		dfn[v] = timestamp++;
		low[v] = dfn[v];
		s.push(v);
		for (vector<int>::const_iterator w = e[v].begin(); w != e[v].end(); ++w) {
			if (dfn[*w] == -1) { // if is not visited
				dfs(*w);
				low[v] = min(low[v], low[*w]);
			}
			else if (dfn[*w] != -2) // if is in the stack and is not a backward edge
				low[v] = min(low[v], dfn[*w]);
		}

		if (low[v] == dfn[v]) {
			vector<int> t;
			do {
				int w = s.top();
				s.pop();
				id[w] = (int)scc.size();
				t.push_back(w);
				dfn[w] = -2;
			} while (t.back() != v);
			scc.push_back(t);
		}
	}

	int gao() {
		scc.clear();
		stack<int>().swap(s);
		timestamp = 0;

		fill(dfn.begin(), dfn.end(), -1);
		for (int i = 0; i < n; ++i)
			if (dfn[i] == -1)
				dfs(i);

		return (int)scc.size();
	}
};

const char arr[3][4] = { "AND", "OR", "XOR" };

int main()
{
	int N, M;
	SCCTarjan scc;
	while (cin >> N >> M) {
		scc.init(2 * N);
		int a, b, c;
		char d[4];
		for (int i = 0; i < M; i++) {
			scanf("%d%d%d", &a, &b, &c);
			scanf("%s", d);
			if (!strcmp(d, arr[0])) { // AND
				if (c) {
					scc.add(2 * a + 0, 2 * a + 1);
					scc.add(2 * b + 0, 2 * b + 1);
				}
				else {
					scc.add(2 * a + 1, 2 * b + 0);
					scc.add(2 * b + 1, 2 * a + 0);
				}
			}
			else if (!strcmp(d, arr[1])) { // OR
				if (c) {
					scc.add(2 * a + 0, 2 * b + 1);
					scc.add(2 * b + 0, 2 * a + 1);
				}
				else {
					scc.add(2 * a + 1, 2 * a + 0);
					scc.add(2 * b + 1, 2 * b + 0);
				}
			}
			else if (!strcmp(d, arr[2])) { // XOR
				if (c) {
					scc.add(2 * a + 1, 2 * b + 0);
					scc.add(2 * b + 1, 2 * a + 0);
					scc.add(2 * a + 0, 2 * b + 1);
					scc.add(2 * b + 0, 2 * a + 1);
				}
				else {
					scc.add(2 * a + 1, 2 * b + 1);
					scc.add(2 * b + 1, 2 * a + 1);
					scc.add(2 * a + 0, 2 * b + 0);
					scc.add(2 * b + 0, 2 * a + 0);
				}
			}
		}

		scc.gao();
		bool flag = true;
		for (int i = 0; i < N; i++)
			if (scc.id[2 * i + 0] == scc.id[2 * i + 1]) {
				flag = false;
				break;
			}
		if (flag) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}