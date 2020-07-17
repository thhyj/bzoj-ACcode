
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
int n;
int lef;
int cnt;
int ans;
const int mod = 997;
inline int ksm(int x, int y) {
	int ret = 1;
	while (y) {
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}
int jiecheng[105];
int val[105], num[105];

int dfs(int now, int left) {
	if (left == 0) {
		int xunhuanjie = 0, zhihuan = 1;
		for (int i = 1; i <= cnt; ++i) {
			xunhuanjie = xunhuanjie + (num[i] * (num[i] - 1)) / 2 * val[i] + (val[i] / 2 * num[i]);
			for (int j = i + 1; j <= cnt; ++j) {
				xunhuanjie = xunhuanjie + num[i] * num[j] * __gcd(val[i], val[j]);
			}
			zhihuan = zhihuan * ksm(val[i], num[i]) * jiecheng[num[i]] % mod;
		}
		ans = (ans + (long long)ksm(2, xunhuanjie) * jiecheng[n] * ksm(zhihuan, mod - 2) % mod) % mod;
	}
	if (now < left) dfs(now + 1, left);
	for (int i = 1 ; i * now <= left; ++i) {
		val[++cnt] = now;
		num[cnt] = i;
		dfs(now + 1, left - now * i);
		--cnt;
	}
}
int main () {
	R(n);
	jiecheng[0] = 1;
	for (int i = 1; i <= 100; ++i) {
		jiecheng[i] = jiecheng[i - 1] * i % mod;
	}
	dfs(1, n);
	cout << ans * ksm(jiecheng[n], mod - 2) % mod << '\n';
	return 0;
}
