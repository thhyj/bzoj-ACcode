
#include <bits/stdc++.h>
using namespace std;
struct point {
    double x, y;
    point(double x, double y) : x(x), y(y) {}
    point() {}
} p[100005];
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
inline bool incircle(const point &a) {
    return getdis(a, o.a) <= o.r;
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
inline void solve(const point &p1, const point &p2, const point &p3) {
	line zhongchui1 = line(point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2), point((p2.y - p1.y) / 2 + (p1.x + p2.x) / 2, (p1.x - p2.x) / 2 + (p1.y + p2.y) / 2));
	line zhongchui2 = line(point((p3.x + p2.x) / 2, (p3.y + p2.y) / 2), point((p2.y - p3.y) / 2 + (p3.x + p2.x) / 2, (p3.x - p2.x) / 2 + (p3.y + p2.y) / 2));
    o.a = inter(zhongchui2, zhongchui1);
    o.r = getdis(o.a , p1);
}
int main () {
//  freopen("in.in", "r", stdin);
//  freopen("minimalcircle.in", "r", stdin);
//  freopen("minimalcircle.out", "w", stdout);
//  while (1) {
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
                            //      printf("p[%d].x = %lf p[%d].y = %lf p[%d].x = %lf p[%d].y = %lf p[%d].x = %lf p[%d].y = %lf\n", i, p[i].x, i, p[i].y, j, p[j].x, j, p[j].y, k, p[k].x, k, p[k].y );
                            //      printf("o.x = %lf, o.y = %lf\n", o.a.x, o.a.y );
                        }
                    }
                }
            }
        }
    }
    printf("%0.3lf\n", o.r);
    //}
    return 0;
}
