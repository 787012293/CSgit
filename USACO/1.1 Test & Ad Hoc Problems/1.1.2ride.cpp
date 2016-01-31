
/*
ID: 13182011
PROG: ride
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() 
{
	ofstream fout("ride.out");
	ifstream fin("ride.in");
	string a, b;
	while (fin >> a >> b) {
		int aa = 1, bb = 1;
		for (int i = 0; i < a.length(); i++) {
			aa *= (a[i] - 'A' + 1);
			aa %= 47;
		}

		for (int i = 0; i < b.length(); i++) {
			bb *= (b[i] - 'A' + 1);
			bb %= 47;
		}

		if (aa == bb)
			fout << "GO" << endl;
		else
			fout << "STAY" << endl;
	}
	return 0;
}