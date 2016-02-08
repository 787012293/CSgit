/*
ID: 13182011
PROG: palsquare
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <assert.h>

using namespace std;
const char mp[22] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K' };

// base 10 to base B
string t2b(int t, int base)
{
	string result;
	while (t > 0) {
		int rem = t % base;
		result += mp[rem];
		t = t / base;
	}
	reverse(result.begin(), result.end());
	return result;
}

int b2t(string b, int base)
{
	int result = 0;
	for (int i = 0; i < b.length(); i++) {
		int tmp;
		if (b[i] >= '0' && b[i] <= '9')
			tmp = b[i] - '0';
		else
			tmp = b[i] - 'A' + 10;
		result += tmp;
		result *= 10;
	}
	result /= 10;
	return result;
}

bool ispal(string b)
{
	for (int i = 0; i < b.length() / 2; i++)
		if (b[i] != b[b.length() - i - 1])
			return false;
	return true;

}

int main()
{
	ifstream fin("palsquare.in");
	ofstream fout("palsquare.out");
	int B;
	while (fin >> B) {
		for (int i = 1; i <= 300; i++) {
			int tmp = i * i;
			string b = t2b(tmp, B);
			if (ispal(b))
				fout << t2b(i, B) << ' ' << b << endl;
		}
	}
}
