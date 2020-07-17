
#include <bits/stdc++.h>
using namespace std;
inline void R (int &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
		ch = getchar();
		if (ch == '-') p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = (v + (v << 2) << 1) + (ch^'0');
		ch = getchar();
	}
	if (p) v = -v;
}
int n, k;
const int inf = 2100000000;
struct node {
	int to, length;
	node(int to, int length) : to(to), length(length) {}
	node() {}
};
std::vector<node> q[40005];
inline void create (int x, int y, int z) {
	q[x].push_back(node(y, z));
	q[y].push_back(node(x, z));
}
int rt;
bool vis[40005];
int siz[40005], d[40005], dis[40005], a[40005];
int sum, ans;
int cnt;
inline int findrt(int x, int f) {
	siz[x] = 1;
	node *p;
	d[x] = 0;
	for (int i = 0 ; i < q[x].size(); ++i) {
		p = &q[x][i];
		if ((!vis[p->to]) && p->to != f) {
			findrt(p->to, x);
			siz[x] += siz[p->to];
			d[x] = max(d[x], siz[p->to]);
		}
	}
	d[x] = max(d[x], sum - siz[x]);
	if (d[x] < d[rt]) rt = x;

}
inline void getdis(int x, int f) {
	a[++cnt] = dis[x];
	node *p;
	for (int i = 0; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (p->to != f && vis[p->to] == 0) {
			dis[p->to] = dis[x] + p->length;
			getdis(p->to, x);
		}
	}
}
inline int calc(int x, int c) {
	cnt = 0;
	dis[x] = c;
	getdis(x, 0);
	sort(a + 1, a + cnt + 1);
	int ret = 0;
	int l = 1, r = cnt;
//	printf("cnt=%d\n", cnt);
//	for (int i = 1; i <= cnt; ++i) {
//		printf("a[%d]=%d\n", i, a[i]);
//	}
	while (l < r) {
		if (a[l] + a[r] <= k) ret += r - l, l++;
		else r--;
	}
	return ret;
}
inline void solve(int x) {
//	printf("x = %d\n",x );
	vis[x] = 1;
	ans += calc(x, 0);
	node *p;
	for (int i = 0 ; i < q[x].size(); ++i) {
		p = &q[x][i];
		if ((!vis[p->to])) {
			ans -= calc(p->to, p->length);
			sum = siz[p->to];
			rt = 0;
			findrt(p->to, 0);
			solve(rt);
		}
	}
}
int main() {
//	freopen("in.in", "r", stdin);
	d[0] = inf;
	R(n);
	int x, y, z;
	for (int i = 1; i < n; ++i) {
		R(x), R(y), R(z);
		create(x, y, z);
	}
	R(k);
	sum = n;
	findrt(1, 0);
	solve(rt);
	printf("%d\n", ans);
}
