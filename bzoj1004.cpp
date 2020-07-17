
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
int sr, sb, sg;
int m, p;
int n;
int zhihuan[105];
bool vis[105];
int cnt[105];
int tot;
int f[25][25][25];
inline int ksm(int x, int y) {
	int ret = 1;
	while (y) {
		if (y & 1) ret = ret * x % p;
		x = x * x % p;
		y >>= 1;
	}
	return ret;
}
inline long long dp() {
	memset(f, 0, sizeof(f));
	f[0][0][0] = 1;
	for (int i = 1; i <= tot; ++i) {
		//	printf("cnt[%d] = %d\n", i, cnt[i]);
		for (int j = sr; j >= 0; --j) {
			for (int k = sb; k >= 0; --k) {
				for (int l = sg; l >= 0; --l) {
					if (j >= cnt[i]) f[j][k][l] = (f[j][k][l] + f[j - cnt[i]][k][l]) % p;
					if (k >= cnt[i]) f[j][k][l] = (f[j][k][l] + f[j][k - cnt[i]][l]) % p;
					if (l >= cnt[i]) f[j][k][l] = (f[j][k][l] + f[j][k][l - cnt[i]]) % p;
				}
			}
		}
	}
	return f[sr][sb][sg];
}
int main () {
	R(sr), R(sb), R(sg), R(m), R(p);
	n = sr + sb + sg;
	long long ans = 0;
	for (int i = 1 ; i <= m; ++i) {
		for (int j = 1; j <= n; ++j)
			R(zhihuan[j]);
		memset(vis, 0, sizeof(vis));
		memset(cnt, 0, sizeof(cnt));
		tot = 0;
		for (int j = 1; j <= n; ++j) {
			if (!vis[j]) {
				++tot;
				++cnt[tot];
				vis[j] = 1;
				int t = zhihuan[j];
				while (!vis[t]) {
					++cnt[tot];
					vis[t] = 1;
					t = zhihuan[t];
				}
			}
		}
		ans = (ans + dp()) % p;
		//	cout<<"ans = "<<ans<<'\n';
	}
	for (int j = 1; j <= n; ++j)
		zhihuan[j] = j;
	memset(vis, 0, sizeof(vis));
	memset(cnt, 0, sizeof(cnt));
	tot = 0;
	for (int j = 1; j <= n; ++j) {
		if (!vis[j]) {
			++tot;
			++cnt[tot];
			vis[j] = 1;
			int t = zhihuan[j];
			while (!vis[t]) {
				++cnt[tot];
				vis[t] = 1;
				t = zhihuan[t];
			}
		}
	}
	ans = (ans + dp()) % p;
	//	cout<<"ans = "<<ans<<'\n';
	++m;
	cout << (ans * (ksm(m, p - 2))) % p;
	return 0;
}
