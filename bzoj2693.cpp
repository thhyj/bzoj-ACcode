
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
	if (p) v = -v;
}
const long long mod = 100000009;
const long long N = 10000005;
long long miu[N + 50],  prime[N + 50];
long long g[N + 50], qz[N + 50];
bool heshu[N + 50];
long long cnt;
inline void init() {
	miu[1] = 1;
	g[1] =	1;
	for (long long i = 2 ; i <= N; ++i) {
		if (!heshu[i]) prime[++cnt] = i, miu[i] = -1, g[i] = ((long long)i -  (long long)i * i) % mod;
		for (long long j = 1; j <= cnt && prime[j] * i <= N; ++j) {
			heshu[prime[j] * i] = 1;
			if (i % prime[j] == 0) {
				miu[i * prime[j]] = 0;
				g[i * prime[j]] = ((long long)g[i] * prime[j]) % mod;
				break;
			} else {
				miu[i * prime[j]] = -miu[i];
				g[i * prime[j]] = ((long long)g[i] * g[prime[j]]) % mod;
			}
		}
	}
	for (long long i = 1; i <= N; ++i) {
		qz[i] = qz[i - 1] + g[i];
	}
}
long long t;
inline long long sum(long long x, long long y) {
	return ((x * (x + 1) / 2) % mod) * ((y * (y + 1) / 2) % mod) % mod;
}
int main () {
	init();
	R(t);
	while (t--) {
		long long n , m;
		R(n), R(m);
		if (n > m) swap(n, m);
		long long j;
		long long ans = 0;
		for (long long i = 1; i <= n; i = j + 1) {
			j = min(n / (n / i), m / (m / i));
			ans = (ans + sum(n / i, m / i) * (qz[j] - qz[i - 1])) % mod;
		}
		cout <<	((ans) % mod + mod) % mod << '\n';
	}

}
