
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
inline void R (double &v) {
	static char ch;
	v = 0;
	bool p = 0;
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
struct point {
	double x, y;
	point (double x, double y): x(x), y(y) {}
	point() {}
} a, b, c, d;
double dis1, dis2;
double p, q, r;
const double eps = 1e-9;
inline double getdis(const point & a, const point &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
point now1, now2;
double t;
inline double calc1(double dis) {
	if (dis2 <= eps) now1 = a; else {
		now2 = point((d.x - c.x) * (dis2 - dis) / dis2 + c.x, (d.y - c.y) * (dis2 - dis) / dis2 + c.y);
	}
	double ret = t;
	ret += dis / (double)q + getdis(now1, now2) / (double)r;
	return ret;
}
inline double calc(double dis) {
	if (dis1 <= eps) now1 = a; else {
		t = dis / (double)p;
		now1 = point((b.x - a.x) * dis / dis1 + a.x, (b.y - a.y) * dis / dis1 + a.y);
	}
	double l = 0, r = dis2, l1, r1, ans1, ans2, ret = INT_MAX;
	for (int i = 1; i <= 100; ++i) {
		l1 = l + (r - l) / 3.0;
		r1 = r - (r - l) / 3.0;
		ans1 = calc1(l1), ans2 = calc1(r1);
		if (ans1 <= ans2) r = r1;
		else l = l1;
		ret = min(ret, min(ans1, ans2));
	}
	return ret;
}

int main () {
	R(a.x), R(a.y), R(b.x), R(b.y), R(c.x), R(c.y), R(d.x), R(d.y);
	R(p), R(q), R(r);
	dis1 = getdis(a, b);
	dis2 = getdis(c, d);
	double l = 0, r = dis1, l1, r1, ans1, ans2, ans = INT_MAX;

	for (int i = 1; i <= 100; ++i) {
		l1 = l + (r - l) / 3.0;
		r1 = r - (r - l) / 3.0;
		ans1 = calc(l1), ans2 = calc(r1);
		if (ans1 <= ans2) r = r1;
		else l = l1;
		ans = min(ans, min(ans1, ans2));
	}
	printf("%0.2lf\n", ans);
	return 0;
}
