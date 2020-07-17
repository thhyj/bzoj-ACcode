
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
#define MAXN 1010
double alpha;
int N, num;
#define INF 1e12
#define eps 1e-5
struct Point
{
    double x, y;
    Point (double x, double y): x(x), y(y) {}
    Point() {}
};
struct Circle
{
    double r;
    Point c;
    Circle(Point c, double r) : c(c), r(r) {}
    Circle() {}
} C[MAXN];
struct Line
{
    Point s, t;
    double f(double x) {return s.y - (s.y - t.y) * ((x - s.x) / (t.x - s.x));}
} l[MAXN];
double F(double x)
{
    double re = 0;
    for (int i = 1; i <= N; i++) //枚举圆是否与扫描线有交
    {
        double d = fabs(x - C[i].c.x);
        if (d - C[i].r >= 0) continue;
        double len = 2 * sqrt(C[i].r * C[i].r - d * d);
        re = max(re, len);
    }
    for (int i = 1; i <= num; i++) //枚举公切线
        if (x >= l[i].s.x && x <= l[i].t.x) re = max(re, 2 * l[i].f(x));
    return re;
} //利用扫描线去判断
double Calc(double l, double r) {double mid = (l + r) / 2; return (F(l) + F(r) + F(mid) * 4) * (r - l) / 6;}
double Simpson(double l, double r, double now)
{
    double mid = (l + r) / 2;
    double x = Calc(l, mid), y = Calc(mid, r);
    if (fabs(now - x - y) < eps) return now;
    else return Simpson(l, mid, x) + Simpson(mid, r, y);
}
void Solve()
{
    double L = INF, R = -INF;
    for (int i = 1; i <= N + 1; i++)
        L = min(L, C[i].c.x - C[i].r), R = max(R, C[i].c.x + C[i].r);
//  printf("%lf\n%lf\n",L,R);
    for (int i = 1; i <= N; i++)
    {
        double d = C[i + 1].c.x - C[i].c.x;
        if (d - fabs(C[i].r - C[i + 1].r) <= 0) continue; //特判小圆被大圆覆盖的情况
        double sina = (C[i].r - C[i + 1].r) / d, cosa = sqrt(1 - sina * sina);
        l[++num] = (Line) {(Point) {C[i].c.x + C[i].r * sina, C[i].r * cosa}, (Point) {C[i + 1].c.x + C[i + 1].r*sina, C[i + 1].r*cosa}};
    }
    printf("%.2lf\n", Simpson(L, R, Calc(L, R)));
}
int main()
{
    scanf("%d%lf", &N, &alpha);
    double h, r;
    for (int i = 1; i <= N + 1; i++)
        scanf("%lf", &h),
        C[i] = (Circle) {((Point) {(h / tan(alpha)) + C[i - 1].c.x, 0}), 0};
    for (int i = 1; i <= N; i++)
        scanf("%lf", &r), C[i].r = r;
//  for (int i=1; i<=N+1; i++)
//      printf("%d     %.2lf     %.2lf\n",i,C[i].c.x,C[i].r);
    Solve();
    return 0;
}
