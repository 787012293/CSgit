#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int MAXN = 100000;

int a[MAXN];
int b[MAXN];
long long s[MAXN];
int N, S;

bool sum(int l, int r)
{
	long long result;
	if (l == 0)
		result = s[r];
	else
		result = s[r] - s[l - 1];
	//cout << l << " " << r << " " << s[r] << " " << s[l - 1] << enl;
	if (result <= S)
		return true;
	else
		return false;
}

void binary_search(int p)
{
	int l, r, mid;
	if (p < N / 2) l = 0, r = p;
	else l = 2 * p - N + 2, r = p;

	// cout << l << " " << r << " " <<  p << endl;
	while (l <= r) {
		//cout << l << " " << r << endl;
		mid = (l + r) >> 1;
		//cout << mid << " " << p << " " << p + 1 << " " << 2 * p - mid + 1 << endl;
		if (sum(mid, p) && sum(p + 1, 2 * p - mid + 1)) r = mid - 1;
		else l = mid + 1;
	}
	//cout << 2 * (p - l + 1) << endl << endl;
	b[l] = 2 * (p - l + 1);
}

int main()
{
	while (cin >> N >> S) {
		for (int i = 0; i < N; i++)
			scanf("%d", &a[i]);
		long long temp = 0;
		for (int i = 0; i < N; i++) {
			temp += a[i];
			s[i] = temp;
		}
		s[N] = 0;
		for (int i = 0; i < N; i++)
			b[i] = 0;
		for (int i = 0; i < N; i++)
			binary_search(i);
		int max = 0;
		for (int i = 1; i < N; i++) {
			b[i] = (b[i - 1] - 2 > b[i] ? b[i - 1] - 2 : b[i]);
		}
		for (int i = 0; i < N; i++)
			cout << b[i] << endl;
	}
	return 0;
}

/*

8 8
1 2 6 0 1 4 3 4

4 6 4 4 4 2 2 0

0 1 2 3 4 5 6 7


*/