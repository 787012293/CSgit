/*
ID: 13182011
PROG: numtri
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
const int MAXN = 1001;
int n;
int a[MAXN][MAXN], sum[MAXN][MAXN];


int main()
{
	ifstream fin("numtri.in");
	ofstream fout("numtri.out");

	while (fin >> n) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j <= i; j++)
				fin >> a[i][j];
		sum[0][0] = a[0][0];
		for (int i = 1; i < n; i++)
			for (int j = 0; j <= i; j++) {
				if (j == 0) sum[i][j] = sum[i - 1][j] + a[i][j];
				else if (j == i) sum[i][j] = sum[i - 1][j - 1] + a[i][j];
				else sum[i][j] = max(sum[i - 1][j], sum[i - 1][j - 1]) + a[i][j];
			}

		int m = 0;
		for (int i = 0; i < n; i++)
			if (sum[n - 1][i] > m)
				m = sum[n - 1][i];
		fout << m << endl;
	}

	fin.close();
	fout.close();
	return 0;
}