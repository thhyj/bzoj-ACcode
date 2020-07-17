
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
std::vector<node> q[200005];
inline void create(int x, int y, int z) {
	q[x].push_back(node(y, z));
	q[y].push_back(node(x, z));
}
int n;
int siz[200005], rt, dis[200005], dep[200005], d[200005];
bool vis[200005];
long long ans, g[200005][2], f[200005][2], t[200005];
const int inf = 2100000000;
int mxdep, mxdp;
int sum;
inline void findrt(int x, int f) {
	node *p;
	siz[x] = 1, d[x] = 0;
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
inline void getdis(int x, int  fa) {
	node *p;
	mxdep = max(mxdep, dep[x]);
	if (t[dis[x]]) f[dis[x]][1]++; else f[dis[x]][0]++;
	t[dis[x]]++;
	for (int i = 0; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (p->to != fa && (!vis[p->to])) {
			dis[p->to] = dis[x] + p->length;
			dep[p->to] = dep[x] + 1;
			getdis(p->to, x);
		}
	}
	t[dis[x]]--;
}
inline void solve(int x) {
	vis[x] = 1;
	g[n][0] = 1;
	mxdp = 0;
	node *p;
	for (int i = 0; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (!vis[p->to]) {
			dis[p->to] = n + p->length;
			dep[p->to] =  mxdep = 1;
			getdis(p->to, x);
			mxdp = max(mxdp, mxdep);
		//	cerr<<"mxdp="<<mxdp<<'\n';
			ans += f[n][0] * (g[n][0] - 1);
			for (int j = -mxdep; j <= mxdep; ++j) {
				ans += f[n - j][0] * g[n + j][1] + f[n - j][1] * g[n + j][0] + f[n - j][1] * g[n + j][1];
			}
			for (int j = n - mxdep; j <= n + mxdep; ++j) {
				g[j][0] += f[j][0];
				g[j][1] += f[j][1];
				f[j][0] = f[j][1] = 0;
			}
		}
	}
	for (int j = n - mxdp; j <= n + mxdp; ++j) {
		g[j][0] = g[j][1] = 0;
	}
	for (int i = 0; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (!vis[p->to]) {
			rt = 0;
			sum = siz[p->to];
			findrt(p->to, 0);
	//		printf("rt=%d\n",rt);
			solve(rt);
		}
	}
}
int main () {
//	freopen("cckk.in","r",stdin);
//	freopen("cckk.out","w",stdout);
	R(n);
	int x, y, z;
	for (int i = 1; i < n; ++i) {
		R(x), R(y), R(z);
		z ? create(x, y, 1) : create(x, y, -1);
	}
	rt = 0;
	sum = n;
	d[0] = inf;
	findrt(1, 0);
	solve(rt);
	cout<<ans<<'\n';
	return 0;
}
