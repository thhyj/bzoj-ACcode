
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
struct tree {
	int sum;
	int ls, rs;
} tr[8000005];
inline void updata(int x) {
	tr[x].sum = tr[tr[x].ls].sum + tr[tr[x].rs].sum;
}
int n, m , q;
int h[100005], tot;
int root[100005];
struct wen {
	int a, b, c, id;
} qu[1000005];
inline bool cmp(const wen &a, const wen &b) {
	return a.c < b.c || ((a.c == b.c) && a.id < b.id);
}
inline void build(int &x, int l, int r, int pos) {
	if (!x) x = ++tot;
	tr[x].sum = 1;
	if (l == r) {
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid) build(tr[x].ls, l, mid, pos);
	else build(tr[x].rs, mid + 1, r, pos);
}
inline int merge(int x, int y) {
	if ((!x) || (!y)) {
		return x ^ y;
	}
	if ((!tr[x].ls) && (!tr[x].rs)) {
		tr[x].sum = tr[x].sum + tr[y].sum;
		return x;
	}
	tr[x].ls = merge(tr[x].ls, tr[y].ls), tr[x].rs = merge(tr[x].rs, tr[y].rs);
	tr[x].sum = tr[tr[x].ls].sum + tr[tr[x].rs].sum;
	return x;
}
int ans[500005], a[100005];
inline int getkth(int x, int l, int r, int k) {
	if (l == r) {
		return l;
	}
	int mid = l + r >> 1;
	if (tr[tr[x].ls].sum < k) return getkth(tr[x].rs, mid + 1, r, k - tr[tr[x].ls].sum);
	else return getkth(tr[x].ls, l, mid, k);
}
int fa[100005];
inline int getfather(int x) {
	return fa[x] == x ? x : (fa[x] = getfather(fa[x]));
}
int main () {
//	freopen("in.in", "r", stdin);
	R(n), R(m), R(q);
	for (int i = 1; i <= n; ++i) {
		R(h[i]);
		a[i] = h[i];
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; ++i)
		h[i] = lower_bound(a + 1, a + n + 1, h[i]) - a, fa[i] = i;
	for (int i = 1; i <= n; ++i) {
		build(root[i], 1, n , h[i]);
	}
//	for(int i = 1; i<=n; ++i) {
//		printf("tr[root[%d]].sum = %d\n", i,tr[root[i]].sum);
//	}
	for (int i = 1; i <= m; ++i) {
		R(qu[i].a), R(qu[i].b), R(qu[i].c);
	}
	for (int i = m + 1; i <= m + q; ++i) {
		R(qu[i].a), R(qu[i].c), R(qu[i].b);
		qu[i].id = i - m;
	}
	sort(qu + 1, qu + 1 + m + q, cmp);
	int p1, q1;
	for (int i = 1; i <= m + q; ++i) {
		//	printf("qu[%d].id = %d, qu[%d].a = %d, qu[%d].b = %d, qu[%d].c = %d\n",i, qu[i].id,i, qu[i].a,i, qu[i].b,i, qu[i].c);
		if (!qu[i].id) {
			p1 = getfather(qu[i].a), q1 = getfather(qu[i].b);
			if (p1 != q1) {
				fa[p1] = q1;
				root[q1] = merge(root[p1], root[q1]);
			}
		} else {
			p1 = getfather(qu[i].a);
			//	printf("qu[%d].b = %d, tr[root[%d]].sum = %d\n", i, qu[i].b, p1, tr[root[p1]].sum);
			if (tr[root[p1]].sum < qu[i].b) {
				ans[qu[i].id] = -1;
				continue;
			}
			ans[qu[i].id] = a[getkth(root[p1], 1, n, tr[root[p1]].sum - qu[i].b + 1)];
		}
	}
	for (int i = 1; i <= q; ++i) {
		/* code */
		printf("%d\n", ans[i]);
	}
}
