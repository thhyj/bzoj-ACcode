
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
struct node *null;
struct node {
	node *lc, *rc;
	bool rev;
	int siz, key, rank;
	node(int key = 0): rev(0), key(key), rank(rand()), siz(1), lc(null), rc(null) {}
	inline void maintain() {
		siz = lc->siz + rc->siz + 1;
	}
	inline void reverse() {
		if (this == null) return;
		rev ^= 1;
		swap(lc, rc);
	}
	inline void pushdown() {
		if (this == null) return;
		if (rev) {
			lc->reverse(), rc->reverse();
			rev = 0;
		}
	}
} pool[1000005], *rt;
int tot;
inline node* newnode(int v) {
	node *x = &pool[tot++];
	*x = node(v);
	return x;
}
inline node *merge(node *x, node *y) {
	if (x == null) return y;
	if (y == null) return x;
	if (x->rank < y->rank) {
		x->pushdown();
		x->rc = merge(x->rc, y);
		x->maintain();
		return x;
	} else {
		y->pushdown();
		y->lc = merge(x, y->lc);
		y->maintain();
		return y;
	}
}
typedef pair<node*, node*> Pair;
inline Pair split (node *x, int k) {
	if (x == null) return make_pair(null, null);
	x->pushdown();
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
		(k <= x->key) ? (x = x->lc) : (ans += x->lc->siz + 1, x = x->rc);
	}
	return ans;
}
inline void insert(int k) {
	node *x = newnode(k);
	int rank = getrank(rt, k);
	Pair t1 = split(rt, rank);
	rt = merge(merge(t1.first, x), t1.second);
}
inline void modify(int l, int r) {
	Pair t1 = split(rt, l - 1), t2 = split(t1.second, r - l + 1);
	t2.first->reverse();
	rt = merge(merge(t1.first, t2.first), t2.second);
}
int n, m;
inline void getans(node *x) {
	if (x == null) return;
	x->pushdown();
	getans(x->lc);
	printf("%d ", x->key);
	getans(x->rc);
}
inline void init() {
	null = newnode(-INT_MAX);
	null->siz = 0;
	rt = null;
}

inline node* build(int n) {
	static node  *st[100005], *pre = null;
	int top = 0;
	node *x;
	for (int i = 1; i <= n; ++i) {
		x = newnode(i);
		pre = null;
		while (top && st[top]->rank > x->rank) {
			pre = st[top];
			pre -> maintain();
			st[top--] = null;
		}
		if(top) st[top]->rc = x;
		x->lc = pre;
		st[++top] = x;
	}
	while(top) st[top--]->maintain();
	return st[1];
}
int main() {
//	freopen("sph.in","r",stdin);
//	freopen("sph.out","w",stdout);
	init();
	R(n), R(m);
	int x;
	rt = build(n);
//	cout << "tot=" << tot << '\n';
	int l, r;
	for (int i = 1; i <= m; ++i) {
		R(l), R(r);
		modify(l, r);
	}
	getans(rt);
}
