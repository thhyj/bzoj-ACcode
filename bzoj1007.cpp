
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
} p[1000005], a[1000005];
inline point1 operator -(const point1 &a, const point1 &b) {
    return point1(a.x - b.x, a.y - b.y);
}
inline double operator * (const point1 &a, const point1 &b) {
    return a.x * b.y - a.y * b.x;
}
struct  line {
    point1 a, b;
    double slop;
    int pos;
} l[1000005], h[1000005];
const double eps = 1e-9;
inline bool operator < (const line &a, const line &b) {
    return a.slop < b.slop || (a.slop == b.slop && (a.b - a.a) * (b.b - a.a) > 0);
}
int cnt, tot;
int head, tail;
double k1, k2;
point1 ret;
int ans [1000005];
inline point1 inter (const line &a, const line &b) {
    k1 = (b.b - a.a) * (a.b - a.a);
    k2 = (a.b - a.a) * (b.a - a.a);
    k1 = k1 / (k1 + k2);
    ret = point1 (b.b.x - (b.b.x - b.a.x) * k1, b.b.y - (b.b.y - b.a.y) * k1);
    return ret;
}
inline bool check(line a, line b, line t) {
    point1 temp = inter(a, b);
    return (t.b - t.a) * (temp - t.a) <=  0;
}
inline void hpi() {
    sort(l + 1, l + cnt + 1);
    for (int i = 1; i <= cnt; ++i) {
        if (l[i].slop != l[i + 1].slop)
            l[++tot] = l[i];
    //    printf("l[%d].slop=%lf\n",tot,l[tot].slop);
    }
    head=1;
    h[++tail] = l[1], ans[tail] = l[1].pos, h[++tail] = l[2], ans[tail] = l[2].pos;
    for (int i = 3; i <= tot; ++i) {
        while (tail > head && check(h[tail - 1], h[tail], l[i])) tail--;
        while (tail > head && check(h[head + 1], h[head], l[i])) head++;
        h[++tail] = l[i], ans[tail] = l[i].pos;
    }
   // cout<<"tail="<<tail<<" head="<<head<<'\n';
    while (head< tail && check(h[head + 1], h[head], h[tail])) head++;
    while (head< tail && check(h[tail - 1], h[tail], h[head])) tail--;
 //   h[tail + 1] = h[head];
  //  tot = 0;
   //   cout<<"tail="<<tail<<" head="<<head<<'\n';
    sort(ans+head,ans+tail+1);
    for (int i = head; i <= tail; ++i) {
        printf("%d ",ans[i]);
    }
}
//double ans;
int main() {
    int n;
    R(n);
    int m;
//  cout<<"n="<<n<<'\n';
    int k, b;
    int tot1 = 0;
    for (int i = 1; i <= n; ++i) {
        R(k), R(b);
        p[++tot1].x = -1;
        p[tot1].y = b-k;
        p[++tot1].x = 1;
        p[tot1].y = k+b;
        l[++cnt].a = p[tot1-1];
        l[cnt].b = p[tot1];
        l[cnt].pos = cnt;
    }
    //p[tot+1] = p[1];
    for (int i = 1; i <= cnt; ++i) {
        l[i].slop = atan2(l[i].b.y - l[i].a.y, l[i].b.x - l[i].a.x);
    }
    hpi();
   // getans();
   // printf("%0.3f\n", ans);
    return 0;
}
