
#include <bits/stdc++.h>
using namespace std;
inline void R (int &v) {
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
int f[40050], p[40050];
std::vector<int> q[40050];
int top[40050], fa[40050], dep[40050], pos[40050], num[40050], indx, son[40050], siz[40050];
int Q, K;
struct tree {
	multiset<int> v;
} tr[200005];
inline void dfs1(int x) {
	int v;
	siz[x] = 1;
	for (int i = 0; i < q[x].size(); ++i) {
		v = q[x][i];
		if (v != fa[x]) {
			fa[v] = x;
			dep[v] = dep[x] + 1;
			dfs1(v);
			siz[x] += siz[v];
			if (siz[son[x]] < siz[v]) son[x] = v;
		}
	}
}
inline void dfs2(int x) {
	int v;
	num[x] = ++indx;
	pos[indx] = x;
	if (son[x]) {
		v = son[x];
		top[v] = top[x];
		dfs2(v);
	}
	for (int i = 0; i <  q[x].size(); ++i) {
		v = q[x][i];
		if (v != fa[x] && v != son[x]) {
			top[v] = v;
			dfs2(v);
		}
	}
}
inline void insert(int x, int l, int r, int pos, int v) {
	tr[x].v.insert(v);
	if (l == r) {
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid) insert(x << 1, l, mid, pos, v);
	else insert(x << 1 | 1, mid + 1, r, pos, v);
}
inline void del(int x, int l, int r, int pos, int v) {
	tr[x].v.erase(tr[x].v.find(v));
	if (l == r) {
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid) del(x << 1, l, mid, pos, v);
	else del(x << 1 | 1, mid + 1, r, pos, v);
}
multiset<int> dui;
int si;
inline void query(int x, int ql, int qr, int l, int r) {
	if (l >= ql && r <= qr) {
		if (tr[x].v.size()) {
			multiset<int>:: iterator iter = tr[x].v.end();
			--iter;
			while (si < K || (*iter) > (*dui.begin())) {
				if (si < K) dui.insert(*iter), ++si;
				else {
					dui.erase(dui.begin());
					dui.insert(*iter);
				}
				if (iter == tr[x].v.begin()) break;
				--iter;
			}
		}
		return;
	}
	int mid = l + r >> 1;
	if (ql <= mid) query(x << 1, ql, qr, l, mid);
	if (qr > mid) query(x << 1 | 1, ql, qr, mid + 1, r);
}
std::vector<int> daan;
inline void xunwen(int x, int y) {
	dui.clear();
	si = 0;
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]] ) swap(x, y);
		query(1, num[top[x]], num[x], 1, n);
		x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	query(1, num[x], num[y], 1, n);
	if (!dui.size()) {
		puts("-1");
		return;
	} else {
		multiset<int> :: iterator iter = dui.end();
		do {
			--iter;
			printf("%d ", *iter);
		} while (iter != dui.begin());
		puts("");
	}
	return;
}
int main () {
//	freopen("knight.in", "r", stdin);
//	freopen("knight.out", "w", stdout);
	R(n);
	int x, y;
	for (int i = 1; i < n; ++i) {
		R(x), R(y);
		q[x].push_back(y);
		q[y].push_back(x);
	}
	int m;
	R(m);
	for (int i = 1; i <= m; ++i) {
		R(f[i]), R(p[i]);
	}
	R(Q), R(K);
	dep[1] = 1;
	top[1] = 1;
	dfs1(1);
	dfs2(1);
	//build(1, 1, n);
	for (int i = 1; i <= m; ++i) {
		insert(1, 1, n, num[p[i]], f[i]);
	}
//	printf("tr[7].v.size() = %d\n", tr[7].v.size());
	int kind;
//	for (int i = 1; i <= n; ++i) {
//		printf("num[%d] = %d\n", i, num[i]);
//	}
	for (int i = 1; i <= Q; ++i) {
		R(kind), R(x), R(y);
		switch (kind) {
		case 1:
			xunwen(x, y);
			break;
		case 2:
			del(1, 1, n, num[p[x]], f[x]);
			p[x] = y;
			insert(1, 1, n, num[p[x]], f[x]);
			break;
		case 3:
			del(1, 1, n, num[p[x]], f[x]);
			f[x] = y;
			insert(1, 1, n, num[p[x]], f[x]);
			break;
		}
	}
	return 0;
}
