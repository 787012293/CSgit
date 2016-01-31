/*
ID: 13182011
PROG: crypt1
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

bool d[10]; // digits

bool isgood(int a)
{
	while (a > 0) {
		if (!d[a % 10])
			return false;
		a /= 10;
	}
	return true;
}

int main()
{
	ifstream fin("crypt1.in");
	ofstream fout("crypt1.out");
	int n;
	while (fin >> n) {
		for (int i = 0; i < n; i++) {
			int tmp;
			fin >> tmp;
			d[tmp] = true;
		}
		int cnt = 0;
		for (int i = 1; i < 10; i++)
			for (int j = 0; j < 10; j++)
				for (int k = 0; k < 10; k++)
					for (int p = 1; p < 10; p++)
						for (int q = 0; q < 10; q++)
							if (d[i] && d[j] && d[k] && d[p] && d[q]) {
								int m = 100 * i + 10 * j + k;
								int mp = m * p, mq = m * q;
								if (!isgood(mp) || mp >= 1000) continue;
								if (!isgood(mq) || mq >= 1000) continue;
								if (!isgood(10 * mp + mq) || (10 * mp + mq) >= 10000) continue;
								cnt++;
							}
		fout << cnt << endl;
	}
	return 0;
}