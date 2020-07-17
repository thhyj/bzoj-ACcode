
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
const int MAXN = 500 ;
vector<int>q[500];
inline void create2(int x, int y) {
	q[x].push_back(y);
	q[y].push_back(x);
}
int x[205], y[205];
int dep[505], fa[505];
inline void dfs(int x, int f) {
	int v;
	fa[x] = f;
	for (int i = 0; i < q[x].size(); ++i) {
		if ((v = q[x][i]) ^ f) {
			dep[v] = dep[x] + 1;
			dfs(v, x);
		}
	}
}
inline void dfs1(int x, int mins) {
	int v;
	for (int i = 0; i < q[x].size(); ++i) {
		if ((v = q[x][i]) ^ fa[x]) {
			dep[v] -= mins;
			dfs1(v, mins);
		}
	}
}
inline void modify(int x) {
	while (x) {
		dfs1(x, dep[x]);
		x = fa[x];
	}
}
int main () {
//	freopen("chessboard.in", "r", stdin);
//	freopen("chessboard.out", "w", stdout);
	int v, n;
	R(v), R(n);
	if(n>=v*2) {
		cout<<v;
		return 0;
	}
	int l = 1, r = n, mid;
	int s = 0, t = v + 1;
	for (int i = 1; i < v; ++i) {
		R(x[i]), R(y[i]);
		++x[i], ++y[i];
		create2(x[i], y[i]);
	}
	dfs(1, 0);
	int ans = 0;
	int max1 = 0, maxp;;
	for (int i = 1; i <= v; ++i) {
		if (dep[i] > max1 && dep[i] <= n) {
			max1 = dep[i];
			maxp = i;
		}
	}
	n -= max1;
	ans += max1;
	modify(maxp);
	while (n > 0) {
		//cout<<"n="<<n<<'\n';
		max1 = 0, maxp;;
		for (int i = 1; i <= v; ++i) {
			if (dep[i] > max1 && dep[i] * 2 <= n) {
				max1 = dep[i];
				maxp = i;
			}
		}
		if(!max1)break;
		n -= max1 * 2;
		ans += max1;
		modify(maxp);
	}
	cout<<ans+1;
	return 0;
}
/*推了两个小时费用流感觉自己ZZ附体 QWQ*/
