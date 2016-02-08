/*
ID: 13182011
PROG: milk3
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
const int MAXN = 20;

int ca, cb, cc; // capacity  
bool res[MAXN + 1];
bool vis[MAXN + 1][MAXN + 1];

void pour(int a, int b, int c)
{
	if (vis[a][b]) return;
	vis[a][b] = true;
	if (a == 0) res[c] = true;
	if (a >= cb - b) pour(a - cb + b, cb, c);
	else pour(0, b + a, c);
	if (a >= cc - c) pour(a - cc + c, b, cc);
	else pour(0, b, c + a);
	if (b >= ca - a) pour(ca, b - ca + a, c);
	else pour(a + b, 0, c);
	if (b >= cc - c) pour(a, b - cc + c, cc);
	else pour(a, 0, c + b);
	if (c >= ca - a) pour(ca, b, c - ca + a);
	else pour(a + c, b, 0);
	if (c >= cb - b) pour(a, cb, c - cb + b);
	else pour(a, b + c, 0);
}

int main()
{
	ifstream fin("milk3.in");
	ofstream fout("milk3.out");
	while (fin >> ca >> cb >> cc) {
		memset(res, 0, sizeof(res));
		memset(vis, 0, sizeof(vis));
		pour(0, 0, cc);
		bool flag = false;
		for (int i = 0; i <= cc; i++) {
			if (res[i] && flag) fout << " ";
			if (res[i]) {
				fout << i;
				flag = true;
			}
		}
		fout << endl;
	}
	fin.close();
	fout.close();
	return 0;
}