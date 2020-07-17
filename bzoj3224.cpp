
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
	int key, rank, siz;
	node(int key = 0): lc(null), rc(null), key(key), rank(rand()), siz(1) {}
	inline void maintain() {
		siz = lc->siz + rc->siz + 1;
	}
} data[100005], *pool[100005], *rt;

int pooltop, datatop;
int cnt;
inline node *newnode(int v) {
	node *u;
	if (pooltop) u = pool[pooltop--];
	else u = &data[datatop++];
	*u = node(v);
	return u;
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

typedef pair<node*, node*> Pair;
inline Pair split(node *x, int k) {
	if (x == null) return make_pair(null, null);
	pair<node*, node*>t;
	if (x->lc->siz >= k) {
		t = split(x->lc, k);
		x->lc = t.second, t.second = x;
	} else {
		t = split(x->rc, k - x->lc->siz - 1);
		x->rc = t.first, t.first = x;
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
inline void recycle(node *x) {
	pool[++pooltop] = x;
}
inline void clear(node *x) {
	if (x == null) {return;}
	clear(x->lc), clear(x->rc);
	recycle(x);
}
inline void del(int k) {
	int rank = getrank(rt, k);
	Pair t1 = split(rt, rank), t2 = split(t1.second, 1);
	rt = merge(t1.first, t2.second);
	clear(t2.first);
}
inline node* getnum(int k) {
	Pair t1 = split(rt, k - 1),
	     t2 = split(t1.second, 1);
	node *ret = t2.first;
	rt = merge(merge(t1.first, ret), t2.second);
	return ret;
}
inline void init() {
	null = newnode(-INT_MAX);
	null->siz = 0;
}
inline int getpre(node *x, int k) {
	int rank = getrank(x, k);
	Pair t = split(x, rank - 1), t2 = split(t.second, 1);
	int ret = t2.first->key;
	x = merge(merge(t.first, t2.first), t2.second);
	return ret;
}
inline int getnxt(node *x, int k) {
	int rank = getrank(x, k + 1);
	Pair t = split(x, rank), t2 = split(t.second, 1);
	int ret = t2.first->key;
	x = merge(merge(t.first, t2.first), t2.second);
	return ret;
}
int main () {
//	freopen("in.in","r",stdin);
	int n;
	R(n);
	//for (int i = 1 ; i <= n; ++i)data[i] = node(-INT_MAX);
	init();
	int kind;
	int x;
	rt = null;
	for (int i = 1; i <= n; ++i) {
		R(kind);
		R(x);
		switch (kind) {
		case 1:
			insert(x);
			break;
		case 2:
			del(x);
			break;
		case 3:
			printf("%d\n", getrank(rt, x) + 1);
			break;
		case 4:
			printf("%d\n", getnum(x)->key);
			break;
		case 5:
			printf("%d\n", getpre(rt, x));
			break;
		case 6:
			printf("%d\n", getnxt(rt, x));
		}
	}
	return 0;
}
