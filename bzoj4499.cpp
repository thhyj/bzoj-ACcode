
#include <bits/stdc++.h>
using namespace std;
inline char read() {
	static const int IN_LEN = 1000000;
	static char buf[IN_LEN], *s, *t;
	s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin) : 0;
	return s == t ? -1 : *s++;
}

template <typename T>
inline bool R(T &x) {
	static char c;
	static bool iosig;
	for (c = read(), iosig = false; !isdigit(c); c = read()) {
		if (c == -1) return false;
		c == '-' ? iosig = true : 0;
	}
	for (x = 0; isdigit(c); c = read()) x = x * 10 + (c ^ '0');
	iosig ? x = -x : 0;
	return true;
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

inline void print(const char *s) {
	for (; *s; s++) print(*s);
}

inline void flush() {
	fwrite(obuf, 1, oh - obuf, stdout);
}
struct tree {
	int k, b;
} tr[800005];
const int mod = 1000000007;
inline void updata(int x) {
	tr[x].k = (long long)tr[x << 1].k * (tr[x << 1 | 1].k) % mod;
	tr[x].b = ((long long)tr[x << 1 | 1].k * tr[x << 1].b + tr[x << 1 | 1].b) % mod;
}
int k[200005], b[200005];
inline void build(int x, int l, int r) {
	if (l == r) {
		tr[x].k = k[l];
		tr[x].b = b[l];
		return;
	}
	int mid = l + r >> 1;
	build(x << 1, l, mid);
	build(x << 1 | 1, mid + 1, r);
	updata(x);
}
inline void modify(int x, int l, int r, int pos, int k,int b) {
	if (l == r) {
		tr[x].k = k;
		tr[x].b = b;
		return;
	}
	int mid = r + l >> 1;
	if (pos <= mid) modify(x << 1, l, mid, pos, k, b);
	else modify(x << 1 | 1, mid + 1, r, pos, k, b);
	updata(x);
}
inline pair<int , int> merge(pair<int, int> a, pair<int, int >b) {
	return make_pair((long long)a.first * b.first % mod, ((long long)a.first * b.second + a.second) % mod);
}
inline pair<int , int> query(int x, int l, int r, int ql, int qr) {
	if (l >= ql && r <= qr) {
		return make_pair(tr[x].k, tr[x].b);
	}
	int mid = l + r >> 1;
	pair<int , int> ret;
	if (ql <= mid) {
		ret = query(x << 1, l, mid, ql, qr);
		if (qr > mid) ret = merge(query(x << 1 | 1, mid + 1, r, ql, qr), ret);
	}
	else if (qr > mid) ret = query(x << 1 | 1, mid + 1, r, ql, qr);
	return ret;
}
int n, m;
int main() {
//	freopen("in.in","r",stdin);
	R(n), R(m);
	for (int i = 1; i <= n; ++i) {
		R(k[i]), R(b[i]);
	}
	build(1, 1, n);
	char ch;
	int x, k1, b1, l, r;
	int ans;
	for (int i = 1; i <= m; ++i) {
		do {
			read(ch);
		} while (!isupper(ch));
		switch (ch) {
		case 'M':
			R(x), R(k1), R(b1);
			modify(1, 1, n, x, k1, b1);
			break;
		case 'Q':
			R(l), R(r), R(x);
			pair<int, int> temp = query(1, 1, n, l, r);
		//	printf("temp.first = %d, temp.second = %d\n", temp.first, temp.second);
			ans = ((long long)temp.first * x + temp.second) % mod;
			print(ans);
			print('\n');
		}
	}
	flush();
	return 0;
}
