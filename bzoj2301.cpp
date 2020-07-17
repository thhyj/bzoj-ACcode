
#include <bits/stdc++.h>
using namespace std;
inline char read() {
	static const int IN_LEN = 1000000;
	static char buf[IN_LEN], *s, *t;
	s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin) : 0;
	return s == t ? -1 : *s++;
}

template <typename T>
inline void read(T &x) {
	static char c;
	static bool iosig;
	for (c = read(), iosig = false; !isdigit(c); c = read()) {
		if (c == -1) return;
		c == '-' ? iosig = true : 0;
	}
	for (x = 0; isdigit(c); c = read()) x = x * 10 + (c ^ '0');
	iosig ? x = -x : 0;
}

inline void read(char &c) {
	while (c = read(), isspace(c) && c != -1)
		;
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

int miu[50005], isheshu[50005], zhishu[50005], cnt;
int qz[50005];
inline void init() {
	miu[1] = 1;
	for (register int i = 2; i <= 50000; ++i) {
		if (!isheshu[i]) zhishu[++cnt] = i, miu[i] = -1;
		for (register int j = 1; j <= cnt && zhishu[j] * i <= 50000; ++j) {
			isheshu[i * zhishu[j]] = 1;
			if (i % zhishu[j] == 0) {
				miu[i * zhishu[j]] = 0;
				break;
			} else {
				miu[i * zhishu[j]] = -miu[i];
			}
		}
	}
}
int n;
inline int solve(int a, int b) {
	int ans = 0;
	if (a > b) swap(a, b);
	for (register int i = 1, j; i <= a; i = j + 1) {
		j = min(a / (a / i), b / (b / i));
		ans = ans + (a / i) * (b / i) * (qz[j] - qz[i - 1]);
	}
	return ans;
}
int main () {
//	freopen("in.in","r",stdin);
	init();
	//for (register int i = 1; i <= 50; ++i) {
	//	printf("%d\n", miu[i]);
	//}
	read(n);
	int a, b, c, d, k;
	for (register int i = 1; i <= 50000; ++i) {
		qz[i] = qz[i - 1] + miu[i];
	}
	int ans = 0;
	while (n--) {
		read(a), read(b), read(c), read(d), read(k);
		a--, c--;
		a /= k, b /= k, c /= k, d /= k;
		ans = 0;
		ans += solve(b, d) - solve(a , d) - solve(b, c) + solve(a, c);
		printf("%d\n", ans);
	}
}
