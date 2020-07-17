
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
using namespace std;
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
inline void R(long double &v) {
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
struct tree {
    int p, r, m, updcnt, sum;
    bool stop;
} tr[1 << 17];
int n, T, c, mod, opt, l, r;
int p[32], cnt, a[50005];
int table[32][1 << 16][2];
inline int ksm(long long a, long long b, long long p) {
    long long res = 1;
    while (b)
    {
        if (b & 1LL) res = (res * a) % p;
        a = (a * a) % p;
        b >>= 1LL;
    }
    return res;
}
inline int phi(long long x) {
    long long res = x;
    for (int i = 2; i * i <= x; i++)
        if (!(x % i))
        {
            res /= i; res *= (i - 1);
            while (!(x % i)) x /= i;
        }
    if (x != 1) res /= x, res *= (x - 1);
    return res;
}
inline int pow(int a, int b) {
    return 1LL * table[b][a & 65535][0] * table[b][a >> 16][1] % p[b];
}
inline int calc(int x, int t) {
    int res = x;
    if (res >= p[t]) res = res % p[t] + p[t];
    while (t--)
    {
        x = res; res = pow(x, t);
        if (t && !res) res += p[t];
    }
    return res % mod;
}
inline void updata(int x) {
    if (tr[x << 1].stop && tr[x << 1 | 1].stop) tr[x].stop = true;
    tr[x].sum = (tr[x << 1].sum + tr[x << 1 | 1].sum) % mod;
    return ;
}
inline void build(int x) {
    if (tr[x].p + 1 == tr[x].r)
    {
        tr[x].sum = a[tr[x].p];
        return ;
    }
    tr[x].m = tr[x].p + tr[x].r >> 1;
    tr[x << 1].p = tr[x].p; tr[x << 1].r = tr[x].m; build(x << 1);
    tr[x << 1 | 1].p = tr[x].m; tr[x << 1 | 1].r = tr[x].r; build(x << 1 | 1);
    updata(x);
    return ;
}
inline void modify(int x, int l, int r) {
    if (tr[x].stop) return ;
    if (tr[x].p + 1 == tr[x].r)
    {
        if ((++tr[x].updcnt) == cnt) tr[x].stop = true;
        tr[x].sum = calc(a[l], tr[x].updcnt);
        return ;
    }
    if (r <= tr[x].m) modify(x << 1, l, r);
    else if (tr[x].m <= l) modify(x << 1 | 1, l, r);
    else
    {
        modify(x << 1, l, tr[x].m);
        modify(x << 1 | 1, tr[x].m, r);
    }
    updata(x);
    return ;
}
inline int query(int x, int l, int r) {
    if (tr[x].p == l && tr[x].r == r) return tr[x].sum;
    if (r <= tr[x].m) return query(x << 1, l, r);
    else if (tr[x].m <= l) return query(x << 1 | 1, l, r);
    else return (query(x << 1, l, tr[x].m) + query(x << 1 | 1, tr[x].m, r)) % mod;
}
int main() {
    R(n); R(T); R(mod); R(c);
    for (int i = 1; i <= n; i++) R(a[i]);
    p[0] = mod;
    while (p[cnt] != 1) p[cnt + 1] = phi(p[cnt]), cnt++;
    p[++cnt] = 1;
    for (int i = 0; i <= cnt; i++) {
        r = ksm(c, 1 << 16, p[i]);
        table[i][0][0] = table[i][0][1] = 1;
        for (int j = 1; j < (1 << 16); j++) {
            table[i][j][0] = 1LL * table[i][j - 1][0] * c % p[i];
            table[i][j][1] = 1LL * table[i][j - 1][1] * r % p[i];
        }
    }
    tr[1].p = 1; tr[1].r = n + 1; build(1);
    while (T--) {
        R(opt); R(l); R(r);
        if (!opt) modify(1, l, r + 1);
        else printf("%d\n", query(1, l, r + 1));
    }
    return 0;
}
