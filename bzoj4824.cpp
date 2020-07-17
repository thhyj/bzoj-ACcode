
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
		ch  = getchar();
	}
	if (p) v = -v;
}
const int mod = 1000000007;
char s[105];
int n;
vector<int>q[105];
inline void create(int x, int y) {
	q[x].push_back(y);
}
long long siz[105], temp[105];
//long long add[1005];
long long c[105][105];
long long dp[105][105], qz[105][105];
//int rd[155];
//bool vis[155];
inline void dfs(int x) {
	siz[x] = dp[x][1] = qz[x][1] = 1;
	int v;
	for (int i = 0; i < q[x].size(); ++i) {
		v = q[x][i];
		//if (vis[v]) continue;
		dfs(v);
		//cout<<"x="<<x<<" v="<<v<<'\n';
		for (int i = 1; i <= siz[x] + siz[v]; ++i) temp[i] = 0;
		for (int i = 1; i <= siz[x]; ++i) {
			for (int j = 0; j <= siz[v]; ++j) {
				if (s[v] == '<') {
					temp[i + j] += dp[x][i] * (qz[v][siz[v]] - qz[v][j] + mod) % mod
					               * c[i + j - 1][i - 1] % mod * c[siz[x] + siz[v] - i - j][siz[x] - i] % mod;
				} else {
					temp[i + j] += dp[x][i] * qz[v][j] % mod
					               * c[i + j - 1][i - 1] % mod * c[siz[x] + siz[v] - i - j][siz[x] - i] % mod;
				}
			}
		}
		siz[x] += siz[v];
		/*temp[x] = siz[x] - 1;
		add[x] = siz[v];
		siz[x] += siz[v];
		cout << "v=" << v << '\n';
		printf("temp[%d]=%d, add[%d]=%d, siz[%d]=%d, dp[%d]=%d", x, temp[x], x, add[x], x, siz[x], x, dp[x]);
		cout << ", dp[" << v << "]=" << dp[v] << '\n';
		if (temp[x] < add[x]) swap(temp[x], add[x]);
		if (temp[x] > 0)
			dp[x] = (c[temp[x] + add[x]][add[x]] * dp[x] % mod * dp[v] % mod) % mod;
		else dp[x] = dp[v];
		cout << "dp[" << x << "]=" << dp[x] << '\n';*/
		for (int i = 1; i <= siz[x]; ++i) {
			dp[x][i] = temp[i];
			qz[x][i] = (qz[x][i - 1] + temp[i]) % mod;
		}
	}
}
int main () {
	///freopen("keyboard.in", "r", stdin);
	//freopen("keyboard.out", "w", stdout);
	R(n);
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			if (j == 0 || j == i)
				c[i][j] = 1;
			else
				c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
	//for (int i = 1; i <= 5; ++i) {
	//	for (int j = 1; j <= i; ++j) {
	//		printf("c[%d][%d]=%d\n", i, j, c[i][j]);
	//	}
	//}
	scanf("%s", s + 2);
	for (int i = 1; i <= n; ++i) {
		if ((i << 1) <= n) create(i, i << 1);
		if ((i << 1 | 1) <= n) create(i, i << 1 | 1);
	}
	dfs(1);
	cout << qz[1][siz[1]];
	return 0;
}
