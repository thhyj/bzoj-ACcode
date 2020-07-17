
#include <bits/stdc++.h>
using namespace std;
inline void R (int &v) {
	static char ch ;
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
} a[300005], b[300005];
int rev[300005];
inline E operator + (const E &a, const E &b) {
	return E (a.r + b.r, a.i + b.i);
}
inline E operator - (const E &a, const E &b) {
	return E (a.r - b.r, a.i - b.i);
}
inline E operator * (const E &a, const E &b) {
	return E(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
}
const double pi = acos(-1);
int n, m;
int c[300005];
inline void fft(E *a, int f) {
	for (int i = 0; i < n; ++i) {
		if (i < rev[i]) swap(a[rev[i]], a[i]);
	}
	E x, y, wn, w;
	for (int i = 1; i < n; i <<= 1) {
		wn = E(cos(pi / i), sin(pi / i) * f);
		for (int j = 0; j < n; j += i << 1) {
			w = E(1, 0);
			for (int k = 0; k < i; ++k, w = w * wn) {
				x = a[j + k], y = a[j + k + i] * w;
				a[j + k] = x + y;
				a[j + k + i] = x - y;
			}
		}
	}
}
int main () {
//	freopen("in.in","r",stdin);
	R(n);
	--n;
	int x;
	char ch;
	for (int i = 0; i <= n; ++i) {
		do {
			ch = getchar();
		} while (!isdigit(ch)); a[i].r = ch^'0';
	}
	for (int i = 0; i <= n; ++i) {
		do {
			ch = getchar();
		} while (!isdigit(ch)); b[i].r = ch^'0';
	}
	m = n + n;
	int len = 0;
	for (n = 1; n <= m; n <<= 1) ++len;
	for (int i = 0; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
	fft(a, 1), fft(b, 1);
	for (int i = 0; i < n; ++i) {
		a[i] = a[i] * b[i];
	}
	fft(a, -1);
	for (int i = 0; i <= m; ++i) {
		c[m - i] = (int)(a[i].r / n + 0.5);
	}
	for(int i=0;i<=m;i++)
		if(c[i]>=10)
		{
			c[i+1]+=c[i]/10,c[i]%=10;
			if(i==m)m++;
		}
	for(int i=m;i>=0;i--)printf("%d",c[i]);
}
