
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
int dp[3005][1243];
const int inf = 0x3f3f3f3f;
int tot;
#define bin(x) (1<<x)
bool vis[5005];
int all;
int n, m, p1;
queue<int>que;
struct node {
	int to, length;
	node(int to, int length): to(to), length(length) {}
	node() {}
};
std::vector<node> q[5005];
struct point {
	int id, col;
	point(int id, int col): id(id), col(col) {}
	point() {}
} p[105];

inline void create(int x, int y, int z) {
	q[x].push_back(node(y, z));
	q[y].push_back(node(x, z));
}
inline bool cmp(const point &a, const point &b) {
	return a.col < b.col;
}
int g[5200];
int main () {
	R(n), R(m), R(p1);
	memset(dp, 0x3f, sizeof(dp));
	int x, y, z;
	for (int i = 1; i <= m; ++i) {
		R(x), R(y), R(z);
		create(x, y, z);
	}
	for (int i = 1; i <= p1; ++i) {
		R(p[i].col), R(p[i].id);
	}
	sort(p + 1, p + p1 + 1, cmp);
	int C = 0;
	int j = 1;
	int nowc = -1;
	for (int i = 1; i <= p1; ++i) {
		if (p[i].col != nowc) {
			nowc = p[i].col;
			++C;
		}
		p[i].col = C;
	}
	memset(g, 0x3f, sizeof(g));
	for (int col = 1; col < (1 << C); ++col) {
		memset(dp, 0x3f, sizeof(dp));
		tot = 0;
		for (int i = 1; i <= p1; ++i) {
			if ((1 << p[i].col - 1) & col) {
				dp[p[i].id][bin(tot++)] = 0;
			}
		}
		all = bin(tot);
		int temp;
		int u, v;
		for (int sta = 1; sta < all; ++sta) {
			for (int i = 1; i <= n; ++i) {
				for (int k = (sta - 1) & sta; k; k = (k - 1)&sta) {
					if (dp[i][sta] > dp[i][k] + dp[i][sta ^ k]) {
						dp[i][sta] = dp[i][k] + dp[i][sta ^ k];
					}
				}
				if (dp[i][sta] != inf) {
					vis[i] = 1;
					que.push(i);
				}
			}
			while (!que.empty()) {
				x = que.front();
				vis[x] = 0;
				que.pop();
				node *p;
				for (int k = 0; k < q[x].size(); ++k) {
					p = &q[x][k];
					if (dp[p->to][sta] > dp[x][sta] + p->length) {
						dp[p->to][sta] = dp[x][sta] + p->length;
						if (!vis[p->to]) {
							vis[p->to] = 1;
							que.push(p->to);
						}
					}
				}
			}
		}
		for (int i = 1; i <= p1; ++i) {
			g[col] = min(g[col], dp[p[i].id][all - 1]);
		}
	}
	for (int i = 1; i < (1 << C) ; ++i) {
		for (int k = (i - 1)&i; k; k = (k - 1)&i) {
			g[i] = min(g[i], g[k] + g[i ^ k]);
		}
	}
	printf("%d\n", g[(1 << C) - 1]);
}
