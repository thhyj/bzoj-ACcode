
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-12;
inline void R(int &v) {
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
inline void R(long long &v) {
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
inline void R(double &v) {
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
struct P {
    double x, y, slop;
} p[10005], t[10005][4], pp[10005], tri[10005][3];
inline double getslop(const P &a) {
    return atan2(a.y, a.x);
}
inline bool operator == (const P &a, const P &b)  {
    return a.x == b.x && a.y == b.y;
}
inline bool operator < (const P &a,const P &b) {
    return a.slop < b.slop;
}
inline double operator * (const P &a, const P &b) {
    return a.x * b.y - a.y * b.x;
}
inline P operator - (const P &a, const P &b) {
    return (P) {a.x - b.x, a.y - b.y};
}
inline P operator + (const P &a, const P &b) {
    return (P) {a.x + b.x, a.y + b.y};
}
inline double dot(const P &a, const P &b) {
    return a.x * b.x + a.y * b.y;
}
double k1, k2;
inline P inter (const P &a1, const P &a2, const P &b1, const P &b2) {
   P temp;
    k1 = (b2 - a1) * (a2 - a1);
    k2 = (a2 - a1) * (b1 - a1);
    k1 = k1 / (k1 + k2);
    temp = (P) {b2.x - (b2.x - b1.x) * k1, b2.y - (b2.y - b1.y) * k1};
    return temp;
}
P base;
const P O = {0, 0};
inline double getlen(const P &a) {
    return sqrt(a.x * a.x + a.y * a.y);
}
int dcmp(double x) {
    if (fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}
struct L {
    P a, b;
    int id, in;
    double slop;
    L(P a, P b, int in , int id, double slop): a(a), b(b), in(in), id(id), slop(slop) {}
    L() {}
    bool operator < (const L &u) const {
        if (a == u.a) {
            return (b - a) * (u.b - a) < 0;
        }
        P a1 = inter(a, b, O, base);
        P b1 = inter(u.a, u.b, O, base);
        return getlen(a1) < getlen(b1);
    }
} l[1000005] ;
int cnt;
inline bool cmp(const L &a, const L &b) {
    return dcmp(a.slop - b.slop) < 0 || dcmp(a.slop - b.slop) == 0 && a.in > b.in;
}
int tot, all;
const double Pi = acos(-1);
P T;
inline void add(P a, P b, int id) {
    if (a.slop > b.slop) swap(a,b);
    l[all++] = L(a, b, 1, id, a.slop);
    l[all++] = L(b, a, 0, id, b.slop);
}
multiset<L>s;
multiset<L>::iterator it[10005];
double calc(L x) {
    P a = inter(x.a, x.b, O, base);
    return getlen(a);
}
inline int solve(int n) {
    sort(p, p  + n);
    sort(l, l + all, cmp);
    int i = 0, j = 0;
    s.clear();
    int ret = 0;
    for (i; i < n; ++i) {
        while (j < all && (dcmp(l[j].slop - p[i].slop) < 0 || (dcmp(l[j].slop - p[i].slop) == 0 && l[j].in))) {
            base = l[j].a;
            if (l[j].in) {
                it[l[j].id] = s.insert(l[j]);
            } else {
                s.erase(it[l[j].id]);
            }
            ++j;
        }
        if (s.empty()) {
            ++ret; continue;
        }
        base = p[i];
        double dis = calc(*s.begin());
      //  printf("%lf\n",dis);
        if (dcmp(getlen(p[i]) - dis) <= 0) ++ret;
    }
    return ret;
}
int ans;
int main () {
 //  freopen("draft.in", "r", stdin);
 //   freopen("draft.out", "w", stdout);
    int V, n;
    R(V), R(n);
    for (int i = 1; i <= V; ++i) {
        R(pp[i].x), R(pp[i].y);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 3; ++j)
            R(tri[i][j].x), R(tri[i][j].y);
    }
    double mx = 0, ang = 0;
    P u, v;
    for (int i = 1; i <= V; ++i) {
        cnt = tot = all = 0;
        for (int  j = i + 1; j <= V; ++j) {
            p[cnt++] = pp[j] - pp[i];
            p[cnt-1].slop = getslop(p[cnt-1]);
        }
        for (int j = 1; j <= n; ++j) {
            for (int k = 0; k < 3; ++k) {
                t[j][k] = (tri[j][k] - pp[i]);
            }
            t[j][3] = t[j][0];
            mx = 0;
            for (int k = 0; k < 3; ++k) {
                ang =  dot(t[j][k], t[j][k + 1]) / getlen(t[j][k]) / getlen(t[j][k + 1]);
                ang = acos(ang);
          //      cout<<"ang="<<ang<<'\n';
                if (ang > mx) {
                    mx = ang;
                    u = t[j][k];
                    v = t[j][k + 1];
                }
            }   
            u.slop = getslop(u), v.slop = getslop(v);
         //   cout<<"i="<<i<<'\n';
        //    cout<<"j="<<j<<'\n';
          //  cout<<"u.ang="<<u.slop<<" v.ang="<<v.slop<<'\n';
            if (fabs(u.slop - v.slop) < Pi) {
                add(u, v, tot++);
            } else {
                P temp = inter (u, v, O, (P) { -1.0, 0});
          //     cout<<"temp.x="<<temp.x<<" temp.y="<<temp.y<<'\n';
                temp.slop = Pi * dcmp(u.slop);
                add(u, temp, tot++);
                temp.slop = Pi * dcmp(v.slop);
                add(v, temp, tot++);
            }
        }
        int ret = solve(cnt);
        ans += ret;
    }
    cout << ans;
    return 0;
}
