
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
int n, m, indx, dfn[10005], low[10005], cnt, st[10005], top, belong[10005], cd[10005], exist[10005], siz[10005];
inline void dfs(int x) {
	low[x] = dfn[x] = ++indx;
	exist[x] = 1;
	st[++top] = x;
	int v;
	for (int i = 0 ; i < q[x].size(); ++i) {
		v = q[x][i];
		if (!dfn[v]) {
			dfs(v);
			low[x] = min(low[x], low[v]);
		}
		if (exist[v]) {
			low[x] = min(low[x], dfn[v]);
		}
	}
	if (low[x] == dfn[x]) {
		++cnt;
		while (st[top] ^ x) {
			belong[st[top]] = cnt;
			++siz[cnt];
			--top;
		}
		belong[st[top]] = cnt;
		--top;
		++siz[cnt];
	}
}
int main () {
	R(n), R(m);
	int x, y;
	for (int i = 1; i <= m; ++i) {
		R(x), R(y);
		q[x].push_back(y);
		//q[y].push_back(x);
	}
	for (int i = 1; i <= n; ++i) {
		if (!dfn[i]) {
			dfs(i);
		}
	} for (int x = 1; x <= n; ++x) {
		for (int i = 0 ; i < q[x].size(); ++i) {
			int v = q[x][i];
			if (belong[v] != belong[x]) {
				++cd[x];
			}
		}
	}
	int tottt = 0, temp;
	for (int i = 1; i <= cnt; ++i) {
		if (!cd[i]) ++tottt, temp = i;
	}
	if (tottt > 1) {
		puts("0");
		return 0;
	}
	cout << siz[temp];
	return 0;
}
