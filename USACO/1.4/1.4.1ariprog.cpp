/*
ID: 13182011
PROG: ariprog
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
const int MAXN = 25;
const int MAXM = 250;
const int INF = 0x3f3f3f3f;
int n, m;
int a[MAXN + 1];
bool isb[MAXM * MAXM * 2 + 1]; // is bisquare
int formb[MAXM * MAXM * 2 + 1]; // form

int main()
{
	ifstream fin("ariprog.in");
	ofstream fout("ariprog.out");

	memset(isb, 0, sizeof(isb));
	memset(formb, 0x3f, sizeof(formb));
	for (int i = 0; i <= MAXM; i++)
		for (int j = 0; j <= MAXM; j++) {
			isb[i * i + j * j] = true;
			if (max(i, j) < formb[i * i + j * j])
				formb[i * i + j * j] = max(i, j);
		}

	while (fin >> n >> m) {
		int maxm = 2 * m * m;
		int cnt = 0;
		for (int i = 1; i <= maxm / 2; i++) // step, disgusting tricks
			for (int j = 0; j <= maxm - i * (n - 1); j++) { // head
				bool flag = true;
				for (int k = 0; k < n; k++) // length
					if (formb[j + i * k] > m || !isb[j + i * k]) {
						flag = false;
						break;
					}
				if (flag) {
					fout << j << ' ' << i << endl;
					cnt++;
				}
			}
		if (cnt == 0) fout << "NONE" << endl;
	}

	fin.close();
	fout.close();
	return 0;
}