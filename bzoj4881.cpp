
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
int n;
const int mod = 998244353;
int a[100005];
struct node {
	int ma, mi, maxpos, minpos;
} tr[400005];
int tot;
inline void updata(int x) {
	tr[x << 1].ma > tr[x << 1 | 1].ma ? (tr[x].ma = tr[x << 1].ma, tr[x].maxpos = tr[x << 1].maxpos) : (tr[x].ma = tr[x << 1 | 1].ma, tr[x].maxpos = tr[x << 1 | 1].maxpos) ;
	tr[x << 1].mi < tr[x << 1 | 1].mi ? (tr[x].mi = tr[x << 1].mi, tr[x].minpos = tr[x << 1].minpos) : (tr[x].mi = tr[x << 1 | 1].mi, tr[x].minpos = tr[x << 1 | 1].minpos) ;
}
inline void build(int x, int l, int r) {
	if (l == r) {
		tr[x].ma = tr[x].mi = a[l];
		tr[x].maxpos = tr[x].minpos = l;
		return;
	}
	int mid = l + r >> 1;
	build(x << 1, l , mid);
	build(x << 1 | 1, mid + 1, r);
	updata(x);
}
inline pair<int, int> Max (const pair<int, int> &a, const pair<int, int> &b) {
	if (a.first > b.first) return a;
	return b;
}
inline pair<int, int> Min (const pair<int, int> &a, const pair<int, int> &b) {
	if (a.first < b.first) return a;
	return b;
}
inline pair<int, int> querymax(int x, int ql, int qr, int l , int r) {
//	cout << "ql=" << ql << " qr=" <<qr<< " l=" << l << " r=" << r << " x=" << x << '\n';
	if (l >= ql && r <= qr) {
		return (pair<int, int>) {tr[x].ma, tr[x].maxpos};
	}
	int mid = l + r >> 1;
	pair<int, int> ret = (pair<int, int>) {0, 0};
	if (ql <= mid) ret = Max(ret, querymax(x << 1, ql, qr, l, mid));
	if (qr > mid) ret = Max(ret, querymax(x << 1 | 1, ql, qr, mid + 1, r));
	return ret;
}
inline pair<int, int> querymin(int x, int ql, int qr, int l, int r) {
	if (l >= ql && r <= qr) {
		return (pair<int, int>) {tr[x].mi, tr[x].minpos};
	}
	int mid = l + r >> 1;
	pair<int, int> ret = (pair<int, int>) {1000000000, 0};
	if (ql <= mid) ret = Min(ret, querymin(x << 1, ql, qr, l, mid));
	if (qr > mid) ret = Min(ret, querymin(x << 1 | 1, ql, qr, mid + 1, r));
	return ret;
}
int col[100005];
inline void modify(int x, int l , int r, int pos, int v) {
	if (l == r) {
		tr[x].ma = -1000000000;
		tr[x].mi = 1000000000;
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid) modify(x << 1, l, mid, pos, v);
	else modify(x << 1 | 1, mid + 1, r, pos, v);
	updata(x);
}
pair<int, int> temp;
int f[3];
inline void dfs(int x, int y) {
	modify(1, 1, n, x, 0);
	col[x] = y;
	y = 3 - y;
	while (1) {
		temp = querymax(1, 1, x, 1, n);
	//	cout<<temp.first<<'\n';
		if (temp.second&& temp.first > a[x]) {
			dfs(temp.second, y);
		} else break;
	}
	while (1) {
		temp = querymin(1, x, n, 1, n);
		if (temp.second && temp.first < a[x]) {
			dfs(temp.second, y);
		} else break;
	}
}
int main () {
//	freopen("out.out", "w", stdout);
	R(n);
	for (int i = 1; i <= n; ++i) {
		R(a[i]);
	}
	tot = 1;
	build(1, 1, n);
	int ret = 0;
	for (int i = 1; i <= n; ++i) {
		if (!col[i]) {dfs(i, 1); ret++;}
	}
//	cout<<"ret="<<ret<<'\n';
	for (int i = 1; i <= n; ++i) {
		if (a[i] < f[col[i]]) return puts("0"), 0;
		f[col[i]] = a[i];
	}
	int ans = 1;
	while (ret--) {
		ans = (ans << 1) % mod;
	}
	cout << ans;
}
