
#include <bits/stdc++.h>
using namespace std;
inline void R(int &v) {
	static char ch;
	bool p = 0;
	v = 0;
	do {
		ch = getchar();
		if (ch == '-') p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = ( v + (v << 2) << 1) + (ch^'0');
		ch = getchar();
	}
	if (p) v = -v;
}
std::vector<int> q[200005];
struct  tree {
	int max, son[2], tag, cov;
} tr[800005];
inline void create(int x, int y) {
	q[x].push_back(y);
	q[y].push_back(x);
}
int a[200005];
int fa[200005], top[200005], son[200005], num[200005], pos[200005], indx, dep[200005], siz[200005];
inline void dfs1(int x) {
	int v;
	siz[x] = 1;
	for (int i = 0; i < q[x].size(); ++i) {
		v = q[x][i];
		if (v ^ fa[x]) {
			dep[v] = dep[x] + 1;
			fa[v] = x;
			dfs1(v);
			siz[x] += siz[v];
			if (siz[v] > siz[son[x]] || (!son[x])) son[x] = v;
		}
	}
}
inline void dfs2(int x) {
	pos[x] = ++indx;
	num[indx] = x;
	int v;
	if (son[x]) {
		v = son[x];
		top[v] = top[x];
		dfs2(v);
	}
	for (int i = 0; i < q[x].size(); ++i) {
		v = q[x][i];
		if (v != fa[x] && v != son[x]) {
			top[v] = v;
			dfs2(v);
		}
	}
}
int root;
int tot;
int n;
inline void updata(int x) {
	tr[x].max = max(tr[tr[x].son[0]].max, tr[tr[x].son[1]].max);
}
inline void build(int &x, int l, int r) {
	if (!x) x = ++tot;
	if (l == r) {
		//cout<<"x="<<x<<" l="<<l<<'\n';
		tr[x].max = a[num[l]];
		return;
	}
	int mid = l + r >> 1;
	build(tr[x].son[0], l, mid);
	build(tr[x].son[1], mid + 1, r);
	updata(x);
}
inline void pushdown(int x) {
	if (tr[x].cov != -1) {
		tr[tr[x].son[0]].cov = tr[x].cov;
		tr[tr[x].son[0]].max = tr[x].cov;
		tr[tr[x].son[0]].tag = 0;
		tr[tr[x].son[1]].cov = tr[x].cov;
		tr[tr[x].son[1]].max = tr[x].cov;
		tr[tr[x].son[1]].tag = 0;
		tr[x].cov = -1;
	}
	if (tr[x].tag) {
		tr[tr[x].son[0]].tag += tr[x].tag;
		tr[tr[x].son[0]].max += tr[x].tag;
		tr[tr[x].son[1]].tag += tr[x].tag;
		tr[tr[x].son[1]].max += tr[x].tag;
		tr[x].tag = 0;
	}
}
inline void add(int x, int l, int r, int al, int ar, int v) {
	if (l >= al && r <= ar) {
		tr[x].max += v;
		if (tr[x].cov != -1)
			tr[x].cov += v;
		else
			tr[x].tag += v;
		return;
	}
	pushdown(x);
	int mid = l + r >> 1;
	if (al <= mid) add(tr[x].son[0], l, mid, al, ar, v);
	if (ar > mid) add(tr[x].son[1], mid + 1, r, al, ar, v);
	updata(x);
}
inline void cover(int x, int l, int r, int al, int ar, int v) {
	if (l >= al && r <= ar) {
		tr[x].cov = v;
		tr[x].max = v;
		tr[x].tag = 0;
		return;
	}
	pushdown(x);
	int mid = l + r >> 1;
	if (al <= mid) cover(tr[x].son[0], l, mid, al, ar, v);
	if (ar > mid) cover(tr[x].son[1], mid + 1, r, al, ar, v);
	updata(x);
}
inline int query(int x, int l, int r, int al, int ar) {
	if (l >= al && r <= ar) {
		//cout<<"num[l]="<<num[l]<<" l="<<l<<" r="<<r<<" tr[x].max="<<tr[x].max<<'\n';
		return tr[x].max;
	}
//	//cout<<"x="<<x<<'\n';
	pushdown(x);
	//updata(x);
	int mid = l + r >> 1, ret = -2000000000;;
	if (al <= mid) ret = max(ret, query(tr[x].son[0], l, mid, al, ar));
	if (ar > mid) ret = max(ret, query(tr[x].son[1], mid + 1, r, al, ar));
	return ret;
}
inline void change(int x, int l, int r, int po, int v) {
	if (l == r) {
		tr[x].max = v;
		return;
	}
	pushdown(x);
	int mid = l + r >> 1;
	if (po <= mid) change(tr[x].son[0], l, mid, po, v);
	else change(tr[x].son[1], mid + 1, r, po, v);
	updata(x);
}
inline void trad(int x, int y, int z) {
	while (top[x]^top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		add(root, 1, n, pos[top[x]] , pos[x], z);
		x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	if(x^y)add(root, 1, n, pos[x] + 1, pos[y], z );
}
inline void trco(int x, int y, int z) {
	while (top[x]^top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		cover(root, 1, n, pos[top[x]] , pos[x], z);
		x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	if(x^y)cover(root, 1, n, pos[x] + 1, pos[y], z );
}
inline int trqm(int x, int y) {
	int ret = -1000000000;
	while (top[x]^top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		//cout<<"x="<<x<<" y="<<y<<'\n';
		//cout<<"top[x]="<<top[x]<<" top[y]="<<top[y]<<'\n';
		//cout<<"pos[top[x]]="<<pos[top[x]]<<" pos[x]="<<pos[x]<<'\n';
		ret = max(ret, query(root, 1, n, pos[top[x]] , pos[x]));
		x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	//cout<<"x="<<x<<" y="<<y<<'\n';
	if(x^y)ret = max(ret, query(root, 1, n, pos[x] + 1, pos[y]));
	return ret;
}
int fi[100005];
int x[100005], y[100005], z[100005];
int main () {
//	freopen("in.in", "r", stdin);
//	freopen("out.out","w",stdout);
	R(n);
	for (int i = 0 ; i <= 800003; ++i) {
		tr[i].cov = -1;
	}
	a[1] = 0;
	tot = root = 1;
	for (int i = 1 ; i < n; ++i) {
		R(x[i]), R(y[i]), R(z[i]);
		create(x[i], y[i]);
	}
	top[1] = fa[1] = dep[1] = 1;
	dfs1(1);
	dfs2(1);
	for (int i = 1; i < n; ++i) {
		(dep[x[i]] < dep[y[i]]) ? (a[y[i]] = z[i], fi[i] = y[i]) : (a[x[i]] = z[i], fi[i] = x[i]);
	}
//	for (int i = 1; i < n; ++i) {
		//cout<<"a["<<i<<"]="<<a[i]<<'\n';
//		//cout<<"dep["<<i<<"]="<<dep[i]<<'\n';
//	}
	char s[10];
	build(root , 1, n);
	int x1, y1, z1;
	while (1) {
		scanf("%s", s);
		if (s[0] == 'S') return 0;
		if (s[0] == 'A') {
			R(x1), R(y1), R(z1);
			trad(x1, y1, z1);
		} else {
			if (s[0] == 'C') {
				if (s[1] == 'h')
				{	R(x1), R(z1);
					//cout<<"fi[x1]="<<fi[x1]<<'\n';
					change(root, 1, n, pos[fi[x1]], z1);
				}
				else {
					R(x1), R(y1), R(z1);
					trco(x1, y1, z1);
				}
			} else {
				if (s[0] == 'M') {
					R(x1), R(y1);
					printf("%d\n", trqm(x1, y1));
				}
			}
		}
	}
	return 0;
}
