
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
struct point {
	double x, y;
	point (double x, double y): x(x), y(y) {}
	point() {}
} wy[205], jl[205], sm[205];
double r[205];
double fw[205], jg[205];
struct node {
	int to, length, pa;
	node (int to, int length, int pa): to(to), length(length), pa(pa) {}
	node() {}
};
std::vector<node> q[2005];
inline void create(int x, int y , int z) {
	q[x].push_back(node(y, z, q[y].size()));
	q[y].push_back(node(x, 0, q[x].size() - 1));
}
int s, t;
bool vis[2005];
int gap[2005], h[2005];
inline void bfs() {
	gap[0]++;
	static queue<int>que;
	que.push(t);
	int j;
	node *p;
	vis[t] = 1;
	while (!que.empty()) {
		j = que.front();
		que.pop();
		for (int i = 0; i < q[j].size(); ++i) {
			p = &q[j][i];
			if (!vis[p->to]) {
				vis[p->to] = 1;
				que.push(p->to);
				h[p->to] = h[j] + 1;
				gap[h[p->to]]++;
				vis[p->to] = 1;
			}
		}
	}
}
const int inf = 2100000000;
int temp[2005];
inline int sap(int x, int flow, int n) {
	if (x == t) {
		return flow;
	}
	int ret = 0, f;
	node *p;
	for (int i = temp[x]; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (h[p->to] + 1 == h[x] && p->length) {
			f = sap(p->to, min(flow - ret, p->length), n);
			p->length -= f;
			q[p->to][p->pa].length += f;
			temp[x] = i;
			if ((ret += f) == flow || h[x] >= n) return temp[x] = 0, ret;
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
bool ma[205][205];
double dis, height, touying;
inline double operator *(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}
inline point operator -(const point &a, const point &b) {
	return point(a.x - b.x, a.y - b.y);
}
inline double dot (const point &a, const point &b) {
	return a.x * b.x + a.y * b.y;
}
inline double getdis(const point &a, const point &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
inline bool check (const point &a, const point &b, const point &t, double r) {
	dis = getdis(a, t);
	touying = dot(t - a, b - a) / getdis(a, b);
	height = sqrt(dis * dis - touying * touying);
	if (height >= r) return 1;
	if (touying >= 0 && touying <= getdis(a, b)) return 0;
	return (dis >= r && getdis(b, t) >= r);
}
bool able[2005];
int main () {
	//freopen("in.in", "r", stdin);
	//freopen("out.out","w",stdout);
	int n, m, T;
	R(n), R(m), R(T);
	for (int i = 1; i <= n; ++i) {
		scanf("%lf%lf%lf%lf", &wy[i].x, &wy[i].y, &fw[i], &jg[i]);
	}
	for (int i = 1; i <= m; ++i) {
		scanf("%lf%lf", &jl[i].x, &jl[i].y);
	}
	for (int i = 1; i <= T; ++i) {
		scanf("%lf%lf%lf", &sm[i].x, &sm[i].y, &r[i]);
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (getdis(wy[i], jl[j]) <= fw[i]) {
				for (int k = 1; k <= T; ++k) {
					if (!check(wy[i], jl[j], sm[k], r[k])) {goto end;}
					//if (ins(wy[i], jl[j], sm[k], r[k]))goto end;
				}
				able[j] = 1;
				ma[i][j] = 1;
end:;
			}
		}
	}
	for (int i = 1; i <= m; ++i) if (!able[i]) {
			puts("-1");
			return 0;
		}
	int l = -1, r = 1e9, mid;
	s = 0, t = n + m + 1;
	int ans;
	while (l < r - 1) {
		memset(q, 0, sizeof(q));
		memset(h, 0 , sizeof(h));
		memset(gap, 0, sizeof(gap));
		memset(vis, 0, sizeof(vis));
		mid = l + r >> 1;
		//printf("mid=%d\n", mid);
		//	cout<<"n="<<n<<" m="<<m<<'\n';
		for (int i = 1; i <= n; ++i) {
			//	printf("mid/jg[%d]+1=%d\n", i, mid / (int)jg[i] + 1);
			create(s, i, mid / (int)jg[i] + 1);
		}
		for (int i = 1; i <= m; ++i) {
			create(i + n, t, 1);
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (ma[i][j]) {
					//	printf("ma[%d][%d] = 1\n", i, j);
					create(i, j + n, 1);
				}
			}
		}
		//for (int i = 1; i <= n; ++i) {
		//	for (int j = 0; j < q[i].size(); ++j) {
		//		printf("q[%d][%d].to = %d, q[%d][%d].length = %d\n", i, j, q[i][j].to, i, j, q[i][j].length);
		//	}
		//}
		//cout << "t=" << t << '\n';
		ans = sap(t + 1);
		//cout << "tot=" << q[t].size() << '\n';
		//cout << "ans=" << ans << '\n';
		if (ans == m) r = mid; else l = mid;
	}
	printf("%d\n", r);
	return 0;
}

