
#include <bits/stdc++.h>
using namespace std;
const int maxn = 50005;
std::vector<int> edge[maxn];
int dfn[maxn], low[maxn], a[maxn << 2], f[maxn << 1], q[maxn << 1], indx, fa[maxn], dep[maxn];
inline void create(int x, int y) {
	edge[x].push_back(y);
	edge[y].push_back(x);
}
int n, m, tot, ans;
inline void dp(int rt, int x) {
	tot = dep[x] - dep[rt] + 1;
	memset(a, 0, sizeof(int) * ((tot << 1) + 5));
	int y = x;
	for (int i = tot; i; --i) {
		a[i] = f[y];
		y = fa[y];
	}
	for (int i = 1; i <= tot; ++i) a[i + tot] = a[i];
	int l = 1, r = 1;
	q[1] = 1;
	for (int i = 2; i <= (tot << 1); ++i) {
		while (l <= r && i - q[l] > (tot >> 1)) ++l;
		ans = max(ans, a[i] + i + a[q[l]] - q[l]);
		while (l <= r && a[i] - i >= a[q[r]] - q[r]) --r;
		q[++r] = i;
	}
	for (int i = 2; i <= tot; ++i) {
		f[rt] = max(f[rt], a[i] + min(i - 1, tot - i + 1));
	}
}
inline void dfs(int x) {
	low[x] = dfn[x] = ++indx;
	int v;
	for (int i = 0; i < edge[x].size(); ++i) {
		v = edge[x][i];
		if (fa[x] != v) {
			if (!dfn[v]) {
				dep[v] = dep[x] + 1;
				fa[v] = x;
				dfs(v);
				low[x] = min(low[x], low[v]);
			} else {
				low[x] = min(low[x], dfn[v]);
			}
			if (dfn[x] < low[v]) {
				ans = max(ans, f[x] + f[v] + 1);
				f[x] = max(f[x], f[v] + 1);
			}
		}
	}
	for (int i = 0; i < edge[x].size(); ++i) {
		v = edge[x][i];
		if (fa[v] != x && dfn[x] < dfn[v]) {
			dp(x, v);
		}
	}
}
int main() {
	int k, x, y;
	//freopen("in.in", "r", stdin);
	scanf("%d", &n);
	scanf("%d", &m);
	//printf("n = %d, m = %d\n",n, m);
	memset(edge, 0, sizeof(edge));
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &k, &x);
		for (int j = 2; j <= k; ++j) {
			scanf("%d", &y);
			create(x, y);
			x = y;
		}
	}
	dfs(1);
	printf("%d\n", ans);
	return 0;
}

