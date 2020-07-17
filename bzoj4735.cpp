
#include <bits/stdc++.h>
using namespace std;
inline void R (int &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
		ch = getchar();
		if (ch == '-') ch = getchar();
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = (v + (v << 2) << 1) + (ch ^ '0');
		ch = getchar();
	}
	if (p) v = -v;
}
int n;
int x, m;
int now;
const int mod = 998244353;
inline int ksm(int x, int y) {
	int ret = 1;
	while (y) {
		if (y & 1) ret = (long long) ret * x % mod;
		x = (long long) x * x % mod; y >>= 1;
	}
	return ret;
}
int main() {
	R(n);
	for (int i = 1; i <= n; ++i) {
		R(x);
		m += x;
	}
	int now = 1, now1 = 1, now2 = 1, now3 = 1, now4 = 1, now5 = 1, now6 = 1,
	    now7 = 1, now8 = 1, now9 = 1, now10 = 1, now11 = 1, now12 = 1, now13 = 1,
	    now14 = 1, now15 = 1;
	int temp = m - 15, i;
	for (i = 1; i <= temp; i += 16) {
		now = (long long)now * i % mod;
		now1 = (long long)now1 * (i + 1) % mod;
		now2 = (long long)now2 * (i + 2) % mod;
		now3 = (long long)now3 * (i + 3) % mod;
		now4 = (long long)now4 * (i + 4) % mod;
		now5 = (long long)now5 * (i + 5) % mod;
		now6 = (long long)now6 * (i + 6) % mod;
		now7 = (long long)now7 * (i + 7) % mod;
		now8 = (long long)now8 * (i + 8) % mod;
		now9 = (long long)now9 * (i + 9) % mod;
		now10 = (long long)now10 * (i + 10) % mod;
		now11 = (long long)now11 * (i + 11) % mod;
		now12 = (long long)now12 * (i + 12) % mod;
		now13 = (long long)now13 * (i + 13) % mod;
		now14 = (long long)now14 * (i + 14) % mod;
		now15 = (long long)now15 * (i + 15) % mod;
	}
	for (; i <= m; ++i) {
		now = (long long)now * i % mod;
	}
	cout << (long long)now * now1 % mod * now2 % mod * now3 % mod * now4 % mod * now5 % mod * now6 % mod * now7 % mod
	     * now8 % mod * now9 % mod * now10 % mod * now11 % mod * now12 % mod * now13 % mod * now14 % mod * now15 % mod *
	     ksm(m - n + 1, mod - 2) % mod;
	return 0;
}
