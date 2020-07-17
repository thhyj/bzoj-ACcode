
#include <bits/stdc++.h>
using namespace std;
inline void R (long long &v) {
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
long long n;
long long lef;
long long cnt;
long long ans;
long long m;
long long mod;
inline long long ksm(long long x, long long y) {
	long long ret = 1;
	while (y) {
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}
long long jiecheng[105];
long long val[105], num[105];

long long dfs(long long now, long long left) {
	if (left == 0) {
		long long xunhuanjie = 0, zhihuan = 1;
		for (long long i = 1; i <= cnt; ++i) {
			xunhuanjie = xunhuanjie + (num[i] * (num[i] - 1)) / 2 * val[i] + (val[i] / 2 * num[i]);
			for (long long j = i + 1; j <= cnt; ++j) {
				xunhuanjie = xunhuanjie + num[i] * num[j] * __gcd(val[i], val[j]);
			}
			zhihuan = zhihuan * ksm(val[i], num[i]) % mod * jiecheng[num[i]] % mod;
		}
		ans = (ans + (long long)ksm(m, xunhuanjie) * jiecheng[n] % mod * ksm(zhihuan, mod - 2) % mod) % mod;
	}
	if (now < left) dfs(now + 1, left);
	for (long long i = 1 ; i * now <= left; ++i) {
		val[++cnt] = now;
		num[cnt] = i;
		dfs(now + 1, left - now * i);
		--cnt;
	}
}
char s[105];
int main () {
	R(n); R(m), R(mod);
	jiecheng[0] = 1;
	for (long long i = 1; i <= 100; ++i) {
		jiecheng[i] = jiecheng[i - 1] * i % mod;
	}
	dfs(1, n);
	cout << ans * ksm(jiecheng[n], mod - 2) % mod << '\n';
	return 0;
}
