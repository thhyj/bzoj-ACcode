
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
const int maxn = 60010;
int ma[maxn][3];
struct node {
    int l, r, lsm, rsm, lm, rm, hm, sum, cnt;
} tr[maxn << 2];
int n, m;
char ch[10];
inline int max(int a, int b, int c)   {
    return max(a, max(b, c));
}
inline int max(int a, int b, int c, int d) {
    return max(max(a, b), max(c, d));
}
inline node merge(node x, node y) {
    node z;
    z.l = x.l, z.r = y.r;
    int mh = max(ma[x.r][0], ma[x.r][1]), mx = max(x.rm, y.lm, mh);
    z.sum = x.sum + y.sum + ma[x.r][0] + ma[x.r][1] - mx, z.hm = max(x.hm, y.hm, mh), z.cnt = x.cnt + y.cnt;
    if (mx == x.rsm && x.cnt == 1) {
        z.lsm = y.lsm, z.rsm = y.rsm, z.lm = max(x.hm, y.lm, mh), z.rm = y.rm, z.cnt--;
    }
    else {
        if (mx == y.lsm && y.cnt == 1) {
            z.lsm = x.lsm, z.rsm = x.rsm, z.lm = x.lm, z.rm = max(x.rm, y.hm, mh), z.cnt--;
        }
        else {
            z.lsm = x.lsm, z.rsm = y.rsm, z.lm = x.lm, z.rm = y.rm, z.cnt -= (mx == x.rsm || mx == y.lsm);
        }
    }
    return z;
}
inline void init(node &x) {
    x.lsm = x.rsm = x.lm = x.rm = x.sum = ma[x.l][2], x.hm = 0, x.cnt = 1;
}
void build(int l, int r, int x) {
    if (l == r) {
        tr[x].l = l, tr[x].r = r, init(tr[x]);
        return ;
    }
    int mid = (l + r) >> 1;
    build(l, mid, x << 1), build(mid + 1, r, x << 1 | 1);
    tr[x] = merge(tr[x << 1], tr[x << 1 | 1]);
}
void updata(int l, int r, int x, int a) {
    if (l == r) {
        init(tr[x]);
        return ;
    }
    int mid = (l + r) >> 1;
    if (a <= mid)   updata(l, mid, x << 1, a);
    else    updata(mid + 1, r, x << 1 | 1, a);
    tr[x] = merge(tr[x << 1], tr[x << 1 | 1]);
}
node query(int l, int r, int x, int a, int b) {
    if (a <= l && r <= b)    return tr[x];
    int mid = (l + r) >> 1;
    if (b <= mid)   return query(l, mid, x << 1, a, b);
    if (a > mid)    return query(mid + 1, r, x << 1 | 1, a, b);
    return merge(query(l, mid, x << 1, a, b), query(mid + 1, r, x << 1 | 1, a, b));
}
int main() {
    R(n), R(m);
    int i, a, b, c, d;
    for (i = 1; i < n; i++) R(ma[i][0]);
    for (i = 1; i < n; i++) R(ma[i][1]);
    for (i = 1; i <= n; i++)R(ma[i][2]);
    build(1, n, 1);
    for (i = 1; i <= m; i++) {
        scanf("%s", ch);
        if (ch[0] == 'C') {
            R(a), R(b), R(c), R(d);
            if (a != c)   R(ma[b][2]), updata(1, n, 1, b);
            else {
                if (b > d)  swap(b, d);
                if (a == 1)    R(ma[b][0]);
                else   R(ma[b][1]);
                updata(1, n, 1, b);
            }
        }
        else {
            R(a), R(b), printf("%d\n", query(1, n, 1, a, b).sum);
        }
    }
    return 0;
}
