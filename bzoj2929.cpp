
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
int s, t;
struct node {
	int to, length, pa;
	node(int to , int length, int pa) : to(to), length(length), pa(pa) {}
	node() {}
};
std::vector<node> q[205];
int temp[205], gap[205], h[205];
bool vis[205];
const int inf = 2100000000;
queue<int>que;
inline void bfs() {
	vis[t] = 1;
	que.push(t);
	gap[0]++;
	int j;
	node *p;
	while (!que.empty()) {
		j = que.front();
		que.pop();
		for (int i = 0; i < q[j].size(); ++i) {
			p = &q[j][i];
			if (!vis[p->to]) {
				vis[p->to] = 1;
				h[p->to] = h[j] + 1;
				gap[h[p->to]]++;
				que.push(p->to);
			}
		}
	}
}
inline int sap(int x, int flow, int n) {
	if (x == t) return flow;
	int ret = 0, f;
	node *p;
	for (int i = temp[x]; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (p->length && h[p->to] + 1 == h[x]) {
			f = sap(p->to, min(flow - ret, p->length), n);
			p->length -= f;
			q[p->to][p->pa].length += f;
			temp[x] = i;
			if ((ret += f) == flow || h[s] >= n) return ret;
		}
	}
	temp[x] = 0;
	if (!(--gap[h[x]])) h[s] = n;
	gap[++h[x]]++;
	return ret;
}
inline int sap(int n) {
	int ret = 0;
	bfs();
	while (h[s] < n) ret += sap(s, inf , n);
	return ret;
}
inline void create(int x, int y, int z) {
	q[x].push_back(node(y, z, q[y].size()));
	q[y].push_back(node(x, 0, q[x].size() - 1));
}
int main () {
	int n;
	R(n);
//	cout<<"n="<<n<<'\n';
	s = 1; t = n;
	int m;
	int x, y, z;
	for (int i = 1 ; i < n; ++i) {
		if (i == 1) {
			R(m);
			for (int j = 1; j <= m; ++j) {
				R(x);
				create(i, x, 1);
			}
		} else {
			R(m);
			for (int j = 1; j <= m; ++j) {
				R(x);
				if (x == t) create(i, t, 1); else create(i, x, inf);
			}
		}
	}
	int ans = sap(n);
	cout << ans;
}
