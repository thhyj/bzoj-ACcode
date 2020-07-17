
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
	if (p)v = -v;
}
int dp[12][13][1243], pre[12][13][1243][3];
#define pii pair<int, int>
#define mk make_pair
int a[12][13];
const int inf = 0x7f7f7f7f;
int tot;
#define bin(x) (1<<x)
bool vis[12][12];
int all;
const int fx[4] = {0, 1, 0, -1};
const int fy[4] = {1, 0, -1, 0};
inline void dfs(int x, int y, int k) {
	if (!k) return;
	vis[x][y] = 1;
	dfs(pre[x][y][k][0], pre[x][y][k][1], pre[x][y][k][2]);
	if (pre[x][y][k][0] == x && pre[x][y][k][1] == y) {
		dfs(pre[x][y][k][0], pre[x][y][k][1], pre[x][y][k][2] ^ k);
	}
}
int n, m;
inline void solve(int x, int y) {
	printf("%d\n", dp[x][y][all - 1]);
	dfs(x, y, all - 1);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (!a[i][j]) {
				putchar('x');
			} else if (vis[i][j]) {
				putchar('o');
			} else putchar('_');
		}
		puts("");
	}
}
queue<pii>que;
int main () {
	R(n), R(m);
	memset(dp, 127, sizeof(dp));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			R(a[i][j]);
			if (!a[i][j]) {
				dp[i][j][bin(tot++)] = 0;
			}
		}
	}
	all = bin(tot);
	pii temp;
	int x, y, u, v;
	for (int sta = 1; sta < all; ++sta) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				for (int k = (sta - 1) & sta; k; k = (k - 1)&sta) {
					if (dp[i][j][sta] > dp[i][j][k] + dp[i][j][sta ^ k] - a[i][j]) {
						dp[i][j][sta] = dp[i][j][k] + dp[i][j][sta ^ k] - a[i][j];
						pre[i][j][sta][0] = i;
						pre[i][j][sta][1] = j;
						pre[i][j][sta][2] = k;
					}
				}
				if (dp[i][j][sta] != inf) {
					vis[i][j] = 1;
					que.push(mk(i, j));
				}
			}
		}

		while (!que.empty()) {
			temp = que.front();
			x = temp.first, y = temp.second;
			vis[x][y] = 0;
			que.pop();
			for (int k = 0; k < 4; ++k) {
				u = x + fx[k], v = y + fy[k];
				if (u > 0 && u <= n && v > 0 && v <= m) {
					if (dp[u][v][sta] > dp[x][y][sta] + a[u][v]) {
						dp[u][v][sta] = dp[x][y][sta] + a[u][v];
						pre[u][v][sta][0] = x;
						pre[u][v][sta][1] = y;
						pre[u][v][sta][2] = sta;
						if (!vis[u][v]) {
							vis[u][v] = 1;
							que.push(mk(u, v));
						}
					}
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (!a[i][j]) {
				solve(i, j);
				return 0;
			}
		}
	}
}
