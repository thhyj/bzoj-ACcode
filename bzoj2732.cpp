
#include <bits/stdc++.h>
#define eps 1e-20  
#define inf 1e15
using namespace std;
inline void R(int &v) {
	static char ch;
	bool p = 0;
	v = 0;
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
inline void R(long double &v) {
	static char ch;
	bool p = 0;
	v = 0;
	do {
		ch = getchar();
		if (ch == '-') p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = v*10 + (ch^'0');
		ch = getchar();
	}
	if (p) v = -v;
}
struct P {
	long double x, y;
	P(long double x, long double y): x(x), y(y) {}
	P() {}
} p[400005], a[400006];
int head, tail;
struct L {
	P a, b;
	long double slop;
	int id;
} l[400005], h[400005], l1[400005];
inline P operator -(const P &a, const P &b) {
	return P(a.x - b.x, a.y - b.y);
}
inline long double operator * (const P &a, const P &b) {
	return a.x * b.y - a.y * b.x;
}
inline bool operator <(const L &a, const L &b) {
	if (fabs(a.slop - b.slop)>eps)return a.slop < b.slop;
	return (a.b - a.a) * (b.b - a.a) > 0;
}
int n;
#define y1 QWQ
#define y2 QWQWQ
int cnt;
int tot;
P t, ret;
long double k1, k2;
inline P inter(L a, L b) {
	k1 = (b.b - a.a) * (a.b - a.a);
	k2 = (a.b - a.a) * (b.a - a.a);
	k1 = k1 / (k1 + k2);
	ret = P(b.b.x - (b.b.x - b.a.x) * k1, b.b.y - (b.b.y - b.a.y) * k1);
	return ret;
}
inline bool check(L a, L b, L t) {
	ret = inter(a, b);
	return (t.b - t.a) * (ret - t.a) < 0;
}
inline void hpi(const int &all) {
	tot = 0;
	for (int i = 1; i <= cnt; ++i) {
		if(l[i].id <= all){
            if(l[i].slop != l1[tot].slop) tot++;
            l1[tot] = l[i];
        }
	}
	head = 1;
	tail = 0;
	h[++tail] = l1[1], h[++tail] = l1[2];
	for (int i = 3; i <= tot; ++i) {
		while (head<tail&&check(h[tail], h[tail - 1], l1[i])) {tail--;}
		while (head<tail&&check(h[head + 1], h[head], l1[i])) {head++;}
		h[++tail] = l1[i];
	}
	while (head<tail&&check(h[tail], h[tail - 1], h[head])) {tail--;}
	while (head<tail&&check(h[head + 1], h[head], h[tail])) {head++;}
}
int main () {
	R(n);
	long double x, y1, y2;
	 l[++cnt].a = P(-1e-13, 1e-13), l[cnt].b = P(-1e-13, inf);
    l[++cnt].a = P(-1e-13, inf), l[cnt].b = P(-inf, inf);
    l[++cnt].a = P(-inf, inf), l[cnt].b = P(-inf, 1e-13);
    l[++cnt].a = P(-inf, 1e-13), l[cnt].b = P(-1e-13, 1e-13);
	for (int i = 1; i <= n; ++i) {
		R(x), R(y1), R(y2);
		l[++cnt].a.x = -1;
		l[cnt].a.y = (y1+(x*x)) / x;
		l[cnt].b.x = 1;
		l[cnt].b.y = (y1 - x * x) / x;
		l[++cnt].b.x = -1;
		l[cnt].b.y = (y2+(x*x)) / x;
		l[cnt].a.x = 1;
		l[cnt].a.y = (y2 - x * x) / x;
		l[cnt].id=l[cnt-1].id=i;
	}
	for (int i = 1; i <= cnt; ++i) {
		l[i].slop = atan2(l[i].b.x - l[i].a.x, l[i].b.y - l[i].a.y);
	}
	int L = 1, R = n + 1, mid, temp;
	sort(l+1, l+cnt+1);
	while (L < R - 1) {
		mid = L + R >> 1;
		hpi(mid);
		if (tail - head >= 2) {
			L = mid;
		} else R = mid;
	}
	printf("%d\n", L);
	return 0; 
}
