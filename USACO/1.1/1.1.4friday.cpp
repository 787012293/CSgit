
/*
ID: 13182011
PROG: friday
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

int mo[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
//              1   2   3   4   5   6   7   8   9  10  11  12
int r[7];

bool isleap(int n)
{
	if (n % 400 == 0)
		return true;
	else if (n % 100 == 0)
		return false;
	else if (n % 4 == 0)
		return true;
	else
		return false;
}

int main() {
	ofstream fout("friday.out");
	ifstream fin("friday.in");
	int n;
	while (fin >> n) {
		memset(r, 0, sizeof(r));
		int mod = 4; // 13/12/1899 is Wed
		for (int i = 0; i < n; i++) { // for each year
			if (isleap(1900 + i))
				mo[1] = 29;
			else
				mo[1] = 28;
			for (int j = 0; j < 12; j++) { // for each month 
				mod = (mod + mo[(j + 11) % 12]) % 7;
				r[mod]++;
			}
		}
		for (int i = 0; i < 6; i++)
			fout << r[i] << ' ';
		fout << r[6] << endl;
	}

	return 0;
}