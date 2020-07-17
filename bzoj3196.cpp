
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
	if (p)v = -v;
}
struct node *null;
struct node {

	int rank;
	node *lc, *rc;
	int key, siz;
	node(int key = 0) : lc(null), rc(null), key(key), siz(1), rank(rand()) {}
	inline void maintain() {
		siz = lc->siz + rc->siz + 1;
	}
} pool[6000005], *rt[200005];
int pooltop;
int a[100005];
inline node* newnode(int k) {
	node *x = &pool[pooltop++];
	*x = node(k);
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
int n;
typedef pair<node *, node *> Pair;
inline Pair split(node *x, int k) {
	if (x == null) return make_pair(null, null);
	Pair  t;
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
inline int getrank(node *x, int k) {
	int ans = 0;
	while (x != null) {
		if (k <= x->key) {
			x = x->lc;
		} else {
			ans = ans + x->lc->siz + 1;
			x = x->rc;
		}
	}
	return ans;
}
inline void insert(node *&x, int k) {
	if (!x) {
		x = newnode(k);
		return;
	}
	int rank = getrank(x, k);
	Pair t = split(x, rank);
	node *y = newnode(k);
	x = merge(merge(t.first, y), t.second);
}
inline void build(int k, int l, int r, int pos, int v) {
	insert(rt[k], v);
	if (l == r) return;
	int mid = l + r >> 1;
	if (pos <= mid) build(k << 1, l, mid, pos, v);
	else build(k << 1 | 1, mid + 1, r, pos, v);
}
inline int getpaiming (int k , int ql, int qr, int l, int r, int v) {
	if (l >= ql && r <= qr) {
		return getrank(rt[k], v);
	}
	int mid = l + r >> 1, ret = 0;
	if (ql <= mid) ret += getpaiming(k << 1, ql, qr, l, mid, v);
	if (qr > mid)ret += getpaiming(k << 1 | 1, ql, qr, mid + 1, r, v);
	return ret;
}

inline int getnum (int ql, int qr, int pos) {
	int l = 0, r = 100000005, mid, temp;
	while (l < r - 1) {
		mid = l + r >> 1;
		temp = getpaiming(1, ql, qr, 1, n, mid) + 1;
		if (temp <= pos) l = mid;
		else r = mid;
	}
	return l;
}

inline void erase(node *&x, int k) {
	int rank = getrank(x, k);
	Pair t1 = split(x, rank), t2 = split(t1.second, 1);
	x = merge(t1.first, t2.second);
}
inline void gai(node *&x, int k, int v) {
	if (x == null) return;
	erase(x, a[k]);
	insert(x, v);
}
inline void modify(int k, int l, int r, int pos, int v) {
	gai(rt[k], pos, v);
	if (l == r) {
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid) modify(k << 1, l, mid, pos, v);
	else modify(k << 1 | 1, mid + 1, r, pos, v);
}
inline int getpre(node *x, int k) {
	int ans = -INT_MAX;
	while (x!=null) {
		if (x->key < k) ans = max(ans, x->key), x = x->rc;
		else x = x->lc;
	}
	return ans;
}
inline int getbefore (int k, int ql, int qr, int l , int r, int v) {
	if (l >= ql && r <= qr) {
		return getpre(rt[k], v);
	}
	int mid = l + r >> 1;
	int ret = -INT_MAX;
	if (ql <= mid) {
		ret = max(ret, getbefore(k << 1, ql, qr, l, mid, v));
	} if (qr > mid) {
		ret = max(ret, getbefore(k << 1 | 1, ql, qr, mid + 1, r, v));
	}
	return ret;
}
inline int getnxt(node *x, int k) {
	int ans = INT_MAX;
	while (x!=null) {
		if (x->key > k) ans = min(ans, x->key), x = x->lc;
		else x = x->rc;
	}
	return ans;
}
inline int getafter (int k, int ql, int qr, int l , int r, int v) {
	if (l >= ql && r <= qr) {
		return getnxt(rt[k], v);
	}
	int mid = l + r >> 1;
	int ret = INT_MAX;
	if (ql <= mid) {
		ret = min(ret, getafter(k << 1, ql, qr, l, mid, v));
	} if (qr > mid) {
		ret = min(ret, getafter(k << 1 | 1, ql, qr, mid + 1, r, v));
	}
	return ret;
}
inline void init() {
	null = newnode(-INT_MAX);
	null->lc = null->rc = null;
	null->siz = 0;
}
int main () {
	init();
	int  m;
	int x;
	R(n), R(m);
	for (int i = 1; i <= n; ++i) {
		R(x);
		a[i] = x;
		build(1, 1, n, i, x);
	}
	int kind, l, r;
	for (int i = 1; i <= m; ++i) {
		R(kind);
		switch (kind) {
		case 1: R(l), R(r), R(x);
			printf("%d\n", getpaiming(1, l, r, 1, n, x) + 1);
			break;
		case 2:	R(l), R(r), R(x);
			printf("%d\n", getnum(l, r, x) );
			break;
		case 3: R(l), R(x);
			modify(1, 1, n, l, x);
			a[l] = x;
			break;
		case 4:
			R(l), R(r), R(x);
			printf("%d\n", getbefore(1, l, r, 1, n, x));
			break;
		case 5:
			R(l), R(r), R(x);
			printf("%d\n", getafter(1, l, r, 1, n, x));
			break;
		}
	}
	return 0;
}
