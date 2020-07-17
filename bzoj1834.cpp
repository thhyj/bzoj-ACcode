
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
	int to, length, w, pa;
	node(int to, int length, int w, int pa): to(to), length(length), w(w), pa(pa) {}
	node() {}
};
vector<node>q[1005];
inline void create(int u, int v, int c, int w) {
	q[u].push_back(node(v, c, 0, q[v].size()));
	q[v].push_back(node(u, 0, 0, q[u].size() - 1));
}
int h[1005], gap[1005], temp[1005];
const int inf = 2100000000;
inline int sap(int x, int t, int flow, int n) {
	if (x == t) return flow;
	int ret = 0;
	node *p;
	int f;
	for (int i = temp[x]; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (h[p->to] + 1 == h[x] && p->length) {
			f = sap(p->to, t, min(flow - ret, p->length), n);
			p->length -= f;
			q[p->to][p->pa].length += f;
			temp[x] = i;
			if ((ret += f) == flow) return ret;
		}
	}
	temp[x] = 0;
	if (!(--gap[h[x]])) h[1] = n;
	gap[++h[x]]++;
	return ret;
}
inline void create1(int u, int v, int c, int w) {
	q[u].push_back(node(v, c, w, q[v].size()));
	q[v].push_back(node(u, 0, -w, q[u].size() - 1));
}
const long long INF = 9187201950435737471;
const int MAXN = 5005 ;
inline pair<int, int> feiyong (int s, int t, int n) {
	long long dis[MAXN];
	int prev[MAXN], pree[MAXN];
	bool vis[MAXN];
	pair<int, int>ans = pair<int, int> {0, 0};
	queue<int>que;
	while (1) {
	//	cout<<233;
		memset(dis, 127, sizeof(dis));
		memset(vis, 0 , sizeof(vis));
		dis[s] = 0;
		que.push(s);
		int x;
		node *p;
		while (!que.empty()) {
			x = que.front();
			que.pop();
			vis[x] = 0;
			for (int i = 0; i < q[x].size(); ++i) {
				p = &q[x][i];
				if (p->w + dis[x] < dis[p->to] && p->length) {
					dis[p->to] = dis[x] + p->w;
					if (!vis[p->to])
						vis[p->to] = 1, que.push(p->to);
					prev[p->to] = x;
					pree[p->to] = i;
				}
			}
		}
		if (dis[t] == INF) break;
	//	cout<<"dis[t]="<<dis[t]<<'\n';
		int flow = INT_MAX;
		for (register int i = t; i ^ s; i = prev[i]) {
	//		printf("i=%d, prev[%d]=%d, q[%d][%d].length=%d\n",i,i,prev[i],prev[i],pree[i],q[prev[i]][pree[i]].length);
			flow = min(flow, q[prev[i]][pree[i]].length);
		}
	//	cout<<"flow="<<flow<<'\n';
		ans.first += flow, ans.second += flow * dis[t];
		for (register int i = t; i ^ s; i = prev[i]) {
			p = &q[prev[i]][pree[i]];
			p->length -= flow;
			q[p->to][p->pa].length += flow;
		}
	}
	return ans;
}
int main () {
//	freopen("in.in", "r", stdin);
	int n, m, k;
	R(n), R(m), R(k);
	int u[5005], v[5005], c[5005], w[5005];
	for (int i = 1; i <= m; ++i) {
		R(u[i]), R(v[i]), R(c[i]), R(w[i]);
		create(u[i], v[i], c[i], 0);
	}
	gap[1] = n;
	int ans = 0;
	while (h[1] < n) ans += sap(1, n, inf, n);
	printf("%d ", ans);
	for(int i = 1 ; i<=m ; ++i) {
		create1(u[i], v[i], inf, w[i]);
	}
	int s, t;
	s = 0;
	t = n;
	create1(s, 1 ,k, 0);
	//printf("q[0][0].length=%d, q[0][0].to=%d\n",q[0][0].length,q[0][0].to);
	pair<int,int> ans1 = feiyong(s, t ,t + 1);
	printf("%d",ans1.second);
	return 0;
}
