/*
ID: 13182011
PROG: wormhole
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <assert.h>
#include <vector>

using namespace std;
const int MAXN = 15;

int n;
int x[MAXN], y[MAXN], r[MAXN], p[MAXN]; // x and y coordinate, right point, partner

bool cycle()
{
	for (int i = 0; i < n; i++) {
		int pos = i;
		for (int j = 0; j < n; j++) {
			pos = r[p[pos]];
			if (pos == -1) break;
		}
		if (pos != -1) return true;
	}
	return false;
}

int solve()
{
	int i, total = 0;
	for (i = 0; i < n; i++)
		if (p[i] == -1) break;

	// if everyone paired
	if (i >= n) {
		if (cycle()) return 1;
		else return 0;
	}

	for (int j = i + 1; j < n; j++)
		if (p[j] == -1) {
			p[i] = j;
			p[j] = i;
			total += solve();
			p[i] = p[j] = -1;
		}
	return total;
}

int main()
{
	ifstream fin("wormhole.in");
	ofstream fout("wormhole.out");
	while (fin >> n) {
		for (int i = 0; i < n; i++)
			fin >> x[i] >> y[i];
		memset(r, -1, sizeof(r));
		memset(p, -1, sizeof(p));

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				if (x[j] > x[i] && y[j] == y[i])
					if (r[i] == -1 || x[j] - x[i] < x[r[i]] - x[i])
						r[i] = j;
			}

		fout << solve() << endl;
	}
	return 0;
}
