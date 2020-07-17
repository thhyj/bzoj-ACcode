
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
	if (p)v = -v;
}
char s[2000005], a[1000005];
int n;
int mx, id, p[2000005];
int fa[2000005];
std::vector<pair<int, int> > e;
inline int getfather(int x) {
	return (fa[x] == x) ? x : (fa[x] = getfather(fa[x]));
}
std::vector<int> q[2000005];
inline void create(int x, int y) {
	q[x].push_back(y);
	q[y].push_back(x);
}
inline void manacher() {
	for (int i = 0 ; i <= n * 2; ++i) {
		if (i <= mx) {
			p[i] = min(mx - i + 1, p[id + id - i]);
		} else p[i] = 1;
		while (s[i + p[i]] == s[i - p[i]]) {
			fa[getfather(i + p[i])] = getfather(i - p[i]);
			++p[i];
		}
		if (i + p[i] - 1 > mx) {
			mx = i + p[i] - 1;
			id = i;
		}
		e.push_back(make_pair(i - p[i], i + p[i]));
	}
}
bool col[2000005];
int vis[2000005];
const int mod = 1000000007;
int main () {
	scanf("%s", a);
	n = strlen(a);
	for (int i = 0; i < n; ++i) {
		s[i << 1] = '#', s[i << 1 | 1] = a[i];
	}
	s[0] = '@';
	s[n << 1] = '*';
	for (int i = 1; i <= n * 2; ++i) {
		fa[i] = i;
	}
	manacher();
	for (int i = 0; i < e.size(); ++i) {
		create(getfather(e[i].first), getfather(e[i].second));
	}
	int cnt;
	int v;
	long long ans = 1;
	for (int i = 1; cnt = 26, i <= n * 2; i += 2) {
		if (getfather(i) != i)continue;
	//	printf("i = %d\n", i);
		col[i] = 1;
		for (int j = 0; j < q[i].size(); ++j) {
			v =  q[i][j];
			if (col[v] && vis[v] < i) {
				vis[v] = i;
				--cnt;
			}
		}
		if (cnt <= 0) ans = 0;
		ans = (long long) ans * cnt % mod;
	//	printf("cnt = %d\n", cnt);
	}
	cout << ans << '\n';
}
