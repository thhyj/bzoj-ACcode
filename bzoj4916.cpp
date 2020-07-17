
#include <bits/stdc++.h>
#include <tr1/unordered_map>
using namespace std;
tr1::unordered_map<int , long long> s;
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
const int N = 1000005;
int sum[N + 50];
int phi[N + 50];
int prime[N + 50];
bool heshu[N + 50];
int cnt;
long long inv6, inv2;
const int mod = 1000000007;
inline long long ksm(long long x, int y) {
	long long ret = 1;
	while (y) {
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod, y >>= 1;
	}
	return ret;
}

inline void init() {
	phi[1] = 1;
	for (int i = 2; i <= N; ++i) {
		if (!heshu[i]) prime[++cnt] = i, phi[i] = i - 1;
		for (int j = 1; j <= cnt && prime[j] * i <= N; ++j) {
			heshu[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
			} else {
				phi[i * prime[j]] = phi[i] * phi[prime[j]];
			}
		}
	}
	for (int i = 1; i <= N; ++i) {
		sum[i] = ((long long)sum[i - 1] + (long long)phi[i] * (long long)i) % mod;
	}
}
int n;
inline int gets(int x) {
	if (x <= N) {
		return sum[x];
	} else {
		if (s.find(x) != s.end()) return s[x];
		int j, ret = (((long long) x * (long long) (x + 1) % (mod)) * (long long) (x + x + 1)) % mod * inv6 % mod;
		for (int i = 2; i <= x; i = j + 1) {
			j = (x / (x / i));
			ret = ((long long)ret - ((long long)(i + j) * (long long)(j - i + 1) % mod * inv2) % mod * (long long)gets(x / i) % mod ) % mod;
		}
		return s[x] = ret;
	}
}
int main() {
	init();
	inv6 = ksm(6, mod - 2);
	inv2 = ksm(2, mod - 2);
	R(n);
	puts("1");
	cout << (gets(n) + mod) % mod;
}
