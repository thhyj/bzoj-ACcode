
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
struct node {
	int to, length;
	node(int to, int length): to(to), length(length) {}
	node() {}
};
vector<node> q[100005];
int n;
int dep[100005], top[100005], son[100005], siz[100005], fa[100005], siz1[100005];
long long dis[100005];
const int inf = 0x7f7f7f7f;
inline void dfs1(int x) {
	node *p;
	siz[x] = 1;
	for (int i = 0 ; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (p->to != fa[x]) {
			dep[p->to] = dep[x] + 1;
			dis[p->to] = dis[x] + p->length;
			fa[p->to] = x;
			dfs1(p->to);
			siz[x] += siz[p->to];
			if (siz[son[x]] < siz[p->to]) son[x] = p->to;
		}
	}
}
inline void dfs2(int x) {
	int v;
	if (son[x]) {
		v = son[x];
		top[v] = top[x];
		dfs2(v);
	}
	node *p;
	for (int i = 0; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (p->to != son[x] && p->to != fa[x]) {
			top[p->to] = p->to;
			dfs2(p->to);
		}
	}
}
inline int getlca(int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		x = fa[top[x]];
	}
	return dep[x] < dep[y] ? x : y;
}
inline long long getdis(int x, int y) {
	return dis[x] + dis[y] - (dis[getlca(x, y)] << 1);
}
int rt, sum;
long long dis1[100005], dis2[100005], sum1[100005];
int d[100005];
int pre[100005];
bool vis[100005];
std::vector<pair<int, int> >  Gx[100005];
inline void findrt(int x, int fa) {
	siz1[x] = 1;
	d[x] = 0;
	node *p;
	for (int i = 0; i < q[x].size(); ++i) {
		p =  &q[x][i];
		if ((!vis[p->to]) && p->to != fa) {
			findrt(p->to, x);
			siz1[x] += siz1[p->to];
			d[x] = max(d[x], siz1[p->to]);
		}
	}
	d[x] = max(d[x], sum - siz1[x]);
//	printf("d[%d] = %d, d[%d] = %d\n", x, d[x], rt, d[rt]);
	if (d[x] < d[rt]) rt = x;
}
inline bool cmp(const pair<int ,int> &a, const pair<int ,int> &b) {
	return siz[a.second] < siz[b.second];
}
inline void divtree(int x, int fa) {
//	printf("x = %d\n",x );
	pre[x] = fa;
	vis[x] = 1;
	node *p;
	for (int i = 0; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (!vis[p->to]) {
			rt = 0;
			sum = siz1[p->to];
			findrt(p->to, x);
			Gx[x].push_back(make_pair(rt, p->to));
			divtree(rt, x);
		}
	}
	sort(Gx[x].begin(), Gx[x].end(), cmp);
}
inline void updata(int x, long long val) {
	sum1[x] += val;
	long long ds;
	for (int i = x; pre[i]; i = pre[i]) {
		ds = getdis(x, pre[i]);
		sum1[pre[i]] += val;
		dis1[pre[i]] += val * ds;
		dis2[i] += val * ds;
	}
}
inline long long calc(int x) {
	long long ret = dis1[x];
	for (int i = x; pre[i]; i = pre[i]) {
		ret += dis1[pre[i]] - dis2[i] + (sum1[pre[i]] - sum1[i]) * getdis(x, pre[i]);
	}
	return ret;
}
int last;
inline long long getans(int x) {
	int v;
	long long temp = calc(x), now = (long long)inf * inf, t;
	int pos;
	pair<int ,int> *p;
	for (int i = 0 ; i < Gx[x].size(); ++i) {
		p = &Gx[x][i];
		t = calc(p->second);
//		cout << "w = " << v << " temp = " << t << '\n';
		if (calc(p->second) < temp) {
			return getans(p->first);
		}
	}
//	cout << "x=" << x << '\n';
	return temp;
}
int q1;
inline void create(int x, int y, int z) {
	q[x].push_back(node(y, z));
	q[y].push_back(node(x, z));
}
int main() {
//	freopen("tree1.in", "r", stdin);
//	freopen("fuck.out", "w", stdout);
	d[0] = inf;
	R(n), R(q1);
	int x, y, z;
	for (int i = 1; i < n; ++i) {
		R(x), R(y), R(z);
		create(x, y, z);
	}
	dfs1(1), dfs2(1);
	rt = 0;
	sum = n;
	findrt(1, 0);
	last = rt;
	divtree(rt, 0);
//	for(int i = 1; i <= n; ++i) {
	//	for(int j = 0; j < Gx[i].size();++j) {
//			printf("Gx[%d][%d] = %d\n", i, j, Gx[i][j]);
	//	}
//	}

	for (int i = 1; i <= q1; ++i) {
		R(x), R(y);
		updata(x, y);
		cout << getans(last) << '\n';
	}
}
