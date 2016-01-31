/*
ID: 13182011
PROG: namenum
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <assert.h>

using namespace std;

const int MAXN = 5002;

struct lst {
	string name;
	unsigned long long num;
} a[MAXN];
int n;

bool cmp(lst a, lst b)
{
	if (a.num != b.num)
		return a.num < b.num;
	else
		return a.name < b.name;
}

int fnd(unsigned long long dst)
{
	int l = 0, r = n - 1, mid;
	while (l < r) {
		mid = (l + r) >> 1;
		if (a[mid].num == dst)
			return mid;
		else if (a[mid].num < dst)
			l = mid + 1;
		else
			r = mid;
	}
	if (a[l].num == dst)
		return l;
	else
		return -1;
}

int main()
{
	ifstream fin("namenum.in");
	ifstream in("dict.txt");
	ofstream fout("namenum.out");

	n = 0;
	while (in >> a[n].name) {
		a[n].num = 0;
		for (int i = 0; i < a[n].name.length(); i++) {
			int tmp;
			switch (a[n].name[i]) {
			case 'A': case 'B': case 'C': tmp = 2; break;
			case 'D': case 'E': case 'F': tmp = 3; break;
			case 'G': case 'H': case 'I': tmp = 4; break;
			case 'J': case 'K': case 'L': tmp = 5; break;
			case 'M': case 'N': case 'O': tmp = 6; break;
			case 'P': case 'R': case 'S': tmp = 7; break;
			case 'T': case 'U': case 'V': tmp = 8; break;
			case 'W': case 'X': case 'Y': tmp = 9; break;
			case 'Q': case 'Z': continue;
				assert(0);
			}
			a[n].num += tmp;
			a[n].num *= 10;
		}
		a[n].num /= 10;
		n++;
	}
	sort(a, a + n, cmp);
	unsigned long long snum; // serial number
	while (fin >> snum) {
		int tmp = fnd(snum);
		if (tmp == -1) {
			fout << "NONE" << endl;
			continue;
		}
		for (; a[tmp].num == snum; tmp--);
		for (tmp++; a[tmp].num == snum; tmp++)
			fout << a[tmp].name << endl;
	}
	return 0;
}
