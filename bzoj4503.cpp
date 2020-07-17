
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cctype>
using namespace std;
const double pi = acos(-1.0);
inline void R(int &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
		ch = getchar();
		if (ch == '-') p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = (v << 3) + (v << 1) + (ch^'0');
		ch = getchar();
	}
	if (p) {
		v = -v;
	}
}
struct COMPLEX {
	double r, i;
	COMPLEX(double r, double i): r(r), i(i) {}
	COMPLEX() {}
};
typedef COMPLEX E;
inline E operator + (const E &a, const E &b) {
	return E(a.r + b.r, a.i + b.i);
}
inline E operator - (const E &a, const E &b) {
	return E(a.r - b.r, a.i - b.i);
}
inline E operator * (const E &a, const E &b) {
	return E(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
}
int rev[400005], n1, n2, m, L, n;
int a[400005], b[400005];
E a1[400005], b1[400005], b2[400005], c[400005];
inline void fft(E *a, int f) {
	for (int i = 0; i < n; ++i) {
		if (i < rev[i])swap(a[i], a[rev[i]]);
	}
	E x,y;
	for (int i = 1; i < n; i = i << 1) {
		E wn(cos(pi / i), f * sin(pi / i));
		for (int j = 0; j < n; j += i << 1 ) {
			E w(1, 0);
			for (int k = 0; k < i; k++, w = w * wn) {
				x = a[j + k], y = w * a[j + k + i];
				a[j + k] = x + y;
				a[j + k + i] = x - y;
			}
		}
	}
}
char s1[100005], s2[100005];
int ans[100005];
int main() {
	//freopen("in.in", "r", stdin);
	//ios::sync_with_stdio(0);
	//cin.tie(0);
	cin >> (s1) >> (s2);
	int x;
	n1 = strlen(s1) - 1, n2 = strlen(s2) - 1;
	for (int i = 0; i <= n1; ++i) {
		a[i] = s1[i] - 96;
		//a1[i].r=a[i].r*a[i].r;
		//a[i].r*=2;
	}
	for (int i = 0; i <= n2; ++i) {
		b[i] = s2[n2 - i] == '?' ? 0 : s2[n2 - i] - 96;
		//b1[i].r=b[i].r * b[i].r;
		//b2[i].r=b[i].r *b1[i].r;
	}
//	for(int i=1;i<=n2;++i)
	//	cout<<b2[i].r<<' ';
	m = n1 + n2;
	for (n = 1; n <= m; n <<= 1)L++;
	for (int i = 0; i < n; i++)rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
	for (int i = 0; i <= n; i++) a1[i] = E(a[i] * a[i], 0), b1[i] = E(b[i], 0);
	fft(a1, 1), fft(b1, 1);
	for (int i = 0; i <= n; i++)c[i] = a1[i] * b1[i];
	for (int i = 0; i <= n; i++) a1[i] = E(a[i] * 2, 0), b1[i] = E(b[i] * b[i], 0);
	fft(a1, 1), fft(b1, 1);
	for (int i = 0; i <= n; i++)c[i] = c[i] - a1[i] * b1[i];
	for (int i = 0; i <= n; ++i) {
		a1[i] = E(1, 0); b1[i] = E(b[i] * b[i] * b[i], 0);
	}
	fft(b1, 1); fft(a1, 1);
	for (int i = 0; i <= n; i++)c[i] = c[i] + b1[i] * a1[i];
	fft(c, -1);
	//cout<<"n="<<n<<" m="<<m<<'\n';
	int cnt = 0;
	//cout<<"n1="<<n1<<" n2="<<n2<<'\n';
	//for (int i=n2; i<=n1; i++) cout<<"i="<<i<<" c[i].r="<<c[i].r<<'\n';
	for (int i = n2; i <= n1; i++) if (c[i].r < 0.5) ans[++cnt] = i - n2;
	cout << cnt << '\n';
	for (int i = 1; i <= cnt; ++i) {
		cout << ans[i] << '\n';
	}
	return 0;
}
