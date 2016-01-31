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

虽然草儿是个路痴（就是在杭电待了一年多，居然还会在校园里迷路的人，汗~),但是草儿仍然很喜欢旅行，因为在旅途中 会遇见很多人（白马王子，^0^），很多事，还能丰富自己的阅历，还可以看美丽的风景……草儿想去很多地方，她想要去东京铁塔看夜景，去威尼斯看电影，去阳明山上看海芋，去纽约纯粹看雪景，去巴黎喝咖啡写信，去北京探望孟姜女……眼看寒假就快到了，这么一大段时间，可不能浪费啊，一定要给自己好好的放个假，可是也不能荒废了训练啊，所以草儿决定在要在最短的时间去一个自己想去的地方！因为草儿的家在一个小镇上，没有火车经过，所以她只能去邻近的城市坐火车（好可怜啊~）。
输入数据有多组，每组的第一行是三个整数T，S和D，表示有T条路，和草儿家相邻的城市的有S个，草儿想去的地方有D个；
接着有T行，每行有三个整数a，b，time,表示a,b城市之间的车程是time小时；(1=<(a,b)<=1000;a,b 之间可能有多条路)
接着的第T+1行有S个数，表示和草儿家相连的城市；
接着的第T+2行有D个数，表示草儿想去地方。
输出草儿能去某个喜欢的城市的最短时间。
*/