
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
struct node {
	int to, length, pa, w;
	node(int to, int length, int pa, int w): to(to), length(length), pa(pa) , w(w) {}
	node() {}
};
const int inf = INT_MAX;
std::vector<node> q[1005];
int dis[1005], pree[1005], pre[1005];
bool vis[1005];
inline void create(int x, int y, int c, int w) {
	q[x].push_back(node(y, c, q[y].size(), w));
	q[y].push_back(node(x, 0, q[x].size() - 1, -w));
}
#define pii pair<int ,int>
#define mk make_pair
inline pii sap(int s, int t, int n) {
	pii ans = mk(0, 0);
	static queue<int> que;
	while (1) {
		memset(dis, 63, sizeof(dis));
		que.push(s);
		vis[s] = 1;
		int x;
		node *p;
		dis[s] = 0;
		while (!que.empty()) {
			x = que.front();
			que.pop();
			vis[x] = 0;
			for (int i = 0; i < q[x].size(); ++i) {
				p = &q[x][i];
				if (dis[p->to] > dis[x] + p->w && p->length) {
					dis[p->to] = dis[x] + p->w;
					if (!vis[p->to]) {
						que.push(p->to);
						vis[p->to] = 1;
					}
					pre[p->to] = x;
					pree[p->to] = i;
				}
			}
		}
		if (dis[t] == 0x3f3f3f3f) break;
		int flow = INT_MAX;
		for (int i = t; i != s; i = pre[i]) {
			flow = min(flow, q[pre[i]][pree[i]].length);
		}
		ans.first += flow, ans.second += flow * dis[t];
		for (int i = t; i != s; i = pre[i]) {
			p = &q[pre[i]][pree[i]];
			p->length -= flow;
			q[p->to][p->pa].length += flow;
		}
	}
	return ans;
}
int main () {
	int s = 1, t = 1000, ss = 1001, tt = 1002, n;
	R(n);
	int k, x, y;
	for (int i = 1; i <= n; ++i) {
		R(k);
		create(i, 1, inf, 0);
		create(i, tt, k, 0);
		for (int j = 1; j <= k; ++j) {
			R(x), R(y);
			create(ss, x, 1, y);
			create(i, x, inf, y);
		}
	}
	pii temp = sap(ss, tt, n + 3);
	printf("%d\n", temp.second);
	return 0;
}
