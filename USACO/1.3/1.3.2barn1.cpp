/*
ID: 13182011
PROG: barn1
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

const int INF = 0x3f3f3f3f;

vector<int> a;
bool s[202];

bool cmp(int a, int b)
{
	return a > b;
}


int main()
{
	ifstream fin("barn1.in");
	ofstream fout("barn1.out");
	int M, S, C;
	while (fin >> M >> S >> C) {
		int pos;
		memset(s, 0, sizeof(s));
		int head = INF, tail = -1;
		for (int i = 0; i < C; i++) {
			fin >> pos;
			if (pos < head) head = pos;
			if (pos > tail) tail = pos;
			s[pos] = true;
		}
		int cnt = 0;
		for (int i = head; i <= tail; i++) {
			if (s[i] && !s[i - 1]) {
				a.push_back(cnt);
				cnt = 0;
			}
			else if (!s[i])
				cnt++;
		}
		sort(a.begin(), a.end(), cmp);
		int len = tail - head + 1;
		for (int i = 0; i < M - 1 && i < a.size(); i++)
			len -= a[i];
		fout << len << endl;
	}
	return 0;
}