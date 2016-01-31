#include <iostream>
#include <algorithm>
using namespace std;

typedef unsigned long long ULL;
const int MAXN = 40020;
const int SEED = 1000000007;

ULL pwr[MAXN];
int m;

char s[MAXN];
int len;

ULL pre[MAXN];
ULL h[MAXN];
int no[MAXN];

bool cmp(const int a, const int b)
{
	if (h[a] != h[b])
		return h[a] < h[b];
	else
		return a < b;
}

int judge(int l)
{
	int cnt = 0;
	int n = len - l + 1, pos = -1;
	for (int i = 0; i < n; i++)
		no[i] = i;
	for (int i = 0; i < n; i++)
		h[i] = pre[i + l - 1] - pre[i - 1] * pwr[l];
	sort(no, no + n, cmp);
	for (int i = 0; i < n; i++) {
		if (i == 0 || h[no[i]] != h[no[i - 1]])
			cnt = 0;
		cnt++;
		if (cnt >= m)
			pos = max(pos, no[i]);
	}
	return pos;
}

int main()
{
	// freopen("input.in", "r", stdin);
	pwr[0] = 1;
	for (int i = 1; i < MAXN; i++)
		pwr[i] = pwr[i - 1] * SEED;
	while (cin >> m) {
		if (m == 0) break;
		cin >> s;
		pre[0] = s[0];
		for (int i = 1; s[i] != '\0'; i++)
			pre[i] = pre[i - 1] * SEED + s[i];
		len = strlen(s);
		if (judge(1) == -1) {
			cout << "none" << endl;
			continue;
		}
		int l = 0, r = len + 1;
		while (l + 1 < r) {
			int mid = (r + l) / 2;
			if (judge(mid) != -1)
				l = mid;
			else
				r = mid;
		}
		int p = judge(l);
		cout << l << ' ' << p << endl;
	}
	return 0;
}
/*
3
baaaababababbababbab
11
baaaababababbababbab
3
cccccc
2
ddddccccrrccccdddd
1
a
0

Dr. Ellie Arroway has established contact with an extraterrestrial civilization. However, all efforts to decode their messages have failed so far because, as luck would have it, they have stumbled upon a race of stuttering aliens! Her team has found out that, in every long enough message, the most important words appear repeated a certain number of times as a sequence of consecutive characters, even in the middle of other words. Furthermore, sometimes they use contractions in an obscure manner. For example, if they need to say bab twice, they might just send the message babab, which has been abbreviated because the second b of the first word can be reused as the first b of the second one.
Thus, the message contains possibly overlapping repetitions of the same words over and over again. As a result, Ellie turns to you, S.R. Hadden, for help in identifying the gist of the message.
Given an integer m, and a string s, representing the message, your task is to find the longest substring of s that appears at least m times. For example, in the message baaaababababbababbab, the length-5 word babab is contained 3 times, namely at positions 5, 7 and 12 (where indices start at zero). No substring appearing 3 or more times is longer (see the first example from the sample input). On the other hand, no substring appears 11 times or more (see example 2). In case there are several solutions, the substring with the rightmost occurrence is preferred (see example 3).
*/