
#include <bits/stdc++.h>
using namespace std;
inline void R(int &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
		ch = getchar();
		if (ch == '-') p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = (v  + (v << 2) << 1) + (ch^'0');
		ch = getchar();
	}
	if (p)v = -v;
}
struct point {
	double x, y;
	point(double x, double y): x(x), y(y) {}
	point() {}
} p[50005];
struct yuan {
	point x;
	double r;
	yuan(point x, double r): x(x), r(r) {}
	yuan() {}
} o;
struct line {
	point a, b;
	line(point a, point b): a(a), b(b) {}
	line() {}
};
inline double operator *(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}
inline point operator - (const point &a, const point&b) {
	return point(a.x - b.x, a.y - b.y);
}
inline point inter(line a, line b) {
	double k1 = (b.b - a.a) * (a.b - a.a);
	double k2 = (a.b - a.a) * (b.a - a.a);
	k1 = k1 / (k1 + k2);
	return point(b.b.x - (b.b.x - b.a.x) * k1, b.b.y - (b.b.y - b.a.y) * k1);
}
int n;
double a;
double beishu;
const double pi = acos(-1);
inline void rotate(point &a, double alpha) {
	double tx = a.x, ty = a.y;
	a.x = tx * cos(alpha) - ty * sin(alpha);
	a.y = tx * sin(alpha) + ty * cos(alpha);
	a.x /= beishu;
}
inline double getdis(point &a, point &b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
inline void findo(point &p1, point &p2, point &p3) {
	line zhongchui1 = line(point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2), point((p2.y - p1.y) / 2 + (p1.x + p2.x) / 2, (p1.x - p2.x) / 2 + (p1.y + p2.y) / 2));
	line zhongchui2 = line(point((p3.x + p2.x) / 2, (p3.y + p2.y) / 2), point((p2.y - p3.y) / 2 + (p3.x + p2.x) / 2, (p3.x - p2.x) / 2 + (p3.y + p2.y) / 2));
	o.x = inter(zhongchui2, zhongchui1);
	o.r = getdis(p1, o.x);
}
inline bool incircle(point &a) {
	return getdis(a, o.x) <= o.r;
}
int main () {
	srand(19260817);
	R(n);
	int x, y;
	for (int i = 1; i <= n; ++i) {
		R(x), R(y);
		p[i] = point(x, y);
	}
	scanf("%lf", &a);
	scanf("%lf", &beishu);
	a = (1.0 - (a / 360)) * acos(-1) * 2;
	for (int i = 1; i <= n; ++i) {
		rotate(p[i], a);
		//		printf("p[%d].x = %f, p[%d].y = %f\n", i, p[i].x, i, p[i].y);
	}
	random_shuffle(p + 1, p + n + 1);
	for (int i = 1; i <= n; ++i) {
		if (!incircle(p[i])) {
			o.x = p[i], o.r = 0;
			for (int j = 1; j < i; ++j) {
				if (!incircle(p[j])) {
					o.x = point((p[i].x + p[j].x) / 2, (p[i].y + p[j].y) / 2);
					o.r = getdis(o.x, p[i]);
					for (int k = 1;  k < j; ++k) {
						if (!incircle(p[k])) {
							findo(p[i], p[j], p[k]);
						}
					}
				}
			}
		}
	}
	printf("%0.3f\n", sqrt(o.r));
}
