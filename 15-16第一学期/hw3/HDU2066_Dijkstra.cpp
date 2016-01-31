#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T, S, D;

const int MAXN = 10000;
const int INF = 0x3f3f3f3f;

vector<pair<int, int>> OE[MAXN], E[MAXN];
int h[MAXN], cnth;
bool vis[MAXN];
int d[MAXN];


void init()
{
	cnth = 0;
	memset(h, -1, sizeof(h));

	int a, b, time;
	// build
	for (int i = 0; i < T; i++) {
		scanf("%d%d%d", &a, &b, &time);
		if (h[a] == -1) {
			cnth++;
			h[a] = cnth;
		}
		if (h[b] == -1) {
			cnth++;
			h[b] = cnth;
		}

		OE[h[a]].push_back(make_pair(h[b], time));
		OE[h[b]].push_back(make_pair(h[a], time));
	}

	// remove self-loop
	for (int i = 1; i <= cnth; i++) {
		memset(vis, 0, sizeof(vis));
		sort(OE[i].begin(), OE[i].end());
		for (int j = 0; j < OE[i].size(); j++)
			if (!vis[OE[i][j].first]) {
				vis[OE[i][j].first] = true;
				E[i].push_back(make_pair(OE[i][j].first, OE[i][j].second));
			}
	}

	for (int i = 0; i < S; i++) {
		scanf("%d", &a);
		E[0].push_back(make_pair(h[a], 0));
		E[h[a]].push_back(make_pair(0, 0));
	}
}

void dijkstra(int s)
{
	for (int i = 0; i <= cnth; i++)
		d[i] = INF;
	d[s] = 0;
	memset(vis, 0, sizeof(vis));
	for (int cnt = cnth; cnt >= 0; cnt--) {
		int u = 0, min = INF;
		for (int i = 0; i <= cnth; i++)
			if (!vis[i] && d[i] < min) {
				u = i;
				min = d[i];
			}
		vis[u] = true;
		for (int v = 0; v < E[u].size(); v++)
			if (d[E[u][v].first] > d[u] + E[u][v].second)
				d[E[u][v].first] = d[u] + E[u][v].second;
	}
}

int main()
{
	while (cin >> T >> S >> D) {
		init();
		dijkstra(0);
		int min = INF, dest;
		for (int i = 0; i < D; i++) {
			scanf("%d", &dest);
			if (d[h[dest]] < min & h[dest] != -1) // condition that graph is disconnected
				min = d[h[dest]];
		}
		printf("%d\n", min);
		for (int i = 0; i <= MAXN; i++)
			OE[i].clear();
		for (int i = 0; i <= MAXN; i++)
			E[i].clear();
	}

	return 0;
}

/*
8 2 3
1 3 7
1 3 5
1 3 6
1 4 7
2 8 12
3 8 4
4 9 12
9 10 2
1 2
8 9 10

10 1 2
1 2 10
2 3 1
2 4 2
2 4 3
3 5 6
3 5 4
1 5 7
4 3 9
1 4 5
4 5 2
1
3 5

��Ȼ�ݶ��Ǹ�·�գ������ں������һ��࣬��Ȼ������У԰����·���ˣ���~),���ǲݶ���Ȼ��ϲ�����У���Ϊ����;�� �������ܶ��ˣ��������ӣ�^0^�����ܶ��£����ܷḻ�Լ��������������Կ������ķ羰�����ݶ���ȥ�ܶ�ط�������Ҫȥ����������ҹ����ȥ����˹����Ӱ��ȥ����ɽ�Ͽ�����ȥŦԼ���⿴ѩ����ȥ����ȿ���д�ţ�ȥ����̽���Ͻ�Ů�����ۿ����پͿ쵽�ˣ���ôһ���ʱ�䣬�ɲ����˷Ѱ���һ��Ҫ���Լ��úõķŸ��٣�����Ҳ���ܻķ���ѵ���������Բݶ�������Ҫ����̵�ʱ��ȥһ���Լ���ȥ�ĵط�����Ϊ�ݶ��ļ���һ��С���ϣ�û�л𳵾�����������ֻ��ȥ�ڽ��ĳ������𳵣��ÿ�����~����
���������ж��飬ÿ��ĵ�һ������������T��S��D����ʾ��T��·���Ͳݶ������ڵĳ��е���S�����ݶ���ȥ�ĵط���D����
������T�У�ÿ������������a��b��time,��ʾa,b����֮��ĳ�����timeСʱ��(1=<(a,b)<=1000;a,b ֮������ж���·)
���ŵĵ�T+1����S��������ʾ�Ͳݶ��������ĳ��У�
���ŵĵ�T+2����D��������ʾ�ݶ���ȥ�ط���
����ݶ���ȥĳ��ϲ���ĳ��е����ʱ�䡣
*/