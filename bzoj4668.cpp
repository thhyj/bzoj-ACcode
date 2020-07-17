
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
int rank[500005], fa[500005];
int dep[500005];
inline void init(int n) {
	for (int i = 1 ; i <= n; ++i) {
		fa[i] = i;
		dep[i] = 1;
	}
}
int tot = 0;
int num[500005];
inline void hebing(int x, int y) {
	int x1 = x, y1 = y;
	while (fa[x]^x) {
		x = fa[x];
	}
	while (fa[y]^y) {
		y = fa[y];
	}
	++tot;
	if (x ^ y) {
		if (rank[x] < rank[y]) {
			fa[x] = y;
			dep[x] = dep[y] + 1;
			while (x1^x) {
				dep[x1] = dep[y] + dep[x1];
				x1 = fa[x1];
			}
			num[x] = tot;
		} else {
			fa[y] = x;
			num[y] = tot;
			dep[y] = dep[x] + 1;
			while (y1^y) {
				dep[y1] = dep[x] + dep[y1];
				y1 = fa[y1];
			}
			if (rank[x] == rank[y]) {
				rank[x]++;
			}
		}
	}
}
inline void pre(int x) {
	if(fa[x] ^ x) {
		pre(fa[x]);
		dep[x] = dep[fa[x]] + 1;
	} else dep[x] = 1;
}
inline int query(int x, int y) {
	int max1 = 0, max2 = 0;
	pre(x), pre(y);
	if (dep[x] < dep[y]) swap(x, y);
	while (dep[x] > dep[y]) {
		max1 = max(max1, num[x]);
		x = fa[x];
	}
	while (x ^ y) {
		if (x == fa[x] || y == fa[y]) break;
		max1 = max(max1, num[x]);
		max2 = max(max2, num[y]);
		x = fa[x], y = fa[y];
	}
	if (x == y) {
		return max(max1, max2);
	} else return 0;
}

int main () {
	int n, m;
	R(n), R(m);
	init(n);
	int kind, x, y;
	int pre = 0;
	for (int i = 1; i <= m; ++i) {
		R(kind);
		R(x), R(y);
		x ^= pre, y ^= pre;
		//cout << "x=" << x << " y=" << y << '\n';
		if (!kind)
		{ hebing(x, y);}
		else {
			printf("%d\n", pre = query(x, y));
		}
	}
	return 0;
}
