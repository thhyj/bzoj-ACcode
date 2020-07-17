
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
vector<int> q[100005];
int n;
int dep[100005], top[100005], son[100005], siz[100005], fa[100005], siz1[100005];
const int inf = 0x7f7f7f7f;
inline void dfs1(int x) {
	int v;
	siz[x] = 1;
	for (int i = 0 ; i < q[x].size(); ++i) {
		v = q[x][i];
		if (v != fa[x]) {
			dep[v] = dep[x] + 1;
			fa[v] = x;
			dfs1(v);
			siz[x] += siz[v];
			if (siz[son[x]] < siz[v]) son[x] = v;
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
	for (int i = 0; i < q[x].size(); ++i) {
		v = q[x][i];
		if (v != son[x] && v != fa[x]) {
			top[v] = v;
			dfs2(v);
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
inline int getdis(int x, int y) {
	return y ? dep[x] + dep[y] - (dep[getlca(x, y)] << 1) : dep[x];
}
int rt;
bool vis[100005];
int d[100005], sum;
inline void findrt(int x, int fa) {
	d[x] = 0;
	siz1[x] = 1;
	int v;
	for (int i = 0; i < q[x].size(); ++i) {
		v = q[x][i];
		if ((!vis[v]) && v != fa) {
			findrt(v, x);
			siz1[x] += siz1[v];
			d[x] = max(d[x], siz1[v]);
		}
	}
	d[x] = max(d[x], sum - siz1[x]);
	if (d[x] < d[rt]) rt = x;
}
multiset<int> g[100005], f[100005], ans;
inline void calc(int x, int fa, int G, int FA) {
//	printf("x = %d, FA = %d, getdis(%d, %d) = %d\n", x, FA, x, FA, getdis(x, FA));
	f[G].insert(getdis(x, FA));
	int v;
	for (int i = 0; i < q[x].size(); ++i ) {
		v = q[x][i];
		if (v != fa && vis[v] == 0) {
			calc(v, x, G, FA);
		}
	}
}
int pre[100005];
bool open[100005];
inline void ps(int x) {
	if (g[x].size() >= 2) {
		multiset<int>::iterator iter = g[x].end();
		int temp1 = *(--iter), temp2 = * (--iter);
//		printf("x = %d, temp1 = %d, temp2 = %d\n", x, temp1, temp2);
		ans.insert(temp1 + temp2);
	}
}
inline void es(int x) {
	if (g[x].size() >= 2) {
		multiset<int>::iterator iter = g[x].end();
		ans.erase(ans.find(*(--iter) + * (--iter)));
	}
}
inline void divtree(int x, int fa) {
//	printf("G = %d\n", x);
	vis[x] = 1;
	g[x].insert(0);
	calc(x, x, x, fa);
	int v;
	for (int i = 0; i < q[x].size(); ++i) {
		v = q[x][i];
		if ((!vis[v])) {
			rt = 0;
			sum = siz1[v];
			findrt(v, x);
			///		printf("rt = %d\n", rt);
			int Gy = rt;
			divtree(rt, x);
			pre[Gy] = x;
			//	printf("f[%d].top() = %d\n", Gy, *(--f[Gy].end()));
			g[x].insert(*(--f[Gy].end()));
		}
	}
	ps(x);
}
inline void del(int x) {
	es(x);
	g[x].erase(g[x].find(0));
	ps(x);
	for (int i = x; pre[i]; i = pre[i]) {
		es(pre[i]);
		g[pre[i]].erase(g[pre[i]].find(*(--f[i].end())));
		f[i].erase(f[i].find(getdis(x, pre[i])));
		if (f[i].size()) g[pre[i]].insert(*(--f[i].end()));
		ps(pre[i]);
	}
}
inline void add(int x) {
	es(x);
	g[x].insert(0);
	ps(x);
	for (int i = x; pre[i]; i = pre[i]) {
		es(pre[i]);
		if (f[i].size())g[pre[i]].erase(g[pre[i]].find(*(--f[i].end())));
		f[i].insert(getdis(x, pre[i]));
		g[pre[i]].insert(*(--f[i].end()));
		ps(pre[i]);
	}
}
int main () {
//	freopen("hide1.in", "r", stdin);
//	freopen("hide.out","w",stdout);
	R(n);
	int x, y;
	d[0] = inf;
	for (int i = 1; i < n; ++i) {
		R(x), R(y);
		q[x].push_back(y);
		q[y].push_back(x);
	}
	dep[1] = 1;
	dfs1(1);
	dfs2(1);
	rt = 0;
	sum = n;
	findrt(1, 0);
	divtree(rt, 0);
	int Q;
	R(Q);
	char ch;
//	printf("ans.size() = %d\n", ans.size());
	for (int i = 1; i <= Q; ++i) {
		do {
			ch = getchar();
		} while (!isupper(ch));
		if (ch == 'G') {
			printf("%d\n", *(--ans.end()));
		} else {
			R(x);
			if (!open[x]) {
				open[x] = 1;
				del(x);
			} else open[x] = 0, add(x);
		}
	}
//	puts("233");
	return 0;
}
