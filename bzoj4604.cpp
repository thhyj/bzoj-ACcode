
#include <bits/stdc++.h>
int x[100005], y[100005], w[100005], cur, n, q, l, a[100005];
using namespace std;
inline char read() {
	static const int IN_LEN = 1000000;
	static char buf[IN_LEN], *s, *t;
	s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin) : 0;
	return s == t ? -1 : *s++;
}
template <typename T>
inline void R(T &x) {
	static char c;
	static bool iosig;
	for (c = read(), iosig = false; !isdigit(c); c = read()) {
		if (c == -1) return;
		c == '-' ? iosig = true : 0;
	}
	for (x = 0; isdigit(c); c = read()) x = (x + (x << 2) << 1) + (c ^ '0');
	iosig ? x = -x : 0;
}
inline int read(char *buf) {
	register int s = 0;
	register char c;
	while (c = read(), isspace(c) && c != -1)
		;
	if (c == -1) {
		*buf = 0;
		return -1;
	}
	do
		buf[s++] = c;
	while (c = read(), !isspace(c) && c != -1);
	buf[s] = 0;
	return s;
}
const int OUT_LEN = 1000000;
char obuf[OUT_LEN], *oh = obuf;
inline void print(char c) {
	oh == obuf + OUT_LEN ? (fwrite(obuf, 1, OUT_LEN, stdout), oh = obuf) : 0;
	*oh++ = c;
}
template <typename T>
inline void print(T x) {
	static int buf[30], cnt;
	if (x == 0) {
		print('0');
	} else {
		x < 0 ? (print('-'), x = -x) : 0;
		for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 | 48;
		while (cnt) print((char)buf[cnt--]);
	}
}
inline void flush() { fwrite(obuf, 1, oh - obuf, stdout); }
int main() {
//	freopen("in.in", "r", stdin);
	R(n), R(q);
	int xl, yl , xr , yr , k;
	int kind;
	int lastans = 0;
	while (q--) {
		R(kind);
		if (kind == 1) {
			R(x[cur]), R(y[cur]), R(w[cur++]);
			//x[cur] ^= lastans, y[cur] ^= lastans, w[cur++] ^= lastans;
		}
		else {
			R(xl), R(yl), R(xr), R(yr), R(k);
			//xl ^= lastans, yl ^= lastans, xr ^= lastans, yr ^= lastans, k ^= lastans;
			for (int i = l = 0; i < cur; i++)
				if (xl <= x[i] && x[i] <= xr && yl <= y[i] && y[i] <= yr)
					a[l++] = w[i];
			if (k > l){
				print('N'), print('A'), print('I'), print('V'), print('E'),
				      print('!'), print('O'), print('R'), print('Z'), print('z'),
				      print('y'), print('z'), print('.'), print('\n'), lastans = 0;}
			else {
				nth_element(a, a + (l - k), a + l);
				print(a[l - k]);
				print('\n');
				lastans = a[l - k];
			}
		}
	}
	flush();
	return 0;
}
