
#include <bits/stdc++.h>
using namespace std;
inline void R (int &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
		ch = getchar();
		if (ch == '-')p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = (v + (v << 2) << 1) + (ch^'0');
		ch = getchar();
	}
	if (p)v = -v;
}
struct node {
	int to, length, pa;
	node(int to, int length, int pa): to(to), length(length), pa(pa) {}
	node() {}
};
std::vector<node> q[1005];
int s, t;
char a[10005];
const int inf = 2100000000;
inline void create(int x, int y, int z) {
	q[x].push_back(node(y, z, q[y].size()));
	q[y].push_back(node(x, 0, q[x].size() - 1));
}
queue<int>que;
bool vis[10005];
int gap[10005], h[10005], temp[10005];
inline void bfs() {
	gap[0]++;
	que.push(t);
	int x;
	node *p;
	vis[t] = 1;
	while (!que.empty()) {
		x = que.front();
		que.pop();
		for (int i = 0; i < q[x].size(); ++i) {
			p = &q[x][i];
			if (!vis[p->to]) {
				vis[p->to] = 1;
				h[p->to] = h[x] + 1;
				gap[h[p->to]]++;
				que.push(p->to);
			}
		}
	}
}
inline int sap(int x, int flow, int n) {
	if (x == t) return flow;
	int ret = 0;
	node *p;
	int f;
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
	while (h[s] < n) ret += sap(s, inf, n);
	return ret;
}
int ma[35][35];
int main() {
//	freopen("in.in","r", stdin);
	int m, n;
	R(n);
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			R(ma[i][j]);
			ans += ma[i][j];
		}
	}
	s = 0, t = n * n + 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (((i + j) & 1) == 0) {
		//		printf("i=%d, j=%d, (i - 1)*n + j=%d\n",i,j,(i - 1)*n + j );
				if (i > 1) create((i - 1)*n + j, (i - 2)*n + j, inf);
				if (i < n) create((i - 1)*n + j, i * n + j, inf);
				if (j > 1) create((i - 1)*n + j, (i - 1) * n + j - 1, inf);
				if (j < n) create((i - 1)*n + j, (i - 1) * n + j + 1, inf);
				create(s, (i - 1)*n + j, ma[i][j]);
			} else {
			//	printf("i=%d, j=%d, (i - 1)*n + j=%d\n",i,j,(i - 1)*n + j );
				create((i - 1)*n + j, t, ma[i][j]);
			}
		}
	}
	cout << ans - sap(t + 1);
}
