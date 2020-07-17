
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
struct node {
	int ls, rs, sum;
} tr[18000005];
int root[500005];
int cnt = 1;
inline void updata(const int &x) {
	tr[x].sum = tr[tr[x].ls].sum + tr[tr[x].rs].sum;
}
inline void build(const int &prev, int &now, int l, int r, int v) {
	now = ++cnt;
	tr[now] = tr[prev];
	if (l == r) {
		tr[now].sum++;
		return ;
	}
	int mid = l + r >> 1;
	if (v <= mid) {
		build(tr[prev].ls,tr[now].ls, l , mid, v);
	} else {
		build(tr[prev].rs,tr[now].rs, mid + 1, r, v);
	}
	updata(now);
}
inline int query(const int &prev, const int &now, const int &l, const int &r, const int &k) {
	if (l == r) {
		if (tr[now].sum - tr[prev].sum > k) return l;
		return 0;
	}
	int mid = l + r >> 1;
	if (tr[tr[now].ls].sum - tr[tr[prev].ls].sum > k) {
		return query(tr[prev].ls, tr[now].ls, l, mid, k);
	}
	else if (tr[tr[now].rs].sum - tr[tr[prev].rs].sum > k) {
		return query(tr[prev].rs, tr[now].rs, mid + 1, r, k);
	}
	return 0;
}
int main () {
	int n;
	int m;
	R(n);
	R(m);
	int lim=500005;
	int x;
	for (int i = 1; i <= n; ++i) {
		R(x);
		build(root[i - 1], root[i], 1, lim, x);
	}
	int y;
	int temp;
	for (int i = 1; i <= m; ++i) {
		R(x), R(y);
		if (temp = query(root[x - 1], root[y], 1, lim, (y - x + 1) / 2))
			printf("%d\n",temp); else puts("0");
	}
	return 0;
}
