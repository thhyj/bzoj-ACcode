
#include <bits/stdc++.h>
using namespace std;
inline char read() {
	static const int IN_LEN = 1000000;
	static char buf[IN_LEN], *s, *t;
	s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin) : 0;
	return s == t ? -1 : *s++;
}

template <class T>
inline void R(T &x) {
	static char c;
	static bool iosig;
	for (c = read(), iosig = false; !isdigit(c); c = read()) {
		if (c == -1) return;
		c == '-' ? iosig = true : 0;
	}
	for (x = 0; isdigit(c); c = read()) x = (x + (x << 2) << 1) + (c ^ '0');
	iosig ? x = -x : 0;
}
int n, q1;
std::vector<int> q[300005];
int siz[300005], fa[300005], dep[300005], in[300005], out[300005], tot, cnt, fan[300005];
int p, k, ans;
inline void create(int x, int y) {
	q[x].push_back(y);
	q[y].push_back(x);
}
inline void dfs(int x) {
	in[x] = ++tot;
	siz[x] = 1;
	fan[tot] = x;
	for (int i = 0; i < q[x].size(); ++i) {
		int v = q[x][i];
		if (v ^ fa[x]) {
			fa[v] = x;
			dep[v] = dep[x] + 1;
			dfs(v);
			siz[x] += siz[v];
		}
	}
	out[x] = tot;
}
struct tree {
	int ls, rs;
	long long sum;
} tr[6000005];
int root[300005];
inline void build(int prev, int &x, int l, int r, int v1, int v2) {
	x = ++cnt;
	tr[x].sum = tr[prev].sum + v2;
	if (l == r) {
		return ;
	}
	int mid = l + r >> 1;
	if (v1 <= mid) tr[x].rs = tr[prev].rs, build(tr[prev].ls, tr[x].ls, l, mid, v1, v2);
	else tr[x].ls = tr[prev].ls, build(tr[prev].rs, tr[x].rs, mid + 1, r, v1, v2);
}
inline	long long query(int prev, int x, int ql, int qr, int l, int r) {
	if (l >= ql && r <= qr) {
		return tr[x].sum - tr[prev].sum;
	}
	int mid = l + r >> 1;
	long long ret = 0;
	if (ql <= mid) ret += query(tr[prev].ls, tr[x].ls, ql, qr, l, mid);
	if (qr > mid) ret += query(tr[prev].rs , tr[x].rs, ql, qr, mid + 1 , r);
	return ret;
}
int mdep;
int main () {
//	freopen("laugh.in", "r", stdin);
//	freopen("laugh.out", "w", stdout);
	R(n), R(q1);
	int x, y, z;
	for (int i = 1; i < n; ++i) {
		R(x), R(y);
		create(x, y);
	}
	dep[1] = 1;
	dfs(1);
	for (int i = 1; i <= n; ++i) {
		mdep = max(dep[i], mdep);
	}
	for (int i = 1; i <= n; ++i) {
		build(root[i - 1], root[i], 1, mdep, dep[fan[i]], siz[fan[i]] - 1);
	}
	int p, k;
	long long ans = 0;
//	for(int i = 1; i <= n; ++i) {
//		printf("siz[%d] = %d, dep[%d] = %d, in[%d] = %d, out[%d] = %d\n",i, siz[i], i ,dep[i],i,in[i],i,out[i]);
//	}
//	for(int i =1; i <=n; ++i) {
//		printf("root[%d] = %d, tr[root[%d]].sum = %d\n",i, root[i], i, tr[root[i]].sum);
////	}
	for (int i = 1; i <= q1; ++i) {
		ans = 0;
		R(p), R(k);
//		printf("dep[%d] = %d\n", p, dep[p]);
		ans += ((long long)siz[p] - 1) * (long long)min(dep[p] - 1, k);
		//	printf("ans = %d\n",ans);
		ans += query(root[in[p]], root[out[p]], min(dep[p] + 1, mdep), min(dep[p] + k, mdep), 1, mdep);
		cout<<ans<<'\n';
	}
	return 0;
}
