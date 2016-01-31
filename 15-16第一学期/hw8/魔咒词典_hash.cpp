#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 200005;
const int MAXL = 85;
const int SEED = 31;
const int MOD = 100007;

struct node {
	char s[MAXL];
	node *next;
};

node a[MAXN]; // store the nodes of the linked list
node *cnt; // indicate the number of items in a 
node *head[MOD]; // the actual hash table, the head of the linked list

unsigned long long hashval(const char *str)
{
	unsigned long long result = 0;
	while (*str != '\0') {
		result = result * SEED + *str;
		str++;
	}
	return result % MOD;
}

int BKDR_hash(const char *s)
{
	int val = hashval(s);
	// cout << s << ' ' << val << endl;
	node *p = head[val];
	while (p != NULL) {
		if (strcmp(p->s, s) == 0)
			return p - a;
		else
			p = p->next;
	}
	strcpy(cnt->s, s);
	cnt->next = head[val]; // insert the node at the beginning of head[val]
	head[val] = cnt;
	cnt++;
	return cnt - a - 1;
}

// return the position of s in a
int find(const char *s)
{
	int val = hashval(s);
	// cout << s << ' ' << val << endl;
	node *p = head[val];
	while (p != NULL) {
		if (strcmp(p->s, s) == 0)
			return p - a;
		else
			p = p->next;
	}
	return -1;
}

int main()
{
	// freopen("input.in", "r", stdin);
	char s[MAXL * 2], temp[MAXL];
	memset(a, 0, sizeof(a));
	cnt = a; // reset to the beginning of a
	memset(head, 0, sizeof(head));
	while (true) {
		cin.getline(s, sizeof(s));
		if (s[0] == '@') break;
		int i = 0, j = 0;
		while (s[i] != ']') {
			temp[j] = s[i];
			i++, j++;
		}
		temp[j] = '\0';
		strcat(temp, "]");
		BKDR_hash(temp); // hash the first part
		j = 0;
		i += 2;
		while (s[i] != '\0') {
			temp[j] = s[i];
			i++, j++;
		}
		temp[j] = '\0';
		BKDR_hash(temp); // hash the second part
	}
	int N;
	cin >> N;
	getchar();
	for (int i = 0; i < N; i++) {
		cin.getline(s, sizeof(s));
		int val = find(s);
		if (val == -1) // not found
			cout << "what?" << endl;
		else {
			char *p = a[val ^ 1].s; // find the other part of the dictionary entry
			if (p[0] != '[')
				cout << p << endl;
			else {
				for (int j = 1; p[j] != ']'; j++)
					cout << p[j];
				cout << endl;
			}
		}
	}
	return 0;
}

/*
[a] b
[c] d e
[f g] h i
@END@
7
b
[c]
d e
[f g]
h i
[j]
k

哈利波特在魔法学校的必修课之一就是学习魔咒。据说魔法世界有100000种不同的魔咒，哈利很难全部记住，但是为了对抗强敌，他必须在危急时刻能够调用任何一个需要的魔咒，所以他需要你的帮助。

给你一部魔咒词典。当哈利听到一个魔咒时，你的程序必须告诉他那个魔咒的功能；当哈利需要某个功能但不知道该用什么魔咒时，你的程序要替他找到相应的魔咒。如果他要的魔咒不在词典中，就输出“what?”
*/