#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
using namespace std;

const int MAXN = 102;

// dp[i][j] record the number of brackets need to be added to sequence s(i, j) to form a regular sequence
// dp[i][j] = 1 for all i
// dp[i][j] = dp[i + 1][j - 1] if s[i] and s[j] is a match
// dp[i][j] = min(dp[i][k] + dp[k + 1][j]) otherwise

string s;
int len;
int dp[MAXN][MAXN];
int b[MAXN][MAXN]; // record the breakpoint between s[i] and s[j]

void print(int i, int j)
{
	if (i == j) {
		if (s[i] == '(' || s[i] == ')')
			cout << "()";
		else
			cout << "[]";
	}
	else if (i < j) {
		if (b[i][j] == -1) {
			if (s[i] == '(') {
				cout << "(";
				print(i + 1, j - 1);
				cout << ")";
			}
			else {
				cout << "[";
				print(i + 1, j - 1);
				cout << "]";
			}
		}
		else {
			print(i, b[i][j]);
			print(b[i][j] + 1, j);
		}
	}

}

int main()
{
	s.clear();
	cin >> s;
	len = s.length();
	memset(dp, -1, sizeof(dp));
	memset(b, -1, sizeof(b));
	for (int i = 0; i < len; i++)
		dp[i][i] = 1;
	for (int i = 1; i < len; i++)
		for (int j = 0; j < len - i; j++) {
			// calculate dp[j][i + j]
			int min = dp[j][j] + dp[j + 1][i + j];
			b[j][i + j] = j;
			for (int k = j; k < i + j; k++)
				if (dp[j][k] + dp[k + 1][i + j] < min) {
					min = dp[j][k] + dp[k + 1][i + j];
					b[j][i + j] = k;
				}
			dp[j][i + j] = min;

			if ((s[j] == '(' && s[i + j] == ')') || (s[j] == '[' && s[i + j] == ']'))
				if (dp[j + 1][i + j - 1] < min) {
					dp[j][i + j] = dp[j + 1][i + j - 1];
					b[j][i + j] = -1;
				}
		}

	/*for (int i = 0; i < 15; i++) {
	for (int j = 0; j < 15; j++)
	cout << std::right << setw(3) << dp[i][j] << ' ';
	cout << endl;
	}*/

	print(0, len - 1);
	cout << endl;
	return 0;
}

/*
[(](](]
(([))]

Let us define a regular brackets sequence in the following way:

1. Empty sequence is a regular sequence.
2. If S is a regular sequence, then (S) and [S] are both regular sequences.
3. If A and B are regular sequences, then AB is a regular sequence.

For example, all of the following sequences of characters are regular brackets sequences:

(), [], (()), ([]), ()[], ()[()]

And all of the following character sequences are not:

(, [, ), )(, ([)], ([(]

Some sequence of characters '(', ')', '[', and ']' is given. You are to find the shortest possible regular brackets sequence, that contains the given character sequence as a subsequence. Here, a string a1 a2 ... an is called a subsequence of the string b1 b2 ... bm, if there exist such indices 1 = i1 < i2 < ... < in = m, that aj = bij for all 1 = j = n.
*/