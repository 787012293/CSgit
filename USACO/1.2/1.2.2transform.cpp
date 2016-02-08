/*
ID: 13182011
PROG: transform
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAXN = 11;
const int INF = 0x3f3f3f3f;
char be[MAXN][MAXN], af[MAXN][MAXN]; // before, after
char ch[MAXN][MAXN]; // changed
int n;

inline void copy(char src[MAXN][MAXN], char dest[MAXN][MAXN])
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			dest[i][j] = src[i][j];
}

inline void print(char a[MAXN][MAXN])
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << a[i][j];
		cout << endl;
	}
	cout << endl;
}

bool cmp(char a[MAXN][MAXN], char b[MAXN][MAXN])
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (a[i][j] != b[i][j])
				return false;
	return true;
}

void r90(char a[MAXN][MAXN], int times)
{
	times %= 4;
	while (times > 0) {
		char tmp[MAXN][MAXN];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				tmp[j][n - i - 1] = a[i][j];
		copy(tmp, a);
		times--;
	}
}

void r180(char a[MAXN][MAXN], int times)
{
	times %= 2;
	while (times > 0) {
		char tmp[MAXN][MAXN];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				tmp[n - i - 1][n - j - 1] = a[i][j];
		copy(tmp, a);
		times--;
	}
}

void r270(char a[MAXN][MAXN], int times)
{
	times %= 4;
	while (times > 0) {
		char tmp[MAXN][MAXN];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				tmp[n - j - 1][i] = a[i][j];
		copy(tmp, a);
		times--;
	}
}

void ref(char a[MAXN][MAXN], int times)
{
	times %= 2;
	while (times > 0) {
		char tmp[MAXN][MAXN];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				tmp[i][n - j - 1] = a[i][j];
		copy(tmp, a);
		times--;
	}
}

int main() {
	ofstream fout("transform.out");
	ifstream fin("transform.in");
	while (fin >> n) {
		for (int i = 0; i < n; i++)
			fin >> be[i];
		for (int i = 0; i < n; i++)
			fin >> af[i];

		copy(be, ch);
		r90(ch, 1);
		if (cmp(af, ch)) {
			fout << 1 << endl;
			continue;
		}
		copy(be, ch);
		r180(ch, 1);
		if (cmp(af, ch)) {
			fout << 2 << endl;
			continue;
		}
		copy(be, ch);
		r270(ch, 1);
		if (cmp(af, ch)) {
			fout << 3 << endl;
			continue;
		}
		copy(be, ch);
		ref(ch, 1);
		if (cmp(af, ch)) {
			fout << 4 << endl;
			continue;
		}
		copy(be, ch);
		ref(ch, 1);
		r90(ch, 1);
		if (cmp(af, ch)) {
			fout << 5 << endl;
			continue;
		}
		copy(be, ch);
		ref(ch, 1);
		r180(ch, 1);
		if (cmp(af, ch)) {
			fout << 5 << endl;
			continue;
		}
		copy(be, ch);
		ref(ch, 1);
		r270(ch, 1);
		if (cmp(af, ch)) {
			fout << 5 << endl;
			continue;
		}
		if (cmp(af, be)) {
			fout << 6 << endl;
			continue;
		}
		fout << 7 << endl;
	}
	return 0;
}