
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
}
std::vector<int> q[10005];
int vis[10005], zhi[10005];
bool exist[10005];
typedef pair<int, int> pii;
#define mk make_pair
set<pii>dui;
int main() {
	
	int n, m;
	R(n), R(m);
	int x, y;
	for (int i = 1; i <= m; ++i) {
		R(x), R(y);
		q[x].push_back(y), q[y].push_back(x);
	}
	pii t;
	for (int i = 1;  i <= n; ++i) {
		dui.insert(mk(0, i));
	}
	int v;
	memset(vis, -1, sizeof(vis));
	while (!dui.empty()) {
		t = *(--dui.end());
	//	printf("t.first = %d, t.second = %d\n", t.first, t.second);
		dui.erase(t);
		vis[t.second] = t.first;
		for (int i = 0; i < q[t.second].size(); ++i) {
			v = q[t.second][i];
			if (vis[v] == -1) {
				dui.erase(mk(zhi[v], v));
				zhi[v]++;
				dui.insert(mk(zhi[v], v));
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans += exist[vis[i]] == 0;
		exist[vis[i]] = 1;
	}
	cout << ans << '\n';
}
