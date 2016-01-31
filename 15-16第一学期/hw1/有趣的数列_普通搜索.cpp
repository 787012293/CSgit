#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int MAXN = 100000;

int N, S;
int a[MAXN], sum[MAXN], len[MAXN], ans[MAXN];

int main()
{
	while (cin >> N >> S) {
		for (int i = 0; i < N; i++)
			scanf("%d", &a[i]);
		sum[0] = a[0];
		len[0] = 0;
		if (sum[0] <= S) len[0]++;
		for (int i = 1; i < N; i++) {
			sum[i] = sum[i - 1] + a[i];
			if (sum[i] <= S)
				len[0]++;
		}

		int maxlen = len[0];
		for (int i = 1; i < N; i++) {
			// cout << maxlen << " " << i << " " << N << endl;
			if (maxlen + i == N + 1) {
				for (; i < N; i++) {
					maxlen--;
					len[i] = maxlen;
				}
				break;
			}
			if (maxlen > 0) maxlen--;
			while (sum[i + maxlen - 1] - sum[i - 1] <= S && maxlen < N - i + 1)
				maxlen++;
			maxlen--;
			len[i] = maxlen;
		}

		/*for (int i = 0; i < N; i++)
		cout << len[i] << " ";
		cout << endl;*/

		int ans[MAXN];
		memset(ans, 0, sizeof(ans));

		for (int i = 0; i < N; i++) {
			if (len[i] == 0) {
				ans[i] = 0;
				continue;
			}
			for (int j = len[i] + i - 1; j >= i; j--) {
				if (j + 1 > N - 1) continue;
				if (len[j + 1] >= j - i + 1) {
					ans[i] = 2 * (j - i + 1);
					break;
				}
			}
		}

		for (int i = 0; i < N; i++)
			printf("%d\n", ans[i]);
	}
	return 0;
}