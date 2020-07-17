
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
inline void R(double &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
		ch = getchar();
		if (ch == '-') p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = v * 10 + (ch^'0');
		ch = getchar();
	}
	if (p) v = -v;
}
double a[10005], b[10005], z[10005];
int x[10005], y[10005];
struct node {
	double length;
	int to;
	node (int to , double length) : to(to), length(length) {}
	node() {}
};
int n, m;
vector<node>q[1005];
inline void create(int x, int y, double z) {
	q[x].push_back(node(y, z));
}
inline void build(double mid) {
	memset(q, 0, sizeof(q));
	for (int i = 1; i <= m; ++i) {
		create(x[i], y[i],  mid * z[i] - a[x[i]]);
	}
}
bool vis[1005];
double dis[1005];
bool pd;
inline void spfa(int x) {
	node *p;
	vis[x] = 1;
	for (int i = 0; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (dis[p->to] > dis[x] + p->length) {
			if (vis[p->to]) {
				pd = 1;
				return;
			}
			dis[p->to] = dis[x] + p->length;
			spfa(p->to);
		}
	}
	vis[x] = 0;
}
inline bool check(double mid) {
	build(mid);
	pd = 0;
	for (int i = 1; i <= n; ++i) {
		memset(vis, 0, sizeof(vis));
		memset(dis, 0 , sizeof(dis));
		spfa(i);
		if (pd) return 1;
	}
	return 0;
}
int main() {
	R(n), R(m);
	for (int i = 1; i <= n; ++i) {
		R(a[i]);
	}
	for (int i = 1; i <= m; ++i) {
		R(x[i]), R(y[i]), R(z[i]);
	}
	double l = 0, r = 10000, mid;
	for (int i = 1; i <= 30; ++i) {
		mid = (l + r) / 2;
		if (check(mid)) {
			l = mid;
		} else r = mid;
	}
	printf("%0.2lf", mid);
}
