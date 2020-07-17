
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
struct point {
	int x, y;
	int val;
	int id;
	point(int x, int y): x(x), y(y) {}
	point() {}
} p[4005];
int b1[2005];
int n, m;
inline double operator * (const point&a, const point&b) {
	return a.x * b.y - a.y * b.x;
}
inline point operator - (const point &a, const point &b) {
	return point(a.x - b.x, a.y - b.y);
}
inline double getdis(const point &a, const point &b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
inline bool cmp1(const point &a, const point &b) {
	return	(a - p[0]) * (b - p[0]) == 0 ? getdis(p[0], a) < getdis(p[0], b) :  (a - p[0]) * (b - p[0]) > 0;
}
int a, b;
int f[2005][2005];
struct node *null;
struct node {
	node *lc, *rc;
	int siz, sum, val, rank, id;
	node(int val = 0, int id = 0): val(val), rank(rand()), sum(val), siz(1), lc(null), rc(null), id(id) {}
	inline void maintain() {
		siz = lc->siz + rc->siz + 1;
		sum = lc->sum + rc->sum + val;
	}
} pool[4005], *rt;
int pooltop;
int mark[2005];
inline node *newnode(int v, int id) {
	node *x = &pool[pooltop++];
	*x = node(v, id);
	return x;
}
inline node *merge(node *x, node *y) {
	if (x == null) return y;
	if (y == null) return x;
	if (x->rank < y->rank) {
		x->rc = merge(x->rc, y);
		x->maintain();
		return x;
	} else {
		y->lc = merge(x, y->lc);
		y->maintain();
		return y;
	}
}
typedef pair<node *, node *> Pair;
inline Pair split(node *x, int k) {
	if (x == null) return make_pair(null, null);
	Pair t;
	if (x->lc->siz >= k) {
		t = split(x->lc, k);
		x->lc = t.second;
		t.second = x;
	} else {
		t = split(x->rc, k - x->lc->siz - 1);
		x->rc = t.first;
		t.first = x;
	}
	x->maintain();
	return t;
}
inline int getrank(node *x) {
	int ans = 0;
	while (x != null) {
		if ((p[b] - p[a])  * (p[x->id] - p[a]) > 0) {
			x = x->lc;
		} else {
			ans += x->lc->siz + 1;
			x = x->rc;
		}
	}
	return ans;
}
inline int insert(int v, int id) {
	node *x = newnode(v, id);
	int rank = getrank(rt), ret;
	Pair t = split(rt, rank);
	ret = t.first->sum;
	rt = merge(merge(t.first, x), t.second);
	return ret;
}
inline void init() {
	null = newnode(0, 0);
	null->siz = 0;
	null->lc = null->rc = null;
}
int main () {

	p[0].x = -12345, p[0].y = -12345;
	R(n), R(m);
	int x, y;
	for (int i = 1; i <= n; ++i) {
		R(x), R(y);
		p[i] = point(x, y);
		p[i].id = i;
		p[i].val = 0;
	}
	int v;
	for (int i = 1;  i <= m; ++i) {
		R(x), R(y), R(v);
		p[i + n] = point(x, y);
		p[i + n].val = v;
		p[i + n].id = i + n;
	}
	sort(p + 1, p + n + m + 1, cmp1);
	for (int i = 1; i <= n + m; i++) {
		//	printf("p[%d].x = %d, p[%d].y = %d\n", i, p[i].x, i, p[i].y);
		mark[p[i].id] = i;
	}
	int temp;
	for (a = 1; a < n + m; ++a) {
		memset(pool, 0, sizeof(pool));
		pooltop = 0;
		init();
		rt = null;
		for (b = a + 1; b <= n + m; ++b) {
			temp = insert(p[b].val, b);
			f[a][b] = f[b][a] = temp;
			//		printf("f[%d][%d] = %d\n", a, b, f[a][b]);
		}
	}
	int q;
	R(q);
	int k, ans = 0;
	for (int i = 1; i <= q; ++i) {
		R(k);
		ans = 0;
		for (int j = 1; j <= k; ++j) {
			R(b1[j]);
			b1[j] = mark[b1[j]];
		}
		b1[++k] = b1[1];
		for (int j = 1; j < k; ++j) {
			if ((p[b1[j]] - p[0]) * (p[b1[j + 1]] - p[0]) < 0) {
				ans += f[b1[j]][b1[j + 1]];
			} else ans -= f[b1[j]][b1[j + 1]];
		}
		printf("%d\n", abs(ans));
	}
	return 0;
}
