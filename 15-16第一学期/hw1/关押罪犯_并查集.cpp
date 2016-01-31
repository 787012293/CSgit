#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 100000;

struct ang {
	int a, b, c;
};

int id[MAXN];
int siz[MAXN];
ang arr[MAXN];
int h[MAXN];

bool compare(ang a, ang b) {
	return a.c > b.c;
}


int Find(int p)
{
	while (p != id[p]) {
		id[p] = id[id[p]];
		p = id[p];
	}
	return p;
}

void Union(int p, int q)
{
	int m = Find(p), n = Find(q);
	if (m == n) return;
	if (siz[m] < siz[n]) {
		id[m] = n;
		siz[n] += siz[m];
	}
	else {
		id[n] = m;
		siz[m] += siz[n];
	}
}


int main()
{
	int N, M;
	while (cin >> N >> M) {

		bool flag = false;

		for (int i = 0; i < M; i++)
			scanf("%d%d%d", &arr[i].a, &arr[i].b, &arr[i].c);

		sort(arr, arr + M, compare);
		memset(h, 0, sizeof(h));

		for (int i = 0; i <= N; i++)
			id[i] = i;

		for (int i = 0; i < M; i++) {
			if (h[arr[i].a] == 0)
				h[arr[i].a] = arr[i].b;
			if (h[arr[i].b] == 0)
				h[arr[i].b] = arr[i].a;

			Union(arr[i].b, h[arr[i].a]);
			Union(arr[i].a, h[arr[i].b]);

			if (Find(arr[i].a) == Find(arr[i].b)) {
				cout << arr[i].c << endl;
				flag = true;
				break;
			}
		}

		if (!flag) cout << 0 << endl;
	}

	return 0;
}