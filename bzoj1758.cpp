
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
        v = (v + (v << 2) << 1) + (ch^'0');
        ch =  getchar();
    }
    if (p) v = -v;
}
struct node {
    int to;
    double length;
    node (int to, double length): to(to), length(length) {}
    node() {}
};
std::vector<node> q[100005];
int n;
int L, U;
const int inf = INT_MAX - 10000;
inline void create(int x, int y, int z) {
    q[x].push_back(node(y, z));
    q[y].push_back(node(x, z));
}
const double eps = 1e-4;
int cnt, rt[100005], siz[100005], d[100005];
bool vis[100005];
int sum;
int D;
int dep[100005], que[100005];
double dis[100005], c[100005], a[100005];
inline void findrt(int x, int f) {
    siz[x] = 1;
    d[x] = 0;
    node *p;
    for (int i = 0; i < q[x].size(); ++i) {
        p = &q[x][i];
        if ((!vis[p->to]) && p->to != f) {
            findrt(p->to, x);
            siz[x] += siz[p->to];
            d[x] = max(siz[p->to], d[x]);
        }
    }
    d[x] = max(d[x], sum - siz[x]);
    if (d[x] < d[rt[cnt]]) rt[cnt] = x;
}
inline void init(int x) {
    node *p;
    ++cnt;
    findrt(x, x);
    x = rt[cnt];
    ////cout << "x1=" << x << '\n';
    vis[x] = 1;
    //  //printf("q[%d].size()=%d\n", x, q[x].size());
    for (int i = 0; i < q[x].size(); ++i) {
        p = &q[x][i];
        if (!vis[p->to]) {
            sum = siz[p->to];
            init(p->to);
        }
    }
}

struct data {
    int x, d;
    data(int x, int d) : x(x), d(d) {
    }
    data() {}
} s[100005];
inline void getdep(int x, int f) {
    if (dep[x] > U)return;

    node *p;
    D = max(D, dep[x]);
    for (int i = 0; i < q[x].size(); ++i) {
        p = &q[x][i];
        if ((!vis[p->to]) && p->to != f) {
            dep[p->to] = dep[x] + 1;
            getdep(p->to, x);
        }
    }
}
int tot;
inline bool cmp(const data&a, const data&b) {
    return a.d < b.d;
}
inline void getdis(int x, int f) {
    if (dep[x] > U)return;
    node *p;
    a[dep[x]] = max(dis[x], a[dep[x]]);
    for (int i = 0; i < q[x].size(); ++i) {
        p = &q[x][i];
        if (p->to != f && (!vis[p->to])) {
            dis[p->to] = dis[x] + p->length;
            getdis(p->to, x);
        }
    }
}
double ans;
inline void solve(int x) {
    x = rt[++cnt];
    node *p;
    tot = 0;
//  cout << "x=" << x << '\n';
    for (int i = 0; i < q[x].size(); ++i) {
        p = &q[x][i];
        if ((!vis[p->to])) {
            //cout << "p->to=" << p->to << '\n';
            D = dep[p->to] = 1;
            dis[p->to] = p->length;
            getdep(p->to, x);
            s[++tot] = data(p->to, D);
        }
    }
    sort(s + 1, s + tot + 1, cmp);

    D = 0;
    for (int i = 1; i <= tot; ++i) {
        getdis(s[i].x, x);
        int l = 1, r = 0, pl = D, pr = D;
        for (int j = 1; j <= s[i].d; ++j) {
            while (pl >= 0 && pl >= L - j) {
                while (l <= r && c[que[r]] < c[pl])--r;
                que[++r] = pl--;
            }
            pr = max(U - j + 1, 0);
            while (l <= r && que[l] >= pr)l++;

            if (l <= r) ans = max(ans, a[j] + c[que[l]]);
        }
        for (int j = 1; j <= s[i].d; ++j) {c[j] = max(c[j], a[j]), a[j] = -inf;}
        D = max(D, s[i].d);
    }
    for (int j = 1; j <= D; ++j)c[j] = -inf;
    if (ans >= 0) return ;
    vis[x] = 1;
    for (int i = 0; i < q[x].size(); ++i) {
        p = &q[x][i];
        if (!vis[p->to]) {
            solve(p->to);
            if (ans >= 0) return ;
        }
    }
}
inline bool check(double mid) {
    node *p;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < q[i].size(); ++j) {
            q[i][j].length -= mid;
        }
    }
    memset(vis, 0 , sizeof(bool) * (n + 2));
    cnt = 0;
    ans = -inf;
    solve(1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < q[i].size(); ++j) {
            q[i][j].length += mid;
        }
    }
    //printf("ans=%0.6lf\n", ans);
    return ans >= 0;
}
inline bool cmp1(const int &a, const int &b) {
    return dep[a] < dep[b];
}
int main () {
    //freopen("cckk.in", "r", stdin);
    //freopen("ou.out", "w", stdout);
    R(n), R(L), R(U);
    int x, y, z;
    for (int i = 1; i < n; ++i) {
        R(x), R(y), R(z);
        create(x, y, z);
    }
    d[0] = inf;
    sum = n;
    init(1);
    //cout << "cnt=" << cnt << '\n';

    for (int i = 1; i <= n; i++)a[i] = c[i] = -inf;
    double l = 0, r = 1000000, mid;
    while (r - l > eps) {
        mid = (l + r) / 2;
        if (check(mid))l = mid;
        else r = mid;
    }
    printf("%0.3lf", l);
    return 0;
}
