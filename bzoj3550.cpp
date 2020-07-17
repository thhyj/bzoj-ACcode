
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
const long long inf = 9187201950435737471;
struct node {
	int to, pa, c, w;
	node (int to, int c, int pa, int w): to(to), c(c), pa(pa), w(w) {}
	node() {}
};
std::vector<node> q[1000];
long long dis[1005];
int pree[1005], pre[1005];
bool vis[1005];
deque<int>que;
inline void create(int x, int y, int c, int w) {
	q[x].push_back(node(y, c, q[y].size(), w));
	q[y].push_back(node(x, 0, q[x].size() - 1, -w));
}
#define pll pair<long long,long long>
inline pll feiyongliu(int s, int t, int n) {
	pll ans = make_pair(0, 0);
	while (1) {
		memset(dis, 127, sizeof(dis));
		memset(vis, 0 , sizeof(vis));
		dis[s] = 0;
		que.push_back(s);
		int x;
		vis[s] = 1;
		node *p;
		while (!que.empty()) {
			x = que.front();
			que.pop_front();
			vis[x] = 0;
			for (int i = 0 ; i < q[x].size(); ++i) {
				p = &q[x][i];
				if (dis[p->to] > dis[x] + p->w && p->c) {
					dis[p->to] = dis[x] + p->w;
					if (!vis[p->to]) {
						vis[p->to] = 1;
						que.push_back(p->to);
					}
					pre[p->to] = x;
					pree[p->to] = i;
				}
			}
		}
		if (dis[t] == inf) break;
		long long flow = inf;
		for (int i = t; i != s; i = pre[i]) {
			flow = min(flow, (long long)q[pre[i]][pree[i]].c);
		}
		ans.first += flow, ans.second += flow * dis[t];
		for (int i = t; i != s; i = pre[i]) {
			p = &q[pre[i]][pree[i]];
			p->c -= flow;
			q[p->to][p->pa].c += flow;
		}
	}
	return ans;
}
int v[1005];
int n, m;
int s, t, ss, tt;
int main() {
	R(n), R(m);
	int x, y, c, w;
	for (int i = 1; i <= 3 * n; ++i) {
		R(v[i]);
	}
	s = 0, t = 2 * n + 2, ss = 2 * n + 3, tt = 2 * n + 4;
	create(ss, s, m, 0);
	create(t, tt, m, 0);
	create(s, 1, m, 0);
	for (int i = 1; i <= n; ++i) {
		create(s, i, 1, -v[i]);
		create(i, i + n, 1, -v[i + n]);
		create(i + n, t, 1, -v[i + n + n]);
		create(i + n + n, t, 1, 0);
	}
	for (int i = 1; i <= 2 * n; ++i) {
		create(i, i + 1, m, 0);
	}
	create(2 * n + 1, t, m, 0);
	s = 1, t = n;
	pll temp = feiyongliu(ss, tt, tt + 1);
	cout << -temp.second << '\n';
	return 0;
}
