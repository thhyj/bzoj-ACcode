
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
long long  y, z, p;
inline long long ksm(long long x, long long y) {
	long long ret = 1;
	while (y) {
		if (y & 1) ret = ret * x % p;
		x = x * x % p;
		y >>= 1;
	}
	return ret;
}
#define x1 agnjilks
#define y1 sajglkgdkj
long long x1, y1, t, T;
inline void exgcd(long long a, long long b) {
	if (a < b) swap(a, b);
	if (!b) {
		x1 = 1, y1 = 0;
	} else {
		exgcd(b, a % b);
		t = x1;
		x1 = y1, y1 = t - a / b * y1;
	}
}
map<long long, long long>ma;
int main() {
	R(T);
	long long kind ;
	R(kind);
	if (kind == 1) {
		while (T--) {
			R(y), R(z), R(p);
			printf("%lld\n", ksm(y, z));
		}
	}
	if (kind == 2) {
		while (T--) {
			R(y), R(z), R(p);
			long long gcd1 = __gcd(y, p);
			if (z % gcd1) {
				puts("Orz, I cannot find x!");
				continue;
			}
			exgcd(y, p);
			x1 *= z / gcd1;
			y1 *= z / gcd1;
			if (y * x1 + p * y1 == z) {
				printf("%lld\n", ((x1 % p + p) % p));
			} else
				printf("%lld\n", ((y1 % p + p) % p));
		}
	}
	if (kind == 3) {
		while (T--) {
			R(y), R(z), R(p);
			y %= p;
			z %= p;
			ma.clear();
			if (!y && !z) {
				puts("1");
				continue;
			}
			if (!y) {
				puts("Orz, I cannot find x!");
				continue;
			}
			long long sp = ceil(sqrt(p)), now = z;
			for (long long i = 1; i < sp; ++i) {
				if (!ma[now]) ma[now] = i;
				now = now * y % p;
			}
			long long cheng = ksm(y, sp);
			now = cheng;
			long long ans = 0;
			for (long long i = 1; i <= sp + 1; ++i) {
				if (ma[now]) {ans = i * sp - ma[now] + 1; break;}
				now = now * cheng % p;
			}
			if (ans)
				printf("%lld\n", ans);
			else {
				puts("Orz, I cannot find x!");
			}
		}
	}
	return 0;
}
