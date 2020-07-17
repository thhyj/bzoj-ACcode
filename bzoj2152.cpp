
#include <bits/stdc++.h>
using namespace std;
inline void R(int &v) {
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
struct node {
	int to, length;
	node (int to, int length): to(to), length(length) {}
	node() {}
};
std::vector<node> q[20005];
inline void create(int x, int y, int z) {
	q[x].push_back(node(y, z));
	q[y].push_back(node(x, z));
}
int n;
int rt, siz[20005], d[20005], dis[20005];
bool vis[20005];
const int inf = 2100000000;
int sum;
inline void findrt(int x, int f) {
	node *p;
	siz[x] = 1;
	d[x] = 0;
	for (int i = 0; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (p->to != f && (!vis[p->to])) {
			findrt(p->to, x);
			siz[x] += siz[p->to];
			d[x] = max(d[x], siz[p->to]);
		}
	}
	d[x] = max(d[x], sum - siz[x]);
	if (d[x] < d[rt]) rt = x;
}
int ans;
int a[4];
inline void getdis(int x, int f) {
	node *p;
	dis[x] %= 3;
	a[dis[x]]++;
	for (int i = 0; i < q[x].size(); ++i) {
		p = &q[x][i];
		if ((p->to != f) && (!vis[p->to])) {
			dis[p->to] = dis[x] + p->length;
			getdis(p->to, x);
		}
	}
}
inline int calc(int x, int now) {
	a[0] = a[1] = a[2] = a[3] = 0;
	dis[x] = now;
	getdis(x, 0);
	int ret = 0;
	ret = 0;
	ret += a[0] * (a[0]);
	ret += a[1] * a[2] * 2;
	return ret;
}
int tot = 0;
inline void solve(int x) {
	vis[x] = 1;
	ans += calc(x, 0);
	node *p;
	for (int i = 0; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (!vis[p->to]) {
			ans -= calc(p->to, p->length % 3);
			rt = 0;
			sum  = siz[p->to];
			findrt(p->to, 0);
		//	printf("rt=%d\n",rt);
			solve(rt);
		}
	}
}
int main () {
//	freopen("cckk.in", "r", stdin);
//	freopen("cckk.out", "w", stdout);

	R(n);
	int x, y , z;
	for (int i = 1; i < n; ++i) {
		R(x), R(y), R(z);
		z %= 3;
		create(x, y, z);
	}
	d[0] = inf;
	sum = n;
	findrt(1, 0);
	solve (rt);
	int GCD = __gcd(ans, n * n);
	printf("%d/%d\n", ans / GCD, n * n / GCD);
}
