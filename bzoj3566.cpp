
#include <bits/stdc++.h>
using namespace std;
inline void R  (int &v) {
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
int n;
struct node {
	int to;
	double gailv;
	node(int to, double gailv): to(to), gailv(gailv) {}
};
vector<node>q[5000005];
inline void create(int x, int y, double gailv) {
	q[x].push_back(node(y, gailv));
	q[y].push_back(node(x, gailv));
}
double gailv[5000005], g[5000005], f[5000005];
inline double merge(double a, double b) {
	return a + b - a * b;
}
const double eps = 1e-9;
inline double split(double a, double b) {
	if (1 - b < eps && 1 - b > -eps) return 1;
	return (a - b) / (1 - b);
}
inline void dfs1(int x, int fa) {
	g[x] = gailv[x];
	node *p;
	for (int i = 0; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (p->to == fa) continue;
		dfs1(p->to, x);
		g[x] = merge(g[x], g[p->to] * p->gailv);
	}
}
inline void dfs2(int x, int fa) {
	node *p;
	for (int i = 0; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (p->to == fa) continue;
		f[p->to] = merge(g[p->to], split(f[x], g[p->to] * p->gailv) * p->gailv);
		dfs2(p->to, x);
	}
}
int main () {
	int n;
	int x, y;
	double z;
	R(n);
	for (int i = 1; i < n; ++i) {
		R(x), R(y);
		scanf("%lf", &z);
		create(x, y, z/100.0);
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%lf", &gailv[i]);
		gailv[i]/=100.0;
	}
	dfs1(1, 1);
	f[1] = g[1];
	dfs2(1, 1);
	double ans = 0;
	for (int i = 1; i <= n; ++i) {
//		printf("f[%d] = %0.6f\n",i,f[i]);
		ans += f[i];
	}
	printf("%0.6f\n", ans);
	return 0;
}
