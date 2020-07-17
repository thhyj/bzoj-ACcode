
#include <bits/stdc++.h>
using namespace std;
inline void R(int &v) {
	bool p = 0;
	v = 0;
	static char ch ;
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
	bool p = 0;
	v = 0;
	static char ch ;
	do {
		ch = getchar();
		if (ch == '-') p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = v*10+ (ch^'0');
		ch = getchar();
	}
	if (p) v = -v;
}
struct  node {
	int to;
	double length;
	node(int to, double length): to(to), length(length) {}
	node() {}
};
std::vector<node> q[3005];
inline void create(int x, int y, double z) {
	q[x].push_back(node(y, z));
}
int x[10005], y[10005];
double z[10005];
int m;
	int n;
inline void build(double mid) {
	for(int i =1 ;i<=n;++i)
	q[i].clear();
	for (int i = 1; i <= m; ++i) {
		create(x[i], y[i], z[i] - mid);
	}
}
bool vis[3005];
bool pd;
double dis[3004];
inline void spfa(int x) {
	node *p;
	vis[x] = 1;
	for (int i = 0; i < q[x].size(); ++i) {
		p = &q[x][i];
		if(dis[p->to] > dis[x] + p->length) {
			if(vis[p->to]) {
				pd = 1;
				return;
			} else {
				dis[p->to] = dis[x] + p->length;
				spfa(p->to);
			}
		}
	}
	vis[x] = 0;
}

inline bool check(double mid) {
	build(mid);
	memset(vis, 0 , sizeof(vis));
	pd = 0;
	for (int i = 1; i <= n; ++i) {
		memset(dis, 0, sizeof(dis));
		spfa(i);
		if (pd) return 1;
	}
	return 0;
}
int main () {
//	freopen("in.in","r",stdin);
	R(n), R(m);
	for (int i = 1; i <= m; ++i) {
		R(x[i]), R(y[i]);
		scanf("%lf",&z[i]);
	}
	double l = -10000000, r = 10000000, mid;
	for (int i = 1; i <= 60; ++i) {
		mid = (l + r) /2;
	//	cout<<"l="<<l<<" r="<<r<<" mid="<<mid<<'\n';
		if (check(mid)) {
			r = mid;
		} else l = mid;
	}
	printf("%0.8lf\n", mid);
	return 0;
}
