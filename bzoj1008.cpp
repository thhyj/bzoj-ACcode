
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
const int p = 100003;
inline long long ksm(long long x, long long y) {
	long long ret = 1;
	while (y) {
		if (y & 1) ret = ret * x % p;
		x = x * x % p;
		y >>= 1;
	}
	return ret;
}
long long n, m;
long long ans;
int main() {
	R(m), R(n);
	ans = ksm(m, n);
	long long temp = m;
	temp = (temp * ksm(m - 1, n - 1)) % p;
	ans = ((ans - temp) % p + p) % p;
	cout << ans << '\n';
	return 0;
}
