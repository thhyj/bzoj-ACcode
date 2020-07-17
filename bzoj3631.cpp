
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
vector<int> q[300005];
int a[300005], fa[300005], dep[300005], siz[300005], son[300005], top[300005], sum[300005];
int tot;
inline void dfs1(int x) {
	siz[x] = 1;
	for (int i = 0; i < q[x].size(); ++i) {
		int v = q[x][i];
		if (v ^ fa[x]) {
			fa[v] = x;
			dep[v] = dep[x] + 1;
			dfs1(v);
			siz[x] += siz[v];
			if ((!son[x]) || siz[v] > siz[son[x]]) son[x] = v;
		}
	}
}
inline void dfs2(int x) {
	if (son[x]) {
		top[son[x]] = top[x];
		dfs2(son[x]);
	}
	for (int i = 0; i < q[x].size(); ++i) {
		int v = q[x][i];
		if ((v ^ son[x]) && (v ^ fa[x])) {
			top[v] = v;
			dfs2(v);
		}
	}
}
inline int getlca(int x, int y) {
	while (top[x]^top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	return x;
}
void gao(int x, int y) {
	sum[x]++, sum[y]++;
//	printf("x = %d, y = %d\n", x, y);
	int LCA = getlca(x, y);
	sum[LCA]--;
	sum[fa[LCA]]--;
//	printf("lca = %d, y = %d\n", LCA, y);
}
inline void dp(int x) {
	for (int i = 0; i < q[x].size(); ++i)
		if (q[x][i] != fa[x]) {
			dp(q[x][i]);
			sum[x] += sum[q[x][i]];
	 	}
}
int main() {
	//freopen("home5.in","r",stdin);
	int n, i, x, y;
	R(n);
	for (i = 1; i <= n; i++)
		R(a[i]);
	for (i = 1; i < n; i++) {
		R(x), R(y);
		q[x].push_back(y);
		q[y].push_back(x);
	}
	dfs1(a[1]);
	dfs2(a[1]);
	for (i = 1; i < n; i++)
		gao(a[i], a[i + 1]);
	dp(a[1]);
	for (int i = 2; i <= n; i++)sum[a[i]]--;
	for (int i = 1; i <= n; i++)printf("%d\n", sum[i]);
	return 0;
}
