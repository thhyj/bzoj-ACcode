
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
inline void R(long long &v) {
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
	long long sum;
	int son[2];
	long long max;
} tr[400040];
int tot, root;
long long a[100040];
inline void updata(int x) {
	tr[x].sum = tr[tr[x].son[0]].sum + tr[tr[x].son[1]].sum;
	tr[x].max = max(tr[tr[x].son[0]].max, tr[tr[x].son[1]].max);
}
inline void build (int &now, int l, int r) {
	if (!now) now = ++tot;
	if (l == r) {
		tr[now].sum = tr[now].max = a[l];
		return ;
	}
	int mid = l + r >> 1;
	build(tr[now].son[0], l, mid);
	build(tr[now].son[1], mid + 1, r);
	updata(now);
}
inline void modify(int x, int al, int ar, int l, int r) {
	if (tr[x].max <= 1) return;
	if (l == r) {
	//	cout << "l=" << l << '\n';
	//	cout << "tr[x].sum=" << tr[x].sum << '\n';
		tr[x].sum = tr[x].max = sqrt(tr[x].sum);
	//cout << "change to " << tr[x].sum << '\n';
		return;
	}
	int mid = l + r >> 1;
	if (al <= mid) {
		modify(tr[x].son[0], al, ar, l, mid);
	}
	if (ar > mid) {
		modify(tr[x].son[1], al, ar, mid + 1, r);
	}
	updata(x);
}
inline long long query(int x, int ql, int qr, int l, int r) {
	if (l >= ql && r <= qr) {
		return tr[x].sum;
	}
	long long ret = 0;
	int mid = l + r >> 1;
	if (ql <= mid) {
		ret += query(tr[x].son[0], ql, qr, l, mid);
	}
	if (qr > mid) {
		ret += query(tr[x].son[1], ql, qr, mid + 1, r);
	}
	return ret;
}
int main() {
	//freopen("in.in", "r", stdin);
	int n;
	R(n);
	for (int i = 1; i <= n; ++i) {
		R(a[i]);
	}
	tot = root = 1;
	build(root, 1, n);
	int m;
	R(m);
	int kind, l, r;
	for (int i = 1; i <= m; ++i) {
		R(kind);
		if (kind == 0) {
			R(l), R(r);
			if(l>r) swap(l,r);
			modify(root, l, r, 1, n);
		}
		if (kind == 1) {
			R(l), R(r);
			if(l>r) swap(l,r);
			printf("%lld\n", query(root, l, r, 1, n) );
		}
	}
}
