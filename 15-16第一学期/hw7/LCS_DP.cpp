#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

const int MAXN = 1000;

int dp[MAXN][MAXN];

// dp[i][j] is the LCS of a[0 ... i] and b[0 ... j]
// dp[i][j] = dp[i - 1][j - 1] + 1, if a[i] == b[j]
//          = max(dp[i - 1][j], dp[i][j - 1]), otherwise
// dp[alen - 1][blen - 1] is the result

int main()
{
	string a, b;
	while (cin >> a >> b) {
		int alen = a.length(), blen = b.length();
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= alen; i++)
			for (int j = 1; j <= blen; j++) {
				if (a[i - 1] == b[j - 1])
					dp[i][j] = dp[i - 1][j - 1] + 1;
				else
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		cout << dp[alen][blen] << endl;
	}
	return 0;
}
/*
A subsequence of a given sequence is the given sequence with some elements (possible none) left out. Given a sequence X = <x1, x2, ..., xm> another sequence Z = <z1, z2, ..., zk> is a subsequence of X if there exists a strictly increasing sequence <i1, i2, ..., ik> of indices of X such that for all j = 1,2,...,k, xij = zj. For example, Z = <a, b, f, c> is a subsequence of X = <a, b, c, f, b, c> with index sequence <1, 2, 4, 6>. Given two sequences X and Y the problem is to find the length of the maximum-length common subsequence of X and Y.
The program input is from a text file. Each data set in the file contains two strings representing the given sequences. The sequences are separated by any number of white spaces. The input data are correct. For each set of data the program prints on the standard output the length of the maximum-length common subsequence from the beginning of a separate line.
*/