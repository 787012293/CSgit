#include <iostream>
using namespace std;

/*
[0][1] [0][1]
[2][3] [2][3]

1 2 4 8 16 32 64 128
0                 7
*/

int a[31][4];
int b[31];

void init()
{
	b[0] = 1;
	for (int i = 0; i < 30; i++)
		b[i + 1] = b[i] * 2;
	a[0][0] = 1, a[0][1] = 1, a[0][2] = 1, a[0][3] = 0;
	for (int i = 0; i < 30; i++) {
		a[i + 1][0] = (a[i][0] * a[i][0] + a[i][1] * a[i][2]) % 10000;
		a[i + 1][1] = (a[i][0] * a[i][1] + a[i][1] * a[i][3]) % 10000;
		a[i + 1][2] = (a[i][2] * a[i][0] + a[i][3] * a[i][2]) % 10000;
		a[i + 1][3] = (a[i][2] * a[i][1] + a[i][3] * a[i][3]) % 10000;
	}
}

void matrix_multiply(int p[4], int q[4])
{
	int r[4];
	r[0] = p[0], r[1] = p[1], r[2] = p[2], r[3] = p[3];
	p[0] = (q[0] * r[0] + q[1] * r[2]) % 10000;
	p[1] = (q[0] * r[1] + q[1] * r[3]) % 10000;
	p[2] = (q[2] * r[0] + q[3] * r[2]) % 10000;
	p[3] = (q[2] * r[1] + q[3] * r[3]) % 10000;
}

int comp(int k)
{
	int l = 0, r = 30, mid;
	while (l < r - 1) {
		mid = (l + r) >> 1;
		if (k >= b[mid]) l = mid;
		else r = mid;
		//cout << l <<" "<< mid << " " << r<< " " << b[mid] <<  endl;
	}
	return l;
}

int main()
{
	init();
	int n;
	while (cin >> n) {
		if (n == -1) break;
		int temp[4] = { 1, 0, 0, 1 };
		while (n != 0) {
			int l = comp(n);
			n -= b[l];
			matrix_multiply(temp, a[l]);
		}
		cout << temp[1] << endl;
	}
	return 0;

	/*int n;
	for (int i = 0; i < 31; i++)
	cout << b[i] << endl;
	while (cin >> n) {
	cout << comp(n) << endl;
	}*/
}