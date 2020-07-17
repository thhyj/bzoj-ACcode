
#include <bits/stdc++.h>
using namespace std;
inline void R (int &v) {
	static char ch;
	v = 0;
	bool p = 0 ;
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
	int to, length, pa;
	node(int to, int length , int pa): to(to), length(length), pa(pa) {}
	node() {}
};
vector<node>q[10005];
inline void create(int x, int y, int z) {
	q[x].push_back(node(y, z, q[y].size()));
	q[y].push_back(node(x, 0, q[x].size() - 1));
}
int gap[10005], dis[10005];
bool vis[10005];
inline void bfs(int s, int t) {
	static queue<int>que;
	que.push(t);
	memset(dis, 127, sizeof(dis));
	dis[t] = 0;
	vis[t] = 1;
	int t1;
	gap[0]++;
	node *p;
	while (!que.empty()) {
		t1 = que.front();
		que.pop();
		for (int i = 0; i < q[t1].size(); ++i) {
			p = &q[t1][i];
			if (!vis[p->to]) {
				dis[p->to] = dis[t1] + 1;
				gap[dis[p->to]]++;
				vis[p->to] = 1;
				que.push(p->to);
			}
		}
	}
}
int ans;
const int inf = INT_MAX;
int temp[10005];
inline int sap(int x, int flow, int s, int t, int n) {
	if (x == t) {
		return flow;
	}
	int ret = 0, f;
	node *p;
	for (int i = temp[x]; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (p->length && dis[p->to] + 1 == dis[x]) {
			f = sap(p->to, min(flow - ret, p->length), s, t, n);
			p->length -= f;
			q[p->to][p->pa].length += f;
			temp[x] = i;
			if ((ret += f) == flow || dis[s] >= n) return ret;
		}
	}
	temp[x] = 0;
	if (!(--gap[dis[x]])) dis[s] = n;
	gap[++dis[x]]++;
	return ret;
}
inline void sap(int s, int t, int n) {
	bfs(s, t);
	while (dis[s] < n) ans += sap(s, inf, s, t, n);
}
int n, m, a, b;
char ma[55][55];
int main () {
	R(n), R(m);
	int s = 0, t = n + 1;
	int x;
	for (int i = 1; i <= n; ++i) {
		R(x);
		if (x == 1) {
			create(s, i, 1);
		} else create(i , t , 1);
	}
	int y;
	for (int i = 1; i <= m; ++i) {
		R(x), R(y);
		create(x, y, 1);
		create(y , x, 1);
	}
	sap(s, t, t + 1);
	printf("%d\n", ans);
	return 0;
}
