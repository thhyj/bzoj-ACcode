
#include <bits/stdc++.h>
#include <tr1/unordered_map>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
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
int n, m, a[200005], mex[200005], rt, ans[200005];
__gnu_pbds::gp_hash_table<int, bool>vis;
__gnu_pbds::gp_hash_table<int, int>nxt, xia;
struct node {
	int ls, rs, mi, tag;
} tr[800005];
int tot;
struct que {
	int l, r, ori;
} q[200005];
const int inf = INT_MAX;
inline void updata(int x) {
	tr[x].mi = min(tr[tr[x].ls].mi, tr[tr[x].rs].mi);
}
inline void build(int &x, int l, int r) {
	if (!x) x = ++tot;
	if (l == r) {
		tr[x].mi = mex[l];
		return ;
	}
	int mid = l + r >> 1;
	build(tr[x].ls, l, mid);
	build(tr[x].rs, mid + 1, r);
	updata(x);
}
inline bool cmp(const que &a, const que &b) {
	return a.l < b.l || (a.l == b.l && a.r < b.r);
}
inline void pushdown(int x) {
	if (tr[x].tag != inf) {
		tr[tr[x].ls].tag = min(tr[tr[x].ls].tag, tr[x].tag);
		tr[tr[x].ls].mi = min(tr[tr[x].ls].mi, tr[x].tag);
		tr[tr[x].rs].tag = min(tr[tr[x].rs].tag, tr[x].tag);
		tr[tr[x].rs].mi = min(tr[tr[x].rs].mi, tr[x].tag);
		tr[x].tag = inf;
	}
}
inline void modify(int x, int al, int ar, int v, int l, int r) {
	if (l >= al && r <= ar) {
		tr[x].mi = min(tr[x].mi, v);
		tr[x].tag = min(tr[x].tag, v);
		return;
	}
	pushdown(x);
	int mid = l + r >> 1;
	if (al <= mid) modify(tr[x].ls, al, ar, v, l, mid);
	if (ar > mid) modify(tr[x].rs, al, ar, v, mid + 1, r);
	updata(x);
}
inline int query(int x, int pos, int l, int r) {
	if (l == r) {
		return tr[x].mi;
	}
	int mid = l + r >> 1;
	pushdown(x);
	if (pos <= mid) return query(tr[x].ls, pos, l, mid);
	else return query(tr[x].rs, pos, mid + 1, r);
}
int main () {
//	freopen("in.in", "r", stdin);
	R(n); R(m);
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		R(a[i]);
		vis[a[i]] = 1;
		while (vis[cnt]) ++cnt;
		mex[i] = cnt;
	}
//	for (int i = 1; i <= n ; ++i)
//	{
//		/* code */
//		printf("mex[%d] = %d\n", i, mex[i]);
//	}
	for (int i = n; i; --i) {
		if (xia[a[i]]) {
			nxt[i] = xia[a[i]];
		} else nxt[i] = n + 1;
		xia[a[i]] = i;
	}
//	for (int i = 1; i <= n ; ++i)
//	{
		/* code */
//		printf("nxt[%d] = %d\n", i, nxt[i]);
	//}
	for (int i = 1; i <= 800002; ++i) {
		tr[i].tag = inf; tr[i].mi = inf;
	}
	tot = 1;
	rt = 1;
	build(rt, 1, n);
	for (int i = 1; i <= m; ++i) {
		R(q[i].l), R(q[i].r);
		q[i].ori = i;
	}
	sort(q + 1, q + 1 + m, cmp);
	int now = 1;
//	for (int i = 1; i <= 4 * n ; ++i)
//	{
		/* code */
//		printf("tr[%d].mi = %d, tr[%d].ls = %d, tr[%d].rs = %d\n", i, tr[i].mi, i, tr[i].ls, i, tr[i].rs);
//	}
	for (int i = 1; i <= m; ++i) {
		while (now < q[i].l) {
			++now;
			modify(rt , now, nxt[now - 1] - 1, a[now - 1], 1, n);
		}
		ans[q[i].ori] = query(rt, q[i].r, 1, n);
	}
	for (int i = 1; i <= m; ++i) {
		printf("%d\n", ans[i]);
	}
}
