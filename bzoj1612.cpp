
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
}
vector<int>q[10005], q2[105];
int rd[105], cd[105];
int ans[105];
int temp;
bool vis[105];
inline void dfs(int x, int fa) {
	int v;
	vis[x] = 1;
	for (int i = 0; i < q[x].size(); ++i) {
		v = q[x][i];
		if (!vis[v]) {
			ans[temp]++;
			dfs(v, x);
		}
	}
}
inline void dfs2(int x, int fa) {
	int v;
	vis[x] = 1;
	for (int i = 0; i < q2[x].size(); ++i) {
		v = q2[x][i];
		if (!vis[v]) {
			ans[temp]++;
			dfs2(v, x);
		}
	}
}
int main () {
	int n, m;
	R(n), R(m);
	int x, y;
	for (int i =  1; i <= m; ++i) {
		R(x), R(y);
		q[x].push_back(y);
		q2[y].push_back(x);
	}
	int ret = 0;
	for (int i = 1; i <= n; ++i) {
		temp = i;
		memset(vis, 0 , sizeof(vis));
		dfs(i, i);
		memset(vis, 0 , sizeof(vis));
		dfs2(i, i);
		++ans[i];
	//	printf("ans[%d] = %d\n", i, ans[i]);
		if (ans[i] == n) ret++;
	}
	printf("%d\n", ret);

}
