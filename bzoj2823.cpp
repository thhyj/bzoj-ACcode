
#include <bits/stdc++.h>
using namespace std;
struct point {
	double x, y;
	point(double x, double y) : x(x), y(y) {}
	point() {}
} p[1000005];
struct yuan {
	point a;
	double r;
	yuan(point a, double r): a(a), r(r) {}
	yuan() {}
} o;
int n;
inline double getdis(const point &a, const point &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
const double eps = 1e-6;
inline bool incircle(const point &a) {
	return (getdis(a, o.a) - o.r) <= eps;
}
struct  line {
	point a, b;
	line (point a, point b): a(a), b(b) {}
	line() {}
};
line zhongchui1, zhongchui2;
double k1, k2;

inline point operator -(const point &a, const  point &b) {
	return point (a.x - b.x, a.y - b.y);
}
inline double operator *(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}
inline point inter (const line &a, const line &b) {
	k1 = (b.b - a.a) * (a.b - a.a);
	k2 = (a.b - a.a) * (b.a - a.a);
	k1 = k1 / (k1 + k2);
	return point(b.b.x - (b.b.x - b.a.x) * k1, b.b.y - (b.b.y - b.a.y) * k1);
}
inline void solve(const point &a, const point &b, const point &c) {
	zhongchui1 = line(point ((a.x + b.x) / 2, (a.y + b.y) / 2), point((a.x + b.x) / 2 - (a.y - b.y) / 2, (a.y + b.y) / 2 + (a.x - b.x) / 2));
//	printf("zhongchui1.b.x=%lf zhongchui1.b.y=%lf\n", zhongchui1.b.x, zhongchui1.b.y );
	zhongchui2 = line(point ((a.x + c.x) / 2, (a.y + c.y) / 2), point((a.x + c.x) / 2 - (a.y - c.y) / 2, (a.y + c.y) / 2 + (a.x - c.x) / 2));
//	printf("zhongchui2.b.x=%lf zhongchui2.b.y=%lf\n", zhongchui2.b.x, zhongchui2.b.y );

	o.a = inter(zhongchui2, zhongchui1);
	o.r = getdis(o.a , a);
}
int main () {
//	freopen("in.in", "r", stdin);
//	freopen("minimalcircle.in", "r", stdin);
//	freopen("minimalcircle.out", "w", stdout);
//	while (1) {
	scanf("%d", &n);
	if (!n) return 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%lf%lf", &p[i].x, &p[i].y);
	}
	o.a = point(0, 0), o.r = 0;
	random_shuffle(p + 1, p + 1 + n);
	for (int i = 1; i <= n; ++i) {
		if (!incircle(p[i])) {
			o.a = p[i];
			o.r = 0;
			for (int j = 1; j < i; ++j) {
				if (!incircle(p[j])) {
					o.a = point ((p[i].x + p[j].x) / 2, (p[i].y + p[j].y) / 2);
					o.r = getdis(p[i], p[j]) / 2;
					for (int k = 1; k < j; ++k) {
						if (!incircle(p[k])) {
							solve(p[i], p[j], p[k]);
							//		printf("p[%d].x = %lf p[%d].y = %lf p[%d].x = %lf p[%d].y = %lf p[%d].x = %lf p[%d].y = %lf\n", i, p[i].x, i, p[i].y, j, p[j].x, j, p[j].y, k, p[k].x, k, p[k].y );
							//		printf("o.x = %lf, o.y = %lf\n", o.a.x, o.a.y );
						}
					}
				}
			}
		}
	}
	printf("%0.2lf %0.2lf %0.2lf\n", o.a.x, o.a.y, o.r );
	//}
	return 0;
}
