/*
ID: 13182011
PROG: milk2
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <list>
#define ITER list<Time>::iterator

using namespace std;


const int MAXN = 5002;
const int INF = 0x3f3f3f3f;

struct Time {
	int s, e; // start and end time
};

list<Time> l;

void ins(int st, int en)
{
	Time tmp = { st, en };
	if (l.size() == 2) {
		ITER it = l.begin();
		it++;
		l.insert(it, tmp);
	}
	for (ITER i = ++l.begin(); i != l.end(); i++) {
		ITER it = i;
		it--;
		if (st <= (*it).e || st > (*i).e) continue;
		if (st < (*i).s) {
			if (en < (*i).s)
				l.insert(i, tmp);
			else {
				ITER j = i, k = i;
				k++;
				for (; en >= (*k).s; l.erase(j++), k++);
				if (en <= (*j).e)
					(*j).s = st;
				else
					(*j) = { st, en };
			}
		}
		else {
			st = (*i).s;
			ITER j = i, k = i;
			k++;
			for (; en >= (*k).s; l.erase(j++), k++);
			if (en <= (*j).e)
				(*j).s = st;
			else
				(*j) = { st, en };
		}
		break;
	}
}

void print()
{
	for (ITER i = l.begin(); i != l.end(); i++)
		cout << (*i).s << ' ' << (*i).e << endl;
	cout << endl;
}

int main()
{
	ofstream fout("milk2.out");
	ifstream fin("milk2.in");
	int n;
	while (fin >> n) {
		l.clear();
		Time tmp = { -1, -1 };
		l.push_back(tmp);
		tmp = { INF, INF };
		l.push_back(tmp);
		for (int i = 0; i < n; i++) {
			int st, en;
			fin >> st >> en;
			ins(st, en);
		}
		int max = 0;
		ITER i, j;
		for (i = ++l.begin(); (*i).s != INF; i++)
			if (max < (*i).e - (*i).s)
				max = (*i).e - (*i).s;
		fout << max << ' ';
		max = 0;
		i = ++l.begin();
		cout << (*i).s << ' ' << (*i).e << endl;
		j = i, j++;
		for (; (*j).s != INF; i++, j++)
			if (max < (*j).s - (*i).e)
				max = (*j).s - (*i).e;
		fout << max << endl;
	}
	return 0;
}
