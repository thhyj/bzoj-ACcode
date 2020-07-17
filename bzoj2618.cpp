
#include <bits/stdc++.h>
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
inline void R(double &v) {
	static char ch;
	bool p = 0;
	v = 0;
	do {
		ch = getchar();
		if (ch == '-') p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = v * 10 + (ch^'0');
		ch = getchar();
	}
	if (p) v = -v;
}
struct  point1 {
	double x, y;
	point1(double x, double y): x(x), y(y) {}
	point1() {}
} p[10005], a[10005];
inline point1 operator -(const point1 &a, const point1 &b) {
	return point1(a.x - b.x, a.y - b.y);
}
inline double operator * (const point1 &a, const point1 &b) {
	return a.x * b.y - a.y * b.x;
}
struct  line {
	point1 a, b;
	double slop;
} l[10005], h[10005];
inline bool operator < (const line &a, const line &b) {
	if (a.slop != b.slop) return a.slop < b.slop;
	return (a.b - a.a) * (b.b - a.a) > 0;
}
int cnt, tot;
int head, tail;
double k1, k2;
point1 ret;
inline point1 inter (const line &a, const line &b) {
	k1 = (b.b - a.a) * (a.b - a.a);
	k2 = (a.b - a.a) * (b.a - a.a);
	k1 = k1 / (k1 + k2);
	ret = point1 (b.b.x - (b.b.x - b.a.x) * k1, b.b.y - (b.b.y - b.a.y) * k1);
	return ret;
}
inline bool check(line a, line b, line t) {
	point1 temp = inter(a, b);
	return (t.b - t.a) * (temp - t.a) < 0;
}
inline void hpi() {
	sort(l + 1, l + cnt + 1);
	for (int i = 1; i <= cnt; ++i) {
		if (l[i].slop != l[i + 1].slop)
			l[++tot] = l[i];
	}
	head=1;
	h[++tail] = l[1], h[++tail] = l[2];
	for (int i = 3; i <= tot; ++i) {
		while (tail > head && check(h[tail - 1], h[tail], l[i])) tail--;
		while (tail > head && check(h[head + 1], h[head], l[i])) head++;
		h[++tail] = l[i];
	}
	while (head < tail && check(h[head + 1], h[head], h[tail])) head++;
	while (head < tail && check(h[tail - 1], h[tail], h[head])) tail--;
	h[tail + 1] = h[head];
	tot = 0;
	for (int i = head; i <= tail; ++i) {
		a[++tot] = inter(h[i], h[i + 1]);
	}
}
double ans;
inline void getans() {
	if (tot < 3) return ;
	a[tot + 1] = a[1];
	for (int i = 1; i <= tot; ++i) {
		ans += a[i + 1] * a[i];
	}
	ans /= 2;
	ans = ans > 0 ? ans : -ans;
}
int main() {
	int n;
	R(n);
	int m;
//	cout<<"n="<<n<<'\n';
	for (int i = 1; i <= n; ++i) {
		R(m);
		for (int j = 1; j <= m; ++j) {
			R(p[j].x), R(p[j].y);
		}
		p[m + 1] = p[1];
		for (int j = 1; j <= m; ++j) {
			l[++cnt].a = p[j];
			l[cnt].b = p[j + 1];
		}
	}
	for (int i = 1; i <= cnt; ++i) {
		l[i].slop = atan2(l[i].b.y - l[i].a.y, l[i].b.x - l[i].a.x);
	}
	hpi();
	getans();
	printf("%0.3f\n", ans);
	return 0;
}
