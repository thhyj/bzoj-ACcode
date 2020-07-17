
#include <iostream>
#include <cstdio>
#include <algorithm>
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
inline void R(long long &v) {
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
int n, tot;
long long x[50005], y[50005], f[50005];;
int q[50005];
struct data {long long x, y;} a[50005];
inline bool cmp(data a, data b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}
inline double slop(int a, int b) {
    return (double)(f[b] - f[a]) / (y[a + 1] - y[b + 1]);
}
int main()
{
    R(n);
    for (int i = 1; i <= n; i++)
        R(a[i].x), R(a[i].y);
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++) {
        while (tot && a[i].y >= y[tot])tot--;
        x[++tot] = a[i].x; y[tot] = a[i].y;
    }
    int l = 0, r = 0;
    for (int i = 1; i <= tot; i++) {
        while (l < r && slop(q[l], q[l + 1]) < x[i])l++;
        int t = q[l];
        f[i] = f[t] + y[t + 1] * x[i];
        while (l < r && slop(q[r], i) < slop(q[r - 1], q[r]))r--;
        q[++r] = i;
    }
    cout<<f[tot]; 
    return 0;
}
