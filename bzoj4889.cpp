
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
int a[50005], b[50005];
int sum[50005], num[50005];
int tot;
int root[50005];
struct tree {
	int sum, num, son[2];
} tr[10000000];
#define lowbit(x) (x&-x)
int n, m;
const int mod = 1000000007;
inline void updata(int x) {
	tr[x].sum = tr[x].num = 0;
	if (tr[x].son[0]) tr[x].sum += tr[tr[x].son[0]].sum, tr[x].num += tr[tr[x].son[0]].num;
	if (tr[x].son[1]) tr[x].sum += tr[tr[x].son[1]].sum, tr[x].num += tr[tr[x].son[1]].num;
	tr[x].sum %= mod;
	tr[x].num %= mod;
}
inline void add(int &x, int l, int r, int pos, int v) {
	if (!x) x = ++tot;
	if (l == r) {
		tr[x].sum += v;
		tr[x].num += v > 0 ? 1 : -1;
		tr[x].sum %= mod;
		tr[x].num =  (tr[x].num + mod) % mod;
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid) add(tr[x].son[0], l, mid, pos, v);
	else add(tr[x].son[1], mid + 1, r, pos, v);
	updata(x);
}
inline pair<int , int> operator + (const pair<int, int> &a, const pair<int, int> &b) {
	return (pair<int, int>) {(a.first + b.first) % mod, (a.second + b.second) % mod};
}
inline pair<int , int> operator - (const pair<int, int> &a, const pair<int, int> &b) {
	return (pair<int, int>) {(a.first - b.first + mod) % mod, (a.second - b.second + mod) % mod};
}
inline pair<int , int> operator % (const pair<int, int> &a, const int &b) {
	return (pair<int, int>) {(a.first) % mod, (a.second) % mod};
}
inline pair<int , int> query (int x, int l, int r, int ql, int qr) {
	if (!x) return (pair<int, int>) {0, 0};
	if (l >= ql && r <= qr) {
		return (pair<int, int>) {tr[x].sum, tr[x].num};
	}
	int mid = l + r >> 1;
	pair<int, int>ret = (pair<int, int>) {0, 0};
	if (ql <= mid) ret = ret + query(tr[x].son[0], l, mid, ql, qr);
	if (qr > mid) ret = ret + query(tr[x].son[1], mid + 1, r, ql, qr);
	return ret % mod;
}
inline void modify(int x, int y, int z) {
	for (int i = z; i <= n; i += lowbit(i)) {
		add(root[i], 1, n, x, y);
	}
}
inline pair<int, int> xunwen(int x, int y) {
	pair<int, int> ret = (pair<int, int>) {0, 0};
	for (int i = y; i; i -= lowbit(i)) {
		ret = ret + query(root[i], 1, n, x + 1, n);
	}
	return ret;
}
inline pair<int, int> queryda(int x, int y) {
	pair<int, int> ret = (pair<int, int>) {0, 0};
	for (int i = y; i; i -= lowbit(i)) {
		ret = ret + query(root[i], 1, n, x + 1, n);
	}
	return ret;
}
inline pair<int, int> queryxiao(int x, int y) {
	pair<int, int> ret = (pair<int, int>) {0, 0};
	for (int i = y; i; i -= lowbit(i)) {
		ret = ret + query(root[i], 1, n, 1, x - 1);
	}
	return ret;
}
int main () {
	//freopen("book.in", "r", stdin);
//	freopen("book.out", "w", stdout);
	R(n), R(m);
	long long ans  = 0;
	for (int i = 1; i <= n; ++i) {
		root[i] = ++tot;
	}
	pair<int, int> temp;
	for (int i = 1; i <= n; ++i) {
		R(a[i]), R(b[i]);
		/*ans = ((ans + query(n) - query(a[i]))) % mod;
		ans = (ans + (query1(n) - query1(a[i])) * b[i]) % mod;
		add(a[i], b[i]);*/
		temp = xunwen(a[i], i);
		//	cout << "temp.first = " << temp.first << " temp.second = " << temp.second << '\n';
		ans = ((ans + temp.first)) % mod;
		ans = (ans + (long long)temp.second *(long long) b[i] % mod) % mod;
		modify(a[i], b[i], i);
	}
//	cout << ans << '\n';
	int x, y;
	for (int i = 1 ; i <= m; ++i) {
		R(x), R(y);
		temp = (pair<int, int>) {0, 0};
		temp = (queryxiao(a[x], n) - queryxiao(a[x], x)) + queryda(a[x], x);
		temp = temp % mod;
		//		cout << "temp.first = " << temp.first << " temp.second = " << temp.second << '\n';
		ans = ((long long)ans - (long long)temp.first + (long long)mod) % mod;
		ans = ((long long)ans - (long long)temp.second * (long long)b[x] % mod + (long long)mod) % mod;
		modify(a[x], -b[x], x);
		temp = (pair<int, int>) {0, 0};
		temp = (queryxiao(a[y], n) - queryxiao(a[y], y)) + queryda(a[y], y);
		temp = temp % mod;
		//		cout << "temp.first = " << temp.first << " temp.second = " << temp.second << '\n';
		ans = ((long long)ans - (long long)temp.first + (long long)mod) % mod;
		ans = ((long long)ans - (long long)temp.second * (long long)b[y] % mod + (long long)mod) % mod;
		modify(a[y], -b[y], y);
		temp = (pair<int, int>) {0, 0};
		temp = (queryxiao(a[y], n) - queryxiao(a[y], x)) + queryda(a[y], x);
		temp = temp % mod;
		//		cout << "temp.first = " << temp.first << " temp.second = " << temp.second << '\n';
		ans = ((long long)ans + (long long)temp.first) % mod;
		ans = ((long long)ans + (long long)temp.second * (long long)b[y] % mod) % mod;
		modify(a[y], b[y], x);
		temp = (pair<int, int>) {0, 0};
		temp = (queryxiao(a[x], n) - queryxiao(a[x], y)) + queryda(a[x], y);
		temp = temp % mod;
		//		cout << "temp.first = " << temp.first << " temp.second = " << temp.second << '\n';
		ans = ((long long)ans + (long long)temp.first) % mod;
		ans = ((long long)ans + (long long)temp.second * (long long)b[x] % mod) % mod;
		modify(a[x], b[x], y);
		swap(a[x], a[y]);
		swap(b[x], b[y]);
		cout << ans << '\n';
	}
	return 0;
}
