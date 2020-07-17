
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
std::vector<int> q[10005];
int n, m;
int st[10005], top;
bool inst[10005];
int indx, dfn[10005], low[10005];
bool pd;
bool vis[10005];
std::vector<int> p1;
bool pd1, pd2;
inline void dfs(int x) {
	if (pd) return;
	dfn[x] = low[x] = ++indx;
	inst[x] = 1;
	st[++top] = x;
	int v;
	for (int i = 0 ; i < q[x].size(); ++i) {
		v = q[x][i];
		if (!dfn[v]) {
			dfs(v);
			low[x] = min(low[x], low[v]);
		} else {
			if (inst[v]) low[x] = min(low[x], dfn[v]);
		}
	}
	if (low[x] == dfn[x]) {
		p1.clear();
		while (x != st[top]) {
			p1.push_back(st[top]);
			vis[st[top]] = 1;
			if (st[top] > n) {
				if (vis[st[top] - n]) {
					pd = 1;
					return;
				}
			} else {
				if (vis[st[top] + n]) {
					pd = 1;
					return;
				}
			}
			inst[st[top]] = 0;
			--top;
		}
		p1.push_back(st[top]);
		vis[st[top]] = 1;
		if (st[top] > n) {
			if (vis[st[top] - n]) {
				pd = 1;
				return;
			}
		} else {
			if (vis[st[top] + n]) {
				pd = 1;
				return;
			}
		}
		inst[st[top]] = 0;
		--top;
		for (int j = 0 ; j < p1.size(); ++j) {
			vis[p1[j]] = 0;
		}
	}
}
inline void dfs1(int x) {
	vis[x] = 1;
	int v;
	for (int i = 0 ; i < q[x].size(); ++i) {
		v = q[x][i];
		if (!vis[v]) {
			dfs1(v);
		}
	}
}
inline void create(int x, int y) {
	q[x].push_back(y);
}
int main () {
	R(n), R(m);
	int x, y;
	char ch1, ch2;
	int f1, f2;
	for (int i = 1; i <= m; ++i) {
		R(x);
		do {
			ch1 = getchar();
		} while (!isupper(ch1));
		R(y);
		do {
			ch2 = getchar();
		} while (!isupper(ch2));
		if (ch1 == 'Y' && ch2 == 'Y') {
			create(x + n, y);
			create(y + n, x);
		} else {
			if (ch1 == 'Y' && ch2 == 'N') {
				create(x + n, y + n);
				create(y, x);
			} else {
				if (ch1 == 'N' && ch2 == 'Y') {
					create(x, y);
					create(y + n, x + n);
				} else if (ch1 == 'N' && ch2 == 'N') {
					create(x, y + n);
					create(y, x + n);
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (!dfn[i]) dfs(i);
	}
	if (pd) {
		puts("IMPOSSIBLE");
		return 0;
	}
	for (int i = 1; i <= n; ++i) {
		pd1 = 1, pd2 = 1;
		memset(vis, 0, sizeof(vis));
		dfs1(i);
		for (int j = 1; j <= n; ++j) {
			if (vis[j] && vis[j + n]) {pd1 = 0; break;}
		}
		memset(vis, 0, sizeof(vis));
		dfs1(i + n);
		for (int j = 1; j <= n; ++j) {
			if (vis[j] && vis[j + n]) {pd2 = 0; break;}
		}
		if (pd1 && pd2) {
			putchar('?');
		} else {
			if (pd1) {
				putchar('Y');
			} else putchar('N');
		}
		pd1 = 0, pd2 = 0;
	}
	return 0;
}
