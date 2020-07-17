
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
int n, m;
inline void R (double &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
		ch = getchar();
		if (ch == '-') p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = (v + v * 10) + (ch^'0');
		ch = getchar();
	}
	if (p) v = -v;
}
struct E {
	double r, i;
	E(double r, double i) : r(r), i(i) {}
	E() {}
} a[500005], b[500005];
int rev[500005];
inline E operator +(const E &a, const E &b) {
	return E(a.r + b.r, a.i + b.i);
}
inline E operator -(const E &a, const E &b) {
	return E(a.r - b.r, a.i - b.i);
}
inline E operator *(const E &a, const E &b) {
	return E(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
}
const double pi = acos(-1);
inline void fft (E *a, int f) {
	for (int i = 0; i < n; ++i) {
		if (rev[i]  > i) swap(a[rev[i]], a[i]);
	}
	E x, y, wn, w;
	for (int i = 1; i < n; i <<= 1) {
		wn = E(cos(pi / i), f * sin(pi / i));
		for (int j = 0; j < n; j += i << 1) {
			w = E(1, 0);
			for (int k = 0; k < i; ++k, w = w * wn) {
				x = a[k + j], y = w * a[k + j + i];
				a[j + k] = x + y;
				a[j + k + i] = x - y;
			}
		}
	}
}
int main () {
	R(n);
	int x;
	for (int i = 0; i < n ; ++i) {
		R(x); a[i].r = x, R(x), b[i].r = x;
	}
	reverse(a, a + n);
	int temp = n;
	m = n + n;
	int len = 0;
	for (n = 1; n <= m; n <<= 1) ++len;
	for (int i = 0; i < n; ++i) rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (len - 1)));
	fft(a, 1), fft(b, 1);
	for (int i = 0; i < n; ++i) {
		a[i] = a[i] * b[i];
	}
	fft(a, -1);
//	reverse(a, a + n + 1);
	for (int i = temp - 1; i >= 0; --i) {
		printf("%d\n", (int)(a[i].r / n + 0.5));
	}
	return 0;
}
