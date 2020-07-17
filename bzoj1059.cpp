
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
int ma[205][205];
int n, T;
int gap[100005], dis[100005], temp[100005];
struct node {
	int to, length, pa;
	node(int to, int length, int pa): to(to), length(length), pa(pa) {
	}
	node() {}
};
std::vector<node> q[100005];
bool vis[100005];
int s, t;
inline void bfs() {
	static queue<int>que;
	que.push(t);
	vis[t] = 1;
	gap[0]++;
	int x;
	node *p;
	while (!que.empty()) {
		x = que.front();
		que.pop();
		for (int i = 0; i < q[x].size(); ++i) {
			p = &q[x][i];
			if (!vis[p->to]) {
				dis[p->to] = dis[x] + 1;
				gap[dis[p->to]]++;
				vis[p->to] = 1;
				que.push(p->to);
			}
		}
	}
}
inline int sap(int x, int flow, int n) {
	if (x == t) {
		return flow;
	}
	int ret = 0, f;
	node *p;
	for (int i = temp[x]; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (dis[p->to] + 1 == dis[x] && p->length) {
			f = sap(p->to, min(flow - ret, p->length), n);
			p->length -= f;
			q[p->to][p->pa].length += f;
			temp[x] = i;
			if ((ret += f) == flow || dis[x] >= n) {
				temp[x] = 0;
				return ret;
			}
		}
	}
	temp[x] = 0;
	if (!(--gap[dis[x]])) dis[s] = n;
	gap[++dis[x]]++;
	return ret;
}
inline int sap(int n) {
	int ret = 0;
	bfs();
	while (dis[s] < n) ret += sap(s, INT_MAX, n);
	return ret;
}
inline void create(int x, int y, int z) {
	q[x].push_back(node(y, z, q[y].size()));
	q[y].push_back(node(x, 0, q[x].size() - 1));
}
int main () {
//	freopen("qmatrix.in","r",stdin);
//	freopen("qmatrix.out","w",stdout);
	R(T);
	s = 0, t = 1000;
	while (T--) {
		R(n);
		memset(gap, 0, sizeof(gap));
		memset(dis, 0, sizeof(dis));
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i <= n + n; ++i) {
			q[i].clear();
		}
		q[t].clear();
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				R(ma[i][j]);
				if (ma[i][j]) create(i, n + j, 1);
			}
		}
		for (int i = 1; i <= n; ++i) {
			create(s, i, 1);
			create(i + n, t, 1);
		}
		if (sap(n * 2 + 2) == n) {
			puts("Yes");
		} else puts("No");
	}
	return 0;
}
