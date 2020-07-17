
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
int prime[10000004];
bool heshu[10000004];
int cnt;
const int mod = 1000000007;
int f[10000005], g[10000005], e[10000005], d[10000005];
int maxp;
inline void xianshai() {
	f[1] = 1, g[1] = 1;
	int temp;
	for (int i = 2; i < maxp; ++i) {
		if (!heshu[i]) prime[cnt++] = i, f[i] = 2, g[i] = (1 + (long long)i * i) % mod, d[i] = 1, e[i] = 1;
		for (int j = 0; j < cnt && (temp = prime[j] * i) < maxp; ++j) {
			heshu[temp] = 1;
			if (i % prime[j]) {
				f[temp] = f[prime[j]] * f[i]%mod;
				g[temp] = ((long long)g[prime[j]] * g[i]) % mod;
				e[temp] = 1;
				d[temp] = i;
			}
			if (!(i % prime[j])) {
				f[temp] = ((long long)f[i] * (e[i] + 2) / (e[i] + 1))%mod;
				e[temp] = e[i] + 1;
				g[temp] = (((long long)g[i] * (g[prime[j]] - 1)) % mod + g[d[i]]) % mod;
				d[temp] = d[i];
				break;
			}
		}
	}
}
int n, q, a, b, c, ans1, ans2;
int main() {
//	freopen("Fibonacci.in", "r", stdin);
//	freopen("Fibonacci.out", "w", stdout);
	R(n);
	R(q), R(a), R(b), R(c);
	maxp = max(q, c) + 1;
	xianshai();
//	cout<<sizeof(vis1)+sizeof(vis2)<<'\n';
//	for (int i = 1000000; i <= 1000100; ++i ) {
//		printf("f[%d] = %d, g[%d] = %d\n",i, f[i], i, g[i]);
//	}
	int t, zong;
	b %= c, a %= c;
	ans1 = 0, ans2 = 0;
	while (n--) {
		ans1 = (ans1 + f[q]) % mod;
		ans2 = (ans2 + g[q]) % mod;
		if (q & 1)ans1 = (ans1 + 1)%mod, ans2 = (ans2 + 4)%mod;
		q = ((long long)q * a + b) % c + 1;
	}
	printf("%d\n%d", ans1, ans2);
	return 0;
}
