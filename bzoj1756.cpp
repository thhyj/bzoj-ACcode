
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
int n, m;
struct tree {
	int ms, ls, rs, sum;
} tr[2000005];
int a[500005];
inline void updata(int x) {
	tr[x].sum = tr[x << 1].sum + tr[x << 1 | 1].sum;
	tr[x].ls = max(tr[x << 1].ls, tr[x << 1].sum + tr[x << 1 | 1].ls);
	tr[x].rs = max(tr[x << 1 | 1].rs, tr[x << 1 | 1].sum + tr[x << 1].rs);
	tr[x].ms = max(max(tr[x << 1].ms, tr[x << 1 | 1].ms), tr[x << 1].rs + tr[x << 1 | 1].ls);
}
inline void build(int x, int l, int r) {
	if (l == r) {
		tr[x].ms = tr[x].ls = tr[x].rs = tr[x].sum = a[l];
		return;
	}
	int mid = l + r >> 1;
	build(x << 1, l, mid);
	build(x << 1 | 1, mid + 1, r);
	updata(x);
}
inline tree query(int x, int l, int r, int ql, int qr) {
	if (l >= ql && r <= qr) {
		return tr[x];
	}
	int mid = l + r >> 1;
	if (qr <= mid)	return query(x << 1, l, mid, ql, qr);
	if (ql > mid)  return query(x << 1 | 1, mid + 1, r, ql , qr);
	else {
		tree temp1, temp2, temp3;
		temp1 = query(x << 1, l, mid, ql, qr);
		temp2 = query(x << 1 | 1, mid + 1, r, ql , qr);
		temp3.sum = temp1.sum + temp2.sum;
		temp3.ls = max(temp1.ls, temp1.sum + temp2.ls);
		temp3.rs = max(temp2.rs, temp2.sum + temp1.rs);
		temp3.ms = max(max(temp1.ms, temp2.ms), temp1.rs + temp2.ls);
		return temp3;
	}
}
inline void modify(int x, int l, int r, int pos, int v) {
	if (l == r) {
		tr[x].sum = tr[x].ms = tr[x].ls = tr[x].rs = v;
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid) {
		modify(x << 1, l, mid, pos, v);
	} else modify(x << 1 | 1, mid + 1, r, pos, v);
	updata(x);
}
int main () {
	R(n), R(m);
	for (int i = 1; i <= n; ++i) {
		R(a[i]);
	}
	build(1, 1, n);
	int kind, x, y;
	for (int i = 1; i <= m; ++i) {
		R(kind), R(x), R(y);
		if (kind == 1) {
			if (x > y) swap(x, y);
			printf("%d\n", query(1, 1, n, x, y));
		} else {
			modify(1, 1, n, x, y);
		}
	}
	return 0;
}
