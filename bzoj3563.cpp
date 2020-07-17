
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
int n, m;
std::vector< pair<int, int> > q[100005];
int k[50005];
int c[25];
bool vis[500005], fangwen[100005];
int tot[50005];
int sum;
inline void dfs(int x, int f) {
	pair<int , int> p;
	fangwen[x] = 1;
	++sum;
	for (int i = 0; i < q[x].size(); ++i) {
		p = q[x][i];
		if (p.first == f || vis[p.second] || fangwen[p.first]) continue;
		dfs(p.first, x);
	}
}
int ans[50005];
int main () {
	R(n), R(m);
	int x, y;
	for (int i = 1; i <= m; ++i) {
		R(x), R(y);
		q[x].push_back(make_pair(y, i));
		q[y].push_back(make_pair(x, i));
	}
	int Q;
	R(Q);
	char ch;
	int v;
	for (int i = 1; i <= Q; ++i) {
		R(k[i]);
		while (1) {
			v = 0;
			do {
				ch = getchar();
				if (ch == '\n') goto end;
			} while (!isdigit(ch));
			while (isdigit(ch)) {
				v = (v + (v << 2) << 1) + (ch^'0');
				ch = getchar();
			}
			c[++tot[i]] = v;
			if (ch == '\n') goto end;
			if (0) {
end: break;
			}
		}
	//	printf("tot[%d] = %d\n", i, tot[i]);
	}
	for (int i = 2; i <= Q; ++i) {
		ans[i] = k[i] ^ tot[i];
	}
	for (int i = 1; i < Q; ++i) {
		if (ans[i + 1] > ans[i]) {
			puts("Connected");
		} else {
			puts("Disconnected");
		}
	}
	for (int i = 1; i <= tot[Q]; ++i) {
		vis[c[i] ^ ans[Q]] = 1;
	}
	dfs(1, 1);
	if (sum == n) {
		puts("Connected");
	} else {
		puts("Disconnected");
	}
	return 0;
}
