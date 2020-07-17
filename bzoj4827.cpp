
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
#define  x1 aygjklasdg
#define y1 fahjlkg
const double pi =  acos(-1);
struct E {
	double r, i;
	E(double r, double i): r(r), i(i) {}
	E() {}
} a[400005], b[400005], c[400005];
inline E operator + (const E &a, const E &b) {
	return E(a.r + b.r, a.i + b.i);
}
inline E operator -(const E &a, const E &b) {
	return E(a.r - b.r, a.i - b.i);
}

inline E operator *(const E &a, const E &b) {
	return E(a.r * b.r - a.i * b.i, a.r * b.i + b.r * a.i);
}
int rev[400005];
int x1[200005], y1[200005];
int n, m, C, c1, c2;
inline void fft(E *a, int f) {
	for (int i = 0; i < n; ++i) {
		if (i < rev[i]) swap(a[i], a[rev[i]]);
	}
	E x, y;
	for (int i = 1; i < n; i <<= 1) {
		E w1(cos(pi / i), f * sin(pi / i));
		for (int j = 0; j < n; j += i << 1) {
			E w = E(1, 0);
			for (int k = 0; k < i; ++k , w = w * w1) {
				x = a[k + j], y = a[i + j + k] * w;
				a[k + j] = x + y;
				a[i + j + k] = x - y;
			}
		}
	}
}
int main () {
//	freopen("gift.in","r",stdin); 
	R(n), R(m);
	for (int i = 0; i < n; i++) {
		R(x1[i]);
		C += x1[i] * x1[i];
		c1 += 2 * x1[i];
		c2 -= 2 * x1[i];
	}
	for (int i = 0; i < n; i++) {
		R(y1[i]);
		C += y1[i] * y1[i];
		c1 -= 2 * y1[i];
		c2 += 2 * y1[i];
	}
	for (int i = 0; i < n; ++i) {
		a[i].r = x1[i];
	}
	for (int i = 0; i < n; ++i) {
		b[i].r = y1[i];
		b[i+n].r = y1[i];
	}
/*	for(int i=0;i<n;i++){
		a[i].r=a[n+i].r=x1[i];
		b[i].r=y1[n-i-1];
	}
	int n1 = n;
	int L = 0;
	for(n=1;n<n1<<2;n<<=1){
		L++;
	}
	for(int i=0;i<n;i++){
		rev[i]=rev[i>>1]>>1|((i&1)<<(L-1));
	}*/
	int n1 = n, m1 = m;
	reverse(b, b + n + n);
	m = n + n + n;
	n = 1;
	int L = 0;
	for (; n <= m; n <<= 1)++L;
	for (int i = 0; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
	fft(a, 1),  fft(b, 1);
	for (int i = 0; i < n; ++i) {
		c[i] = a[i] * b[i];
	}
	fft(c, -1);
	int ans = INT_MAX;
	long long daan = INT_MAX;
	for (int i = n1 - 1; i < n1 + n1 - 1; ++ i) {
		for (int j = 0; j <= m1; j++) {
	//		printf(" c[%d].r = %d\n", i, int(c[i].r + .5));
			ans = min(ans, C + c1 * j + n1 * j * j - 2 * int((c[i].r/ n + .5) ));
			ans = min(ans, C + c2 * j + n1 * j * j - 2 * int((c[i].r/ n + .5) ));
		}
	}
	cout << ans;
	return 0;
}
