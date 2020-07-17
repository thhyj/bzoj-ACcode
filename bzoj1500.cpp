
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
const int inf = INT_MAX;
struct node {
	int qz, hz, key;
	node *lc, *rc;
	bool rev;
	int sum, ma, rank, tag, siz;
	node (int key = 0) : rank(rand()), key(key), rev(0), lc(null), rc(null), tag(inf), siz(1) {
		sum = qz = hz = ma = key;
	}
	inline void maintain() {
		siz = lc->siz + rc->siz + 1;
		sum = lc->sum + rc->sum + key;
		qz = max(lc->qz, lc->sum + key + max(rc->qz, 0));
		hz = max(rc->hz, rc->sum + key + max(lc->hz, 0));
		ma = max(lc->hz, 0) + key + max(rc->qz, 0);
		ma = max(max(lc->ma, rc->ma), ma);
	}
	inline void cover(int t) {
		if (this == null) return;
		key = t; sum = siz * t;
		ma = qz = hz = max(t, sum);
		tag = t;
	}
	inline void reverse() {
		if (this == null) return;
		rev ^= 1;
		swap(lc, rc);
		swap(qz, hz);
	}
	inline void pushdown() {
		if (this == null) return;
		if (tag != inf) {
			lc->cover(tag), rc->cover(tag);
			tag = inf;
		}
		if (rev) {
			lc->reverse(), rc->reverse();
			rev = 0;
		}
	}
} data[500005], *pool[500005], *rt;
int pooltop, datatop;
inline node * newnode(int v) {
	node *x;
	if (pooltop) x = pool[pooltop--];
	else x = &data[datatop++];
	*x = node(v);
	return x;
}
inline void recycle(node *x) {
	pool[++pooltop] = x;
}
inline void clear(node *x) {
	if (x == null) return;
	clear(x->lc), clear(x->rc);
	recycle(x);
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
inline node* build(int tot) {
	static node *st[500005], *pre, *x;
	int top = 0;
	int t;
	for (int i = 1; i <= tot; ++i) {
		R(t);
		pre = null;
		x = newnode(t);
		while (top && st[top]->rank > x->rank) {
			st[top]->maintain();
			pre = st[top];
			st[top--] = null;
		}
		if (top) st[top]->rc = x;
		x->lc = pre;
		st[++top] = x;
	}
	while (top) st[top--]->maintain();
	return st[1];
}
inline void insert(int pos, int tot) {
	node *temp = build(tot);
	Pair t1 = split(rt, pos);
	rt = merge(merge(t1.first, temp), t1.second);
}
inline void del(int pos, int tot) {
	Pair t1 = split(rt, pos - 1), t2 = split(t1.second, tot);
	rt = merge(t1.first, t2.second);
	clear(t2.first);
}
inline void modify(int pos, int tot) {
	int x;
	R(x);
	Pair t1 = split(rt, pos - 1), t2 = split(t1.second, tot);
	t2.first->cover(x);
	merge(merge(t1.first, t2.first), t2.second);
}
inline void rever(int pos, int tot) {
	Pair t1 = split(rt, pos - 1), t2 = split(t1.second, tot);
	t2.first->reverse();
	merge(merge(t1.first, t2.first), t2.second);
}
inline int getsum(int pos, int tot) {
	Pair t1 = split(rt, pos - 1), t2 = split(t1.second, tot);
	int ret;
	ret = t2.first->sum;
	merge(merge(t1.first, t2.first), t2.second);
	return ret;
}
inline void init() {
	null = newnode(-inf);
	null->siz = 0, null->sum = 0;
}
int main () {
	init();
	int n, m;
	R(n), R(m);
	rt = build(n);
	char ch;
	int pos, tot;
	for (int i = 1; i <= m; ++i) {
		do {
			ch = getchar();
		} while (!isupper(ch));
		switch (ch) {
		case 'I':
			R(pos), R(tot);
			insert(pos, tot);
			break;
		case 'D':
			R(pos), R(tot);
			del(pos, tot);
			break;
		case 'M':
			do {
				ch = getchar();
			} while (!isupper(ch));
			do {
				ch = getchar();
			} while (!isupper(ch));
			if (ch == 'K') {
				do {
				ch = getchar();
				} while (ch != '-');
				R(pos), R(tot);
				modify(pos, tot);
			} else {
				ch = getchar();
				ch = getchar();
				ch = getchar();
				ch = getchar();
				printf("%d\n", rt->ma);
			}
			break;
		case 'R':
			R(pos), R(tot);
			rever(pos, tot);
			break;
		case 'G':
			do {
				ch = getchar();
			} while (ch != '-');
			R(pos), R(tot);
			printf("%d\n", getsum(pos, tot));
			break;
		}
	}
	return 0;
}
