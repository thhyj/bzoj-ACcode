
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
int n, m, k;
double a[1005];
struct matrix {
	double a[1005];
} ma;
inline matrix  operator * (const matrix &a , const matrix &b) {
	matrix temp;
	memset(temp.a, 0, sizeof(temp.a));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			temp.a[i] += b.a[(i - j + n) % n] * a.a[j];
		}
	}
	return temp;
}
inline matrix ksm(matrix x, int y) {
	matrix ret;
	memset(ret.a, 0 , sizeof(ret.a));
	ret.a[0] = 1;
	while (y) {
		if (y & 1) ret = ret * x;
		x = x * x; y >>= 1;
	}
	return ret;
}
double ans[1005];
int main () {
	R(n), R(m), R(k);
	int x;
	for (int i = 1; i <= n; ++i) {
		R(x);
		a[i] = x;
	}
	ma.a[0] = 1.0 - 1.0 / (double)m;
	ma.a[1] = 1.0 / (double)m;
	ma = ksm(ma, k);
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < n; ++j) {
			ans[i] += a[j + 1] * ma.a[(i - j - 1 + n) % n];
		}
	}
	for (int i = 1; i <= n; ++i) {
		printf("%0.3f\n", ans[i]);
	}
	return 0;
}
