/*
ID: 13182011
PROG: combo
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

int n;
int a[3], b[3];

bool dis(int i, int j)
{
	int res = (i - j + n) % n;
	if (res >= n - 2 || res <= 2)
		return true;
	else
		return false;
}

bool isgood(int i, int j, int k)
{
	if ((dis(i, a[0]) && dis(j, a[1]) && dis(k, a[2])) ||
		(dis(i, b[0]) && dis(j, b[1]) && dis(k, b[2])))
		return true;
	else
		return false;
}

int main()
{
	ifstream fin("combo.in");
	ofstream fout("combo.out");
	while (fin >> n) {
		// number 1..n is equivalent to 0..n-1
		for (int i = 0; i < 3; i++)
			fin >> a[i];
		for (int i = 0; i < 3; i++)
			fin >> b[i];
		int cnt = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				for (int k = 0; k < n; k++)
					if (isgood(i, j, k))
						cnt++;
		fout << cnt << endl;
	}
	return 0;
}