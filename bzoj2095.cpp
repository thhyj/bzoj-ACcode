
#include <bits/stdc++.h>
using namespace std;
#define getchar getchar_unlocked
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
const int inf = INT_MAX;
struct node {
	int to , length, pa;
	node(int to, int length, int pa): to(to), length(length), pa(pa) {}
	node() {}
};
std::vector<node> q[10005];
inline void create(int x, int y, int z) {
	q[x].push_back(node(y, z, q[y].size()));
	q[y].push_back(node(x, 0, q[x].size() - 1));
}
int dis[10005], gap[10005];
int temp[10005];
bool vis[10005];
int a[2005], b[2005], c[2005], d[2005];
int in[2005], out[2005];
int fa[2005], siz[2005];
int s, t;
inline void bfs() {
	static queue<int>que;
	gap[0]++;
	vis[t] = 1;
	que.push(t);
	int x;
	node *p;
	while (!que.empty()) {
		x = que.front();
		que.pop();
		for (int i = 0; i < q[x].size(); ++i) {
			p = &q[x][i];
			if (!vis[p->to]) {
				vis[p->to] = 1;
				que.push(p->to);
				dis[p->to] = dis[x] + 1;
				gap[dis[p->to]]++;
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
			f =	sap(p->to, min(flow - ret, p->length), n);
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
	while (dis[s] < n ) ret += sap(s, inf, n);
	return ret;
}
int cnt;
inline int getfather(int x) {
	return x == fa[x] ? x : (fa[x] = getfather(fa[x]));
}
inline void merge(int x, int y) {
	int fx = getfather(x), fy = getfather(y);
	if (fx == fy) return;
	if (siz[fx] < siz[fx]) swap(fx, fx);
	fa[fy] = fx;
	siz[fx] += siz[fy];
}
int n, m;
inline bool check(int mid) {
	int x, y;
	q[s].clear(), q[t].clear();
	for (int i = 1; i <= n; ++i) fa[i] = i, siz[i] = 1, q[i].clear();
	memset(dis, 0, sizeof(dis));
	memset(gap, 0, sizeof(gap));
	memset(vis, 0, sizeof(vis));
	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));
	for (int i = 1; i <= m; ++i) {
		x = a[i], y = b[i];
		if (c[i] <= mid && d[i] <= mid) {
			merge(x, y);
			in[y]++;
			out[x]++;
			create(y, x, 1);
		} else {
			if (c[i] <= mid) {
				merge(x, y);
				in[y]++;
				out[x]++;
			} else {
				if (d[i] <= mid) {
					merge(x, y);
					in[x]++;
					out[y]++;
				}
			}
		}
	}
	if (siz[getfather(1)] != n) return 0;
	int liuy = 0, liuh = 0;;
	for (int i = 1; i <= n; ++i) {
		if ((in[i] + out[i]) & 1) return 0;
		if (in[i] > out[i]) {
			create(s, i, (in[i] - out[i]) >> 1);
			liuy += (in[i] - out[i]) >> 1;
		}
		if (out[i] > in[i]) create(i, t, (out[i] - in[i]) >> 1), liuh += (out[i] - in[i]) >> 1;
	}
	return (liuy == liuh) && (sap(t + 1) == liuy);
}
int main () {

	R(n), R(m);
	s = 0, t = n + 1;
	for (int i = 1; i <= m; ++i) {
		R(a[i]), R(b[i]), R(c[i]), R(d[i]);
	}
	int l = -1, r = 1001, mid;
	while (l < r - 1) {
		mid = l + r >> 1;
	//	printf("l = %d, r = %d, mid = %d\n", l, r, mid);
		if (check(mid)) r = mid;
		else l = mid;
	}
	if(r == 1001) {
		puts("NIE");
		return 0;
	}
	printf("%d\n", r);
	return 0;
}
