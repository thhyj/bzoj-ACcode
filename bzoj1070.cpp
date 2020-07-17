
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
		v = (v + (v << 2) << 1) + (ch^'0');
		ch = getchar();
	}
	if (p) v = -v;
}
struct  node {
	int to, length, pa, w;
	node(int to, int length, int w, int pa) : to(to), length(length), w(w), pa(pa) {}
	node() {}
};
vector<node>q[10005];
inline void create(int x, int y, int z, int w) {
	q[x].push_back(node(y, z, w, q[y].size()));
	q[y].push_back(node(x, 0, -w, q[x].size() - 1));
}
const int INF = 252645135;
int dis[1005];
int prev[1005], pree[1005];
bool vis[1005];
inline pair<int, int>feiyong(int s, int t, int n) {
	pair<int, int>ans = pair<int, int> {0, 0};
	int j;
	int flow;
	node *p;
	while (1) {
		memset(dis, 15, sizeof(dis)) ;
		memset(vis, 0 , sizeof(vis));
		queue<int> que;
		dis[s] = 0;
		que.push(s);
		while (!que.empty()) {
			j = que.front();
			que.pop();
			vis[j] = 0;
			for (int i = 0; i < q[j].size(); ++i) {
				p = &q[j][i];
				if (dis[p->to] > dis[j] + p->w && p->length) {
					dis[p->to] = dis[j] + p->w;
					prev[p->to] = j;
					pree[p->to] = i;
					if (!vis[p->to]) que.push(p->to), vis[p->to] = 1;
				}
			}
		}
		if (dis[t] == INF) break;
		flow = INT_MAX;
		for (int i = t; i ^ s; i = prev[i]) {
			flow = min(flow, q[prev[i]][pree[i]].length);
		}
		ans.first += flow;
		ans.second += flow * dis[t];
		for (int i = t; i ^ s; i = prev[i]) {
			p = &q[prev[i]][pree[i]];
			p->length -= flow;
			q[p->to][p->pa].length += flow;
		}
	}
	return ans;
}
int main() {
	int s, t, m, n;
	R(m), R(n);
	s = 0;
	t = (m + 1) * n + 1;
	int x;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1 ; j <= m; ++j) {
			R(x);
			for (int k = 1; k <= n; ++k) {
				create(i, j * n + k, 1, x * k);
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		create(s, i, 1, 0);
	}
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			create(i * n + j, t, 1, 0);
		}
	}
	double ans;
	ans = feiyong(s, t, t + 1).second;
	printf("%0.2lf", ans / n);
	return 0;
}
