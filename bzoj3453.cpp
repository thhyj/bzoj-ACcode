
#include <bits/stdc++.h>
#define ll long long
inline void R (ll &v) {
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
using namespace std;
const ll mod = 1234567891;
inline ll ksm (ll x, ll y) {
	ll ret = 1;
	while (y) {
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}
ll T, k, a, n, d;
ll g[205];
ll h[205];
ll ans[205];
ll f[205];
/*inline ll getg(ll x) {
	x %= mod;
	ll ret = 0;
	long long len = k + 3;
	for (long long i = 1; i <= len; ++i) {
		ll temp = g[i];
		for (long long j = 1; j <= len; ++j) {
			if (i == j) continue;
			temp = (temp * (x - j)) % mod;
			temp = (temp * ksm(i - j, mod - 2ll)) % mod;
		}
		ret = (ret + temp) % mod;
	}
	return (ret + mod) % mod;
}*/
inline ll getg(ll x) {
	x %= mod;
	ll ret = 0;
	ll len = k + 3, fenzi = 1 , fenmu = 1;

	for (ll j = 1; j <= len; ++j) {
		if(x != j)
		fenzi =  fenzi * (x - j) % mod;
		if (j != 1) fenmu = fenmu * (1 - j) % mod;
	}
	ll temp;
	if(x >= 1 && x <= len) {
		for (long long i = 1; i <= len; ++i) {
			if(i == x){
		//		printf("fenzi =  %I64d, fenmu = %I64d\n", fenzi * ksm(x - i, mod - 2) % mod, fenmu);
				temp = g[i];
				temp = (temp * fenzi % mod);
				temp = temp * ksm(fenmu, mod - 2) % mod;
				ret = (ret + temp) % mod;
			}
			fenmu = ((fenmu * ksm(i - len, mod - 2)) % mod) * i % mod;
		}
	} else {
		for (long long i = 1; i <= len; ++i) {
		//	printf("fenzi =  %I64d, fenmu = %I64d\n", fenzi * ksm(x - i, mod - 2) % mod, fenmu);
			temp = g[i];
			temp = (temp * fenzi % mod) * ksm(x - i, mod - 2) % mod;
			temp = temp * ksm(fenmu, mod - 2) % mod;
			ret = (ret + temp) % mod;
			fenmu = ((fenmu * ksm(i - len, mod - 2)) % mod) * i % mod;
		}
	}
	return (ret + mod) % mod;
}
inline ll geth(ll x) {
	x %= mod;
	ll ret = 0;
	ll len = k + 3, fenzi = 1 , fenmu = 1;

	for (ll j = 1; j <= len; ++j) {
		if(x != j)
		fenzi =  fenzi * (x - j) % mod;
		if (j != 1) fenmu = fenmu * (1 - j) % mod;
	}
	ll temp;
	if(x >= 1 && x <= len) {
		for (long long i = 1; i <= len; ++i) {
			if(i == x){
		//		printf("fenzi =  %I64d, fenmu = %I64d\n", fenzi * ksm(x - i, mod - 2) % mod, fenmu);
				temp = h[i];
				temp = (temp * fenzi % mod);
				temp = temp * ksm(fenmu, mod - 2) % mod;
				ret = (ret + temp) % mod;
			}
			fenmu = ((fenmu * ksm(i - len, mod - 2)) % mod) * i % mod;
		}
	} else {
		for (long long i = 1; i <= len; ++i) {
		//	printf("fenzi =  %I64d, fenmu = %I64d\n", fenzi * ksm(x - i, mod - 2) % mod, fenmu);
			temp = h[i];
			temp = (temp * fenzi % mod) * ksm(x - i, mod - 2) % mod;
			temp = temp * ksm(fenmu, mod - 2) % mod;
			ret = (ret + temp) % mod;
			fenmu = ((fenmu * ksm(i - len, mod - 2)) % mod) * i % mod;
		}
	}
	return (ret + mod) % mod;
}
inline ll getans(ll x) {
	x %= mod;
	ll ret = 0;
	ll len = k + 4, fenzi = 1 , fenmu = 1;

	for (ll j = 1; j <= len; ++j) {
		if(x != j)
		fenzi =  fenzi * (x - j) % mod;
		if (j != 1) fenmu = fenmu * (1 - j) % mod;
	}
	ll temp;
	if(x >= 1 && x <= len) {
		for (long long i = 1; i <= len; ++i) {
			if(i == x){
		//		printf("fenzi =  %I64d, fenmu = %I64d\n", fenzi * ksm(x - i, mod - 2) % mod, fenmu);
				temp = ans[i];
				temp = (temp * fenzi % mod);
				temp = temp * ksm(fenmu, mod - 2) % mod;
				ret = (ret + temp) % mod;
			}
			fenmu = ((fenmu * ksm(i - len, mod - 2)) % mod) * i % mod;
		}
	} else {
		for (long long i = 1; i <= len; ++i) {
		//	printf("fenzi =  %I64d, fenmu = %I64d\n", fenzi * ksm(x - i, mod - 2) % mod, fenmu);
			temp = ans[i];
			temp = (temp * fenzi % mod) * ksm(x - i, mod - 2) % mod;
			temp = temp * ksm(fenmu, mod - 2) % mod;
			ret = (ret + temp) % mod;
			fenmu = ((fenmu * ksm(i - len, mod - 2)) % mod) * i % mod;
		}
	}
	return (ret + mod) % mod;
}
int main() {
//	freopen("in.in","r",stdin);
	R(T);
	while (T--) {
		R(k), R(a), R(n), R(d);
		g[0] = 0;
		for (long long i = 1; i <= k + 3; ++i) {
			f[i] = (f[i - 1] + ksm(i, k)) % mod;
		}
//		printf("f[123] = %I64d\n", f[123]);
		for (long long i = 1; i <= k + 3; ++i) {
			g[i] = (g[i - 1] + f[i]) % mod;
		}
//		printf("g[4] = %I64d\n", g[4]);
//		printf("getg(4) = %I64d\n", getg(4));
		for (long long i = 1; i <= k + 3; ++i) {
			h[i] = getg(a + i * d);
//					printf("a + %I64d *d = %I64d\n", i, a+i*d);
		}
//		for (int i = 1; i < k + 4; ++i) {
///			printf("h[%d] = %I64d\n", i, h[i]);
	//	}
//		printf("geth(0) = %I64d\n", geth(0));
		ans[0] = geth(0);
		for (long long i = 1; i <= k + 4; ++i) {
			ans[i] = (ans[i - 1] + geth(i)) % mod;
		}
//		printf("ans[1] = %I64d\n", ans[1]);
//		printf("getans(1) = %I64d\n", getans(1));
		cout << getans(n) << '\n';
	}
}
