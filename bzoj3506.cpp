
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
		v = (v + (v << 2) << 1) + (ch ^ '0');
		ch = getchar();
	}
	if (p)v = -v;
}
struct node *null;
struct node {
	int key, siz, rank;
	node *lc, *rc;
	bool rev;
	int mi;
	node(int key = 0): key(key), siz(1), lc(null), rc(null), rev(0), rank(rand()), mi(key) {}
	inline void maintain() {
		siz = lc->siz + rc->siz + 1;
		mi = min(key, min(lc->mi, rc->mi));

	}
	inline void reverse() {
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
int pooltop;
inline node* newnode(int k) {
	node *x = &pool[pooltop++];
	*x = node(k);
	return x;
}
inline node * merge(node *x, node *y) {
	if (x == null) return y;
	if (y == null) return x;
	x->pushdown(); y->pushdown();
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
	x->pushdown();
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
inline node * getnum(int k) {
	cout << "k=" << k << '\n';
	node *x = rt;
	while (1) {
		x->pushdown();
		if (x->lc->siz > k) {
			x = x->lc;
		} else {
			if (x->lc->siz < k) {
				k -= x->lc->siz + 1;
				x = x->rc;
			} else {
//				puts("233");
				return x;
			}
		}
	}
}
inline int getrank(node *x, int k) {
	int ans = 0;
	while (x != null) {
		if (k <= x->key) x = x->lc;
		else ans += x->lc->siz + 1, x = x->rc;
	}
	return ans;
}
inline int findmin(node *x) {
	int ans = 0;
	while (x != null) {
		x->pushdown();
		if (x->lc->mi == x->mi) {
			x = x->lc;
			continue;
		}
		if (x->rc->mi == x->mi) {
			ans += x->lc->siz + 1;
			x = x->rc;
			continue;
		}
		ans += x->lc->siz + 1;
		return ans;
	}
}
inline int getmin(int l, int r) {
	Pair t1 = split(rt, l - 1), t2 = split(t1.second, r - l + 1);
//	printf("min = %d\n", t2.first->mi);
	int x = findmin(t2.first) + t1.first->siz;
	rt = merge(merge(t1.first, t2.first), t2.second);
	return x;
}
inline void rever(int l, int r) {
	Pair t1 = split(rt, l - 1), t2 = split(t1.second, r - l + 1);
	t2.first->reverse();
	rt = merge(merge(t1.first, t2.first), t2.second);
}
inline void init() {
	null = newnode(INT_MAX);
	null->siz = 0;
	null->lc = null->rc = null;
}
int pos[1000005], num[1000005];
inline node* build(int n) {
	static node *st[1000005], *pre;
	node *x;
	int top = 0, t;
	for (int i = 1; i <= n; ++i ) {
		pre = null;
		x = newnode(num[i]);
		while (top && st[top]->rank > x->rank) {
			pre = st[top];
			pre->maintain();
			st[top--] = null;
		}
		if (top) st[top]->rc = x;
		x->lc = pre;
		st[++top] = x;
	}
	while (top) st[top--]->maintain();
	return st[1];
}
inline void bianli(node *x) {
	if (x == null) return;
	x->pushdown();
	bianli(x->lc);
	printf("%d ", x->key);
	bianli(x->rc);
}
bool cmp ( int i , int j ) {
	if ( num[i] == num[j] ) return i < j ;
	return num[i] < num[j] ;
}
int main () {
//	freopen("in.in","r",stdin);
	init();
//	cout<<null->lc<<' '<<null->rc;
	int n;
	R(n);
	for (int i = 1; i <= n; ++i) {
		R(num[i]);
		pos[i] = i;
	}
	sort(pos + 1, pos + n + 1, cmp);
	for (int i = 1; i <= n; ++i) {
		num[pos[i]] = i;
	}
	rt = build(n);
	int temp;
	for (int i = 1; i < n; ++i) {
		printf("%d ", temp = getmin(i, n));
		rever(i, temp);
	}
	printf("%d\n", n);
	return 0;
}
