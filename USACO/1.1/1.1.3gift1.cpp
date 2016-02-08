
/*
ID: 13182011
PROG: gift1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string a[10];
int r[10];

int main() {
	ofstream fout("gift1.out");
	ifstream fin("gift1.in");
	int NP;
	while (fin >> NP) {
		for (int i = 0; i < NP; i++)
			fin >> a[i];
		for (int i = 0; i < NP; i++)
			r[i] = 0;
		for (int i = 0; i < NP; i++) { // for each giver
			string in;
			int pos;
			fin >> in;
			for (int j = 0; j < NP; j++)
				if (in == a[j]) {
					pos = j;
					break;
				}
			int m, cnt;
			fin >> m >> cnt;
			if (cnt != 0)
				m /= cnt;
			r[pos] -= (m * cnt);
			for (int j = 0; j < cnt; j++) {
				fin >> in;
				for (int k = 0; k < NP; k++)
					if (in == a[k]) {
						r[k] += m;
						break;
					}
			}
		}
		for (int i = 0; i < NP; i++)
			fout << a[i] << ' ' << r[i] << endl;
	}
	return 0;
}