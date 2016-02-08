/*
ID: 13182011
PROG: beads
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

const int MAXN = 351;

string in;
char cl[2 * MAXN];
int num[2 * MAXN], cnt;

int main()
{
	ofstream fout("beads.out");
	ifstream fin("beads.in");

	int n;
	while (fin >> n) {
		fin >> in;
		// modify the string into a form without white at the beginning or same color at the beginning and end
		if (in[0] == 'w' || in[0] == in[n - 1]) {
			char tmp = in[0];
			int cnttmp = 0;
			for (; in[cnttmp] == tmp && cnttmp < n - 1; cnttmp++);
			if (cnttmp != n - 1) {
				in.erase(0, cnttmp);
				for (int i = 0; i < cnttmp; i++)
					in += tmp;
			}
			else { // one kind of color
				fout << n << endl;
				continue;
			}
		}
		if (in[0] == 'w') {
			char tmp = in[0];
			int cnttmp = 0;
			for (; in[cnttmp] == tmp && cnttmp < n - 1; cnttmp++);
			if (cnttmp != n - 1) {
				in.erase(0, cnttmp);
				for (int i = 0; i < cnttmp; i++)
					in += tmp;
			}
		}
		cnt = -1;
		for (int i = 0; i < n; i++) {
			if (cnt >= 1 && in[i] == cl[cnt - 1] && cl[cnt] == 'w') { // if there is a substring in the form r..rw..wr..r
				num[cnt - 1] += num[cnt] + 1;
				cnt--;
			}
			else if (in[i] == cl[cnt]) // if not a new color
				num[cnt]++;
			else if (in[i] == 'w') {
				cnt++;
				cl[cnt] = 'w';
				num[cnt] = 1;
			}
			else if (cnt > -1 && cl[cnt] != 'w') {
				cnt++;
				cl[cnt] = 'w';
				num[cnt] = 0;
				cnt++;
				cl[cnt] = in[i];
				num[cnt] = 1;
			}
			else {
				cnt++;
				cl[cnt] = in[i];
				num[cnt] = 1;
			}
		}
		if (cl[cnt] != 'w') {
			cnt++;
			cl[cnt] = 'w';
			num[cnt] = 0;
		}
		if (cnt - 1 != 0 && cl[cnt - 1] == cl[0]) {
			num[0] += num[cnt - 1] + num[cnt];
			cnt -= 2;
		}
		/*for (int i = 0; i <= cnt; i++)
		cout << cl[i] << ' ';
		cout << endl;
		for (int i = 0; i <= cnt; i++)
		cout << num[i] << ' ';
		cout << endl;*/
		if (cnt <= 4) {
			int sum = 0;
			for (int i = 0; i <= cnt; i++)
				sum += num[i];
			fout << sum << endl;
			continue;
		}

		int max = 0;
		for (int i = 0; i < cnt; i += 2) {
			int sum = (num[i] + num[(i + 1) % (cnt + 1)] + num[(i + 2) % (cnt + 1)] + num[(i + 3) % (cnt + 1)] + num[(i + cnt) % (cnt + 1)]);
			if (sum > max)
				max = sum;
		}
		fout << max << endl;
	}
	return 0;
}