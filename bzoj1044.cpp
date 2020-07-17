
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
int a[500005], sum[500005];
inline bool check(int mid) {
	int tot = 0, len = 0;
	for (int i = 1; i <= n; ++i) {
		len += a[i];
		while (len > mid) {
			++tot, len = a[i];
			if (tot > m) return 0;
		}
	}
	return 1;
}
int pos[500005];
int f[500005][2], g[500005][2], ma;
const int mod = 10007;
int main() {
	R(n), R(m);
	for (int i = 1; i <= n; ++i) {
		R(a[i]);
		sum[i] = sum[i - 1] + a[i];
		ma = max(ma, a[i]);
	}
	int l = ma - 1, r = sum[n], mid;
	while (l < r - 1) {
		mid = l + r >> 1;
		if (check(mid)) r = mid;
		else l = mid;
	}
	printf("%d ", r);
	int now = 0;
	for (int i = 1; i <= n; ++i) {
		if(sum[i] <= r) f[i][0] = 1;
		while (sum[i] - sum[now] > r) ++now;
		if (sum[i] - sum[now] <= r) pos[i] = now;
	//	printf("pos[%d] = %d\n", i, pos[i]);
	}
	now = 0;
	int ans = 0;
	while (m--) {
		for (int i = 1; i <= n; ++i) {
			g[i][now] = (g[i - 1][now] + f[i][now]) % mod;
		}
		now ^= 1;
		for (int i = 1; i <= n; ++i) {
			f[i][now] = (g[i - 1][now ^ 1] - g[max(pos[i] - 1, 0)][now ^ 1] + mod) % mod;
		}
		ans = (ans + f[n][now]) % mod;
	}
	printf("%d\n", ans);
}
