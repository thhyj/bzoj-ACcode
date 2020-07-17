
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
const int p = 10007;
int pow1[10050];
inline int ksm(int x, int y) {
	int ret = 1;
	while (y) {
		if (y & 1) ret = ret * x % p;
		x = x * x % p; y >>= 1;
	}
	return ret;
}
inline int calc(int n, int m) {
	return n >= m ? (((pow1[n] * ksm(pow1[n - m], p - 2) % p) * ksm(pow1[m], p - 2)) % p) : 0;
}
inline int Lucas(int n, int m) {
	if (n < m) return 0;
	if (n < p && m < p) {
		return calc(n, m);
	} else 	return (calc(n % p, m % p) * Lucas(n / p, m / p)) % p;
}
int n, m, T;
int main () {
	//freopen("in.in","r",stdin);
	pow1[0] = 1;
	for (int i = 1; i < 10050; ++i) {
		pow1[i] = (pow1[i - 1] * i) % p;
	}
	R(T);
	while (T--) {
		R(n), R(m);
		printf("%d\n", Lucas(n, m));
	}
}
