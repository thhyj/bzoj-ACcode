
#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <ctime>
using namespace std;
#define MAX 2000010
#define LEFT (pos << 1)
#define RIGHT (pos << 1|1)
inline void R(long long &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
		ch = getchar();
		if (ch == '-')
			p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = (v + (v << 2) << 1) + (ch ^ '0');
		ch = getchar();
	}
	if (p)
		v = -v;
}
inline void R(int &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
		ch = getchar();
		if (ch == '-')
			p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = (v + (v << 2) << 1) + (ch ^ '0');
		ch = getchar();
	}
	if (p)
		v = -v;
}
long long n, en, re;
long long a[1000005];
int tree[MAX << 2];

void BuildTree(int l, int r, int pos)
{
    if(l == r) {
        tree[pos] = l;
        return ;
    }
    int mid = (l + r) >> 1;
    BuildTree(l, mid, LEFT);
    BuildTree(mid + 1, r, RIGHT);
    tree[pos] = a[tree[LEFT]] > a[tree[RIGHT]] ? tree[LEFT]:tree[RIGHT];
}

int Ask(int l, int r, int x, int y, int pos)
{
    if(l == x && y == r)
        return tree[pos];
    int mid = (l + r) >> 1;
    if(y <= mid)    return Ask(l, mid, x, y, LEFT);
    if(x > mid)     return Ask(mid + 1, r, x, y, RIGHT);
    int left = Ask(l, mid, x, mid, LEFT);
    int right = Ask(mid + 1, r, mid + 1, y, RIGHT);
    return a[left] > a[right] ? left:right;
}

long long solve(const long long &l, const long long &r, const long long &s, const long long &e) {
	if (l > r) return 0;
	long long tar= Ask(1, n, l, r, 1);
	long long top,bot;
	long long ret = 0;
		if ((tar - l) * re + s > en) 
			ret += solve(l, tar - 1, s, en),top=en;
			else top=(tar - l) * re + s ;
			if ((r - tar + 1) * re < e) {
				bot=en-((r - tar + 1) * re);
			} else 
				ret+=solve(tar + 1, r, re, e),bot=0;
			return ret+(top-bot)*a[tar];
}
int main() {
	long long T;
	R(T);
	for (long long o = 1; o <= T; ++o)
	{
        memset(a,0,sizeof(a));
		R(en); R(re); R(n);
		for (long long i = 1; i <= n; ++i) {
			R(a[i]);
		}
		   BuildTree(1, n, 1);
		//	cout<<"getmax(1,n)"<<getmax(1,n)<<'\n';
		//cout << solve(1, getmax(1, n) - 1, en, en - re) + solve(getmax(1, n) + 1, n, re, 0) + (long long)a[getmax(1, n)]*(long long)en << '\n';
		cout<<solve(1,n,en,re)<<'\n';
	}
	return 0;
}
