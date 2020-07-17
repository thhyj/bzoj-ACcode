
#include <bits/stdc++.h>
using namespace std;
const int inf = 2100000000;
inline char read() {
	static const int IN_LEN = 1000000;
	static char buf[IN_LEN], *s, *t;
	if (s == t) {
		t = (s = buf) + fread(buf, 1, IN_LEN, stdin);
		if (s == t) return -1;
	}
	return *s++;
}

template<class T>
inline void R(T &x) {
	static bool iosig;
	static char ch;
	for (iosig = false, ch = read(); !isdigit(ch); ch = read()) {
		if (ch == -1) return;
		if (ch == '-') iosig = true;
	}
	for (x = 0; isdigit(ch); ch = read())
		x = (x + (x << 2) << 1) + (ch ^ 48);
	if (iosig) x = -x;
}
struct node {
	int to, length, pa;
	node(int to, int length, int pa): to(to), length(length), pa(pa) {}
	node() {}
};
std::vector<node> q[1000005];
inline void create(int x , int y, int z) {
	q[x].push_back(node(y, z, q[y].size()));
	q[y].push_back(node(x, 0, q[x].size() - 1));
}
queue<int>que;
bool vis[1000005];
int s, t;
int h[1000005], gap[1000005], temp[1000005];
inline void bfs() {
	que.push(t);
	vis[t] = 1;
	gap[0]++;
	node *p;
	int j;
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
inline int sap(int x, int flow , int n) {
	if (x == t) return flow;
	int ret = 0, f;
	node *p;
	for (int i = temp[x]; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (h[p->to] + 1 == h[x] && p->length) {
			f = sap(p->to, min(flow - ret, p->length), n);
			p->length -= f;
			q[p->to][p->pa].length += f;
			if ((ret += f) == flow || h[s] >= n) return ret;
		}
	}
	temp[x] = 0;
	if (!(--gap[h[x]])) h[s] = n;
	gap[++h[x]]++;
	return ret;
}
int ans;
inline int sap(int n) {
	int ret = 0;
	bfs();
	while (h[s] < n) ret += sap(s, inf, n);
	return ret;
}
int main () {
//	freopen("in.in", "r", stdin);
	int n, m ;
	R(n), R(m);
	s = 0;
	t = n + m + 1;
	int x, y, z;
	for (int i = 1; i <= n; ++i) {
		R(x);
		create(s, i, x);
		//ret+=x;
	}
	for (int i = 1; i <= m; ++i) {
		R(x), R(y), R(z);
		create(x, i + n, inf);
		create(y, i + n, inf);
		create(i + n, t, z);
		ans += z;
	}
	cout << ans - sap(t + 1);
	return 0;
}
