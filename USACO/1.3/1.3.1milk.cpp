/*
ID: 13182011
PROG: milk
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <assert.h>

using namespace std;
const int MAXN = 5002;

struct farmer {
	int p, a;
} f[MAXN];

bool cmp(farmer a, farmer b)
{
	return a.p < b.p;
}

int main()
{
	ifstream fin("milk.in");
	ofstream fout("milk.out");
	int n, m;
	while (fin >> n >> m) {
		for (int i = 0; i < m; i++)
			fin >> f[i].p >> f[i].a;
		sort(f, f + m, cmp);
		int sum = 0;
		for (int i = 0; i < m; i++) {
			if (f[i].a < n) {
				n -= f[i].a;
				sum += f[i].a * f[i].p;
			}
			else {
				sum += n * f[i].p;
				break;
			}
		}
		fout << sum << endl;
	}
	return 0;
}