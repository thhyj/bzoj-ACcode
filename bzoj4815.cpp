
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
int siz;
long long f[4000005], qz[4000005], block1[4000005],  g[4000005];
long long phi[4000005];
long long prime[4000005];
bool pr[4000005];
int tot, bl[4000005];
const int mod = 1000000007;
inline void xianshai(int n) {
	phi[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!pr[i]) {
			prime[++prime[0]] = i;
			phi[i] = i - 1;
		}
		for (int j = 1; j <= prime[0] && prime[j]*i <= n; ++j) {
			pr[prime[j]*i] = 1;
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			} else {
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			}
		}
	}
	for (int i = 1; i <= n; i++) g[i] = (g[i - 1] + (long long) i * i % mod * phi[i] % mod) % mod;
}
inline int gcd (int x, int y) {
	if (x < y) swap(x, y);
	int t;
	while (y) {
		t = x;
		x = y;
		y = t % y;
	}
	return x;
}
struct kuai {
	int l, r;
} b1[1000005];
inline long long ksm(long long x, long long k) {
	long long ret = 1;
	while (k) {
		if (k & 1) ret = ret * x % mod;
		x = x * x % mod; k >>= 1;
	}
	return ret;
}
int query(int x) {
	//printf("bl[%d]=%d\n", x, x, bl[x]);
	return (qz[x] + block1[bl[x]]) % mod;
}
int main () {
//	freopen("table.in", "r", stdin);
//	freopen("table.out", "w", stdout);
	int n, m;
	R(m), R(n);
	xianshai(n);
	siz = sqrt(n);
	//cout << "siz=" << siz << '\n';
	int a, b, k;
	long long x;
	//for (int i = 1; i <= n; ++i) {
	//	g[i] = (g[i - 1] + (long long)i * (long long)i % mod * (long long)phi[i]) % mod;
	//}
	int tmp;
	tot = (n - 1) / siz + 1;
	for (int i = 1; i <= n; ++i) {
		f[i] = (long long)i * i % mod;
		tmp = ((i - 1) / siz) + 1;
		qz[i] = (qz[i - 1] + f[i]) % mod;
		bl[i] = tmp;
	}
	//for (int i = 1; i <= n; ++i) printf("bl[%d]=%d,qz[%d]=%d\n", i, bl[i], i, qz[i]);
	for (int i = 1; i <= tot; ++i) {
		b1[i].l = (i - 1) * siz + 1;
		b1[i].r = i * siz;
	}
	int d;
	int t;
	int r;
	int cg;
	for (int i = 1; i <= m; ++i) {
		R(a), R(b), R(x), R(k);
		d = gcd(a, b);
		t = f[d];
		a = ksm(((long long)a * b % mod), mod - 2)%mod;
	//	cout<<"a="<<a<<'\n';
		x %= mod;
		f[d] = ((long long) d * d % mod * x % mod * a % mod + mod) % mod;
	//	cout << "v=" << f[d] << '\n';

		r = b1[bl[d]].r;
		cg = (f[d] - t + mod) % mod;
		if (!cg) {
			long long ans = 0;
			int pre = 0;
			for (int i = 1; i <= k; i = r + 1, pre = tmp) {
				r = k / (k / i); //cout << "k=" << k << " r=" << r << '\n';
				tmp = query(r);
				//	cout << "tmp=" << tmp << '\n';
				ans = (ans + (long long) (tmp - pre + mod) * g[k / i] % mod) % mod;
			}
			printf("%d\n", (ans + mod) % mod);
			continue;
		}
		for (int i = d; i <= r; i++) qz[i] = (qz[i] + cg) % mod;
		for (int i = bl[d] + 1; i <= tot; i++) block1[i] = (block1[i] + cg) % mod;
		//	for (int i = 1; i <= tot; ++i) {
		//		printf("block1[%d]=%d\n", i, block1[i] );
		//}
		long long ans = 0;
		int pre = 0;
		tmp = 0;
		for (int i = 1; i <= k; i = r + 1, pre = tmp) {
			r = k / (k / i);
			//cout << "k=" << k << " r=" << r << '\n';
			tmp = query(r);
			//cout << "tmp=" << tmp << '\n';
			ans = (ans + (long long) (tmp - pre + mod) * g[k / i] % mod) % mod;
		}
		printf("%d\n", (ans + mod) % mod);
	}
	return 0;
}
