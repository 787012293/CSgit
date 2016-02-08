/*
ID: 13182011
PROG: skidesign
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
const int MAXN = 1002;
const int INF = 0x3f3f3f3f;
int n;
int a[MAXN];

int main()
{
	ifstream fin("skidesign.in");
	ofstream fout("skidesign.out");

	while (fin >> n) {
		int min = INF, max = -1;
		for (int i = 0; i < n; i++) {
			fin >> a[i];
			if (a[i] < min) min = a[i];
			if (a[i] > max) max = a[i];
		}
		int diff = max - min;
		if (diff <= 17) {
			fout << 0 << endl;
			continue;
		}
		int result = INF;
		for (int l = min, r = min + 17; r <= max; l++, r++) {
			int tmp = 0;
			for (int i = 0; i < n; i++) {
				if (a[i] < l) tmp += (l - a[i]) * (l - a[i]);
				if (a[i] > r) tmp += (a[i] - r) * (a[i] - r);
			}
			if (tmp < result) result = tmp;
		}
		fout << result << endl;
	}

	fin.close();
	fout.close();
	return 0;
}