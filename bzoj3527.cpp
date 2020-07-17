
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
struct E {
	double r, i;
	E(double r, double i): r(r), i(i) {}
	E() {}
} f[300005], h[300005], g[300005], a[300005], x1[300005];
int n, m;
int rev[300005];
const E operator + (const E &a, const E &b) {
	return E(a.r + b.r, a.i + b.i);
}
const E operator - (const E &a, const E &b) {
	return E(a.r - b.r, a.i - b.i);
}
const E operator *(const E &a, const E &b) {
	return E(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
}
const double pi = acos(-1);
inline void fft(E *a, int f) {
	for (int i = 0; i < n; ++i) {
		if (i < rev[i]) swap(a[rev[i]], a[i]);
	}
	E wn, w, x, y;
	for (int i = 1; i < n; i <<= 1) {
		wn = E(cos(pi / i), sin(pi / i) * f);
		for (int j = 0; j < n; j += i << 1) {
			w = E(1, 0);
			for (int k = 0; k < i; k++, w = w * wn) {
				x = a[j + k], y = a[j + k + i] * w;
				a[j + k] = x + y;
				a[j + k + i] = x - y;
			}
		}
	}
}
int main() {
	R(n);
	--n;
	for (int i = 0; i <= n; ++i) {
		scanf("%lf", &f[i].r);
	}
	for (int i = 1; i <= n; ++i) g[i].r = 1.0 / i / i;
	int temp = n;
	m = n + n;
	int len = 0;
	for (n = 1; n <= m; n <<= 1) ++len;
	for (int i = 0; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
	for (int i = 0; i <= temp; ++i) {
		h[i] = f[temp - i];
	}
	fft(f, 1), fft(g, 1);
	for (int i = 0; i <= n; ++i) {
		a[i] = f[i] * g[i];
	}
	fft(a, -1);
	memset(g, 0, sizeof(g));
	for (int i = 1; i <= temp; ++i) g[i].r = 1.0 / i / i;
	fft(h, 1), fft(g, 1);
	for (int i = 0; i < n; ++i) {
		x1[i] = h[i] * g[i];
	}
	fft(x1, -1);
	for (int i = 0; i <= temp; ++i) {
		a[i] = a[i] - x1[temp - i];
	}
	for (int i = 0; i <= temp; ++i) {
		printf("%.3lf\n", a[i].r / n);
	}
}
