#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const int MAXM = 1002;
const int MAXN = 104;
const int INF = 99999999;

struct edge {
	int u, v;
	int cap, flow;
	int next;
	edge() {}
	edge(int u, int v, int cap, int flow, int next) {
		this->u = u;
		this->v = v;
		this->cap = cap;
		this->flow = flow;
		this->next = next;
	}
};

int M, N;
int pigh[MAXM]; // pig number of each pighouse
int q[MAXM][MAXN]; // q[] and cnt[] store the buying queue of each pighouse
int cnt[MAXM];
int cap[MAXN];

edge G[MAXN*4+MAXN*MAXN];
int m; // indicate the number of edges
int head[MAXN];
int d[MAXN];
const int source = 0, sink = MAXN-1;

bool exist[MAXN][MAXN]; // indicate whether there is an infinite edge from customer i to j

inline void add(int u, int v, int cap)
{
	G[m] = edge(u, v, cap, 0, head[u]);
	head[u] = m;
	m++;
	G[m] = edge(v, u, 0, 0, head[v]);
	head[v] = m;
	m++;
}

void initG()
{
	memset(head, -1, sizeof(head));
	m = 0;
	memset(exist, 0, sizeof(exist));
	for(int i=1; i<=M; i++) {
		add(source, q[i][0], pigh[i]); // edge from source to the first customer of pighouse No.i
		for(int j=0; j<cnt[i]-1; j++)
			if(!exist[q[i][j]][q[i][j+1]]) {
				add(q[i][j], q[i][j+1], INF); // INF edge from customer No.j to No.(j+1)
				exist[q[i][j]][q[i][j+1]] = true;
			}
	}
	for(int i=1; i<=N; i++)
		add(i, sink, cap[i]);
}

// Dinic algorithm

bool Dinic_BFS()
{
	bool vis[MAXN];
	memset(vis, 0, sizeof(vis));
	queue<int> Q;
	Q.push(source);
	d[source] = 0;
	vis[source] = true;
	while(!Q.empty()) {
		int u = Q.front(); Q.pop();
		for(int i=head[u]; i!=-1; i=G[i].next) {
			edge &e = G[i];
			if(!vis[e.v] && e.cap > e.flow) {
				vis[e.v] = true;
				d[e.v] = d[u] + 1;
				Q.push(e.v);
			}
		}
	}
	return vis[sink]; // not connected if sink is not visited
}

// f is the maximum possible flow from source to u
// if u == sink, then DFS will return the maximum flow from source to sink
int Dinic_DFS(int u, int f)
{
	if(u == sink || f == 0) return f;
	int result = 0;
	for(int i=head[u]; i!=-1 && result < f; i=G[i].next) {
		edge &e = G[i];
		int temp = min(f-result, e.cap-e.flow);
		// if v is deeper than u and there exists an augmenting path 
		if(d[u] == d[e.v]-1 && e.cap > e.flow) {
			temp = Dinic_DFS(e.v, temp);
			e.flow = e.flow + temp; // increase flow
			G[i^1].flow = G[i^1].flow - temp; // decrease flow of backward edge
			result = result + temp;
		}
	}
	if(result == 0) d[u] = -2;
	return result;
}

int Dinic()
{
	int flow = 0;
	while(Dinic_BFS())
		while(1) {
			int val = Dinic_DFS(source, INF);
			if(val == 0) break;
			flow += val;
		}

	return flow;
}

int main()
{
	while(cin >> M >> N) {
		for(int i=1; i<=M; i++)
			cin >> pigh[i];
		memset(cnt, 0, sizeof(cnt));
		for(int i=1; i<=N; i++) {
			int A;
			cin >> A;
			for(int j=0; j<A; j++) {
				int key;
				cin >> key;
				q[key][cnt[key]] = i; // add customer No.i into the queue of pighouse No.key
				cnt[key]++;
			}
			cin >> cap[i];
		}
		initG();
		/*for(int i=0; i<m; i++)
			cout << G[i].u << ' ' << G[i].v << ' ' << G[i].cap << endl;*/
		cout << Dinic() << endl;
	}
	return 0;
}
/*
Mirko works on a pig farm that consists of M locked pig-houses and Mirko can't unlock any pighouse because he doesn't have the keys. Customers come to the farm one after another. Each of them has keys to some pig-houses and wants to buy a certain number of pigs.
All data concerning customers planning to visit the farm on that particular day are available to Mirko early in the morning so that he can make a sales-plan in order to maximize the number of pigs sold.
More precisely, the procedure is as following: the customer arrives, opens all pig-houses to which he has the key, Mirko sells a certain number of pigs from all the unlocked pig-houses to him, and, if Mirko wants, he can redistribute the remaining pigs across the unlocked pig-houses.
An unlimited number of pigs can be placed in every pig-house.
Write a program that will find the maximum number of pigs that he can sell on that day.
*/