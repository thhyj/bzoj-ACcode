
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
	int rank, key, ma;
	node *lc, *rc;
	int siz;
	node (int key = 0) : rank(rand()), key(key), ma(key), lc(null), rc(null), siz(1) {}
	inline void maintain() {
		siz = lc->siz + rc->siz + 1;
		ma = max(key, max(lc->ma, rc->ma));
	}
} pool[1000005], *rt;
int pooltop;
inline node *newnode(int v) {
	node *x = &pool[pooltop++];
	*x = node(v);
	return x;
}
inline void init() {
	null = newnode(-INT_MAX);
	null->lc = null->rc = null;
	null->ma = null->key = 0;
	null->siz = 0;
}
inline node *merge(node *x, node* y) {
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
typedef pair<node*, node*> Pair;
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
inline int getrank(node *x, int k) {
	int ans = 0;
	while (x != null) {
		if (k <= x->key) {
			x = x->lc;
		} else {
			ans += x->lc->siz + 1;
			x = x->rc;
		}
	}
	return ans;
}
inline void insert(int v, int pos) {
	Pair t1 = split(rt, pos);
	node *x = newnode(t1.first->ma + 1);
	rt = merge(merge(t1.first, x), t1.second);
}
int main () {
	init();
	rt = null;
	int n;
	int x;
	R(n);
	for(int i = 1; i <= n; ++i) {
		R(x);
		insert(i, x);
		printf("%d\n", rt->ma);
	}
	return 0;
}
