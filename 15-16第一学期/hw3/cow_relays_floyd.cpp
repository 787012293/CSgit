#include <iostream>
using namespace std;

const int MAXN = 202;
const int MAXI = 1002;
const int INF = 0x3f3f3f3f;

int N, T, S, E;
int a[MAXN][MAXN], temp[MAXN][MAXN], ans[MAXN][MAXN];
int h[MAXI]; // hash list
int cnt;

void init()
{
	memset(h, -1, sizeof(h));
	int len, p1, p2;
	cnt = 0;

	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			a[i][j] = temp[i][j] = INF;

	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++)
			ans[i][j] = INF;
		ans[i][i] = 0;
	}

	for (int i = 0; i < T; i++) {
		scanf("%d%d%d", &len, &p1, &p2);
		if (h[p1] == -1) {
			h[p1] = cnt;
			cnt++;
		}
		if (h[p2] == -1) {
			h[p2] = cnt;
			cnt++;
		}
		if (a[h[p1]][h[p2]] > len)
			a[h[p1]][h[p2]] = a[h[p2]][h[p1]] = len;
	}
}

void floyd(int result[MAXN][MAXN], int l[MAXN][MAXN], int r[MAXN][MAXN])
{
	for (int k = 0; k < cnt; k++)
		for (int i = 0; i < cnt; i++)
			for (int j = 0; j < cnt; j++)
				if (result[i][j] > l[i][k] + r[k][j])
					result[i][j] = l[i][k] + r[k][j];
}

void copy(int src[MAXN][MAXN], int dest[MAXN][MAXN])
{
	for (int i = 0; i < cnt; i++)
		for (int j = 0; j < cnt; j++) {
			dest[i][j] = src[i][j];
			src[i][j] = INF;
		}
}

int main()
{

	while (cin >> N >> T >> S >> E) {
		init();
		int n = N;
		while (n > 0) {
			if (n & 1) {
				floyd(temp, ans, a);
				copy(temp, ans);
			}
			floyd(temp, a, a);
			copy(temp, a);
			n >>= 1;
		}
		printf("%d\n", ans[h[S]][h[E]]);
	}
	return 0;
}

/*
For their physical fitness program, N (2 ¡Ü N ¡Ü 1,000,000) cows have decided to run a relay race using the T (2 ¡Ü T ¡Ü 100) cow trails throughout the pasture.

Each trail connects two different intersections (1 ¡Ü I1i ¡Ü 1,000; 1 ¡Ü I2i ¡Ü 1,000), each of which is the termination for at least two trails. The cows know the lengthi of each trail (1 ¡Ü lengthi  ¡Ü 1,000), the two intersections the trail connects, and they know that no two intersections are directly connected by two different trails. The trails form a structure known mathematically as a graph.

To run the relay, the N cows position themselves at various intersections (some intersections might have more than one cow). They must position themselves properly so that they can hand off the baton cow-by-cow and end up at the proper finishing place.

Write a program to help position the cows. Find the shortest path that connects the starting intersection (S) and the ending intersection (E) and traverses exactly N cow trails.
*/