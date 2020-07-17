
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
	int siz, dis, v;
	node(int v = 0): v(v), siz(1), dis(0), lc(null), rc(null) {
	}
} pool[1000005], *rt[1000005];
int l[1000005], r[1000005];
int pooltop;
int p;
inline node * newnode(int v) {
	node *x = &pool[pooltop++];
	*x = node(v);
	return x;
}
inline node *merge(node *x, node *y) {
	if (x == null) return y;
	if (y == null) return x;
	if (x->v < y->v) swap(x, y);
	x->rc = merge(x->rc, y);
	x->siz = x->lc->siz + x->rc->siz + 1;
	if (x->lc->dis < x->rc->dis) swap(x->lc, x->rc);
	x->dis = x->rc->dis + 1;
	return x;
}
int a[1000005];
int n;
int main () {
	null = newnode(0);
	null->lc = null->rc = null;
	null->siz = 0, null->dis = -1;
	R(n);
	rt[0] = null;
	for (int i = 1; i <= n; ++i) {
		R(a[i]);
		a[i] -= i;
	}
	for (int i = 1; i <= n; ++i) {
		rt[++p] = newnode(a[i]);
		l[p] = r[p] = i;
	//	printf("rt[%d]->v = %d, rt[%d]->v = %d\n", p, rt[p]->v, p - 1, rt[p - 1]->v );
		while (p - 1 && rt[p]->v < rt[p - 1]->v) {
		//	printf("rt[%d]->v = %d, rt[%d]->v = %d\n", p, rt[p]->v, p - 1, rt[p - 1]->v );
			rt[p - 1] = merge(rt[p - 1], rt[p]);
			--p;
			r[p] = i;
			while (rt[p]->siz > (r[p] - l[p] + 2) / 2) rt[p] = merge(rt[p]->lc, rt[p]->rc);
		}
	}
	long long ans = 0;
	for (int i = 1; i <= p; i++) {
	//	printf("rt[%d]->v = %d\n", i, rt[i]->v );
		for (int j = l[i]; j <= r[i]; j++) ans += abs(a[j] - rt[i]->v);
	}
	cout << ans;

}
