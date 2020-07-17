
#include <bits/stdc++.h>
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
	if (p)v = -v;
}
using namespace std;
int cnt, tot;
struct node {
	int c[2], fa;
} q[800005];
int root[800005];
struct tree {
	int c[2], sum;
} tr[8000005];
inline void updata(int x) {
	tr[x].sum = tr[tr[x].c[0]].sum + tr[tr[x].c[1]].sum;
}
int top;
int yezi[200005];
bool vis[200005];
inline void build(int &x, int l, int r, int pos) {
	if (!x) x = ++tot;
	tr[x].sum = 1;
	if (l == r) {
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid) build(tr[x].c[0], l, mid, pos);
	else build(tr[x].c[1], mid + 1, r, pos);
}
long long ans;
long long cnt1, cnt2;
inline int merge(int x, int y) {
	if(!x) return y;
	if(!y) return x;
	cnt1 += (long long)tr[tr[x].c[0]].sum * tr[tr[y].c[1]].sum;
	cnt2 += (long long)tr[tr[y].c[0]].sum * tr[tr[x].c[1]].sum;
	tr[x].c[0] = merge(tr[x].c[0], tr[y].c[0]), tr[x].c[1] = merge(tr[x].c[1], tr[y].c[1]);
	updata(x);
	return x;
}
inline void solve(int x) {
	if (!x)return;
	solve(q[x].c[0]); solve(q[x].c[1]);
	if (!root[x]) {
		cnt1 = cnt2 = 0;
		root[x] = merge(root[q[x].c[0]], root[q[x].c[1]]);
		ans += min(cnt1, cnt2);
	}
}
int n;
inline void read(int now) {
	int x;
	R(x);
	if (x) {
		build(root[now], 1, n, x);
	} else {
		read(q[now].c[0] = ++cnt);
		read(q[now].c[1] = ++cnt);
	}
}
int main () {
//	freopen("in.in", "r", stdin);
	R(n);
	read(++cnt);
	solve(1);
	printf("%lld\n", ans);
}
