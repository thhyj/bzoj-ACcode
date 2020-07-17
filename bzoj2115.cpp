
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
inline void R (unsigned long long &v) {
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
	int to, pa;
	unsigned long long length;
	node(int to, unsigned long long length, int pa): to(to), length(length), pa(pa) {}
	node();
};
std::vector<node> q[50005];
inline void create(int x, int y, unsigned long long z) {
	q[x].push_back(node(y, z, q[y].size()));
	q[y].push_back(node(x, z, q[x].size() - 1));
}
int n, m;
unsigned long long a[250005], d[50005];
bool vis[50005];
int cnt;
inline void dfs(int x, int fa) {
//	printf("x = %d\n", x);
	node *p;
	vis[x] = 1;
	for (int i = 0 ; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (p->to != fa) {
			if (!vis[p->to]) {
				d[p->to] = d[x] ^ p->length;
				dfs(p->to, x);
			} else  a[++cnt] = d[x] ^ d[p->to] ^ p->length;
		}
	}
}
unsigned long long o[150005];
vector<unsigned long long>v;
inline void xianxingji() {
	for (int i = 1; i <= cnt; ++i) {
		for (int j = 60; j >= 0; --j) {
			if (!(a[i] & (1ll << j))) continue;
			if (o[j]) a[i] ^= o[j];
			else {
				for (int k = 0; k < j; ++k) {
					if ((a[i] & (1ll << k))) a[i] ^= o[k];
				}
				for (int k = j + 1; k <= 60; ++k) {
					if (o[k] & (1ll << j)) o[k] ^= a[i];
				}
				o[j] = a[i];
				break;
			}
		}
	}
	v.clear();
	for (int i = 0; i <= 60; i++)  v.push_back(a[i]);
}
int main () {
	R(n), R(m);
	int x , y;
	unsigned long long z;
	for (int i = 1; i <= m; ++i) {
		R(x), R(y), R(z);
		create(x, y , z);
	}
	dfs(1, 1);
	xianxingji();
	unsigned long long ans = d[n];
//	cout << "ans =" << ans << '\n';
	for (int i = 0; i < int(v.size()); i++) if ((ans ^ v[i]) > ans) ans ^= v[i];
	cout << ans;
	return 0;
}
