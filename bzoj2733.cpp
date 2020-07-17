
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
struct tree {
    int ls, rs, sum;
} tr[2000005];
char ch[2];
int n, m, q, tot, f[100005], root[100005], v[100005], id[100005];
inline void update(int x) {
    tr[x].sum = tr[tr[x].ls].sum + tr[tr[x].rs].sum;
}
int getfa(int x) {
    return f[x] != x ? f[x] = getfa(f[x]) : x;
}
void insert(int &x, int l, int r, int v) {
    x = ++tot;
    if (l == r) {
        tr[x].sum = 1;
        return;
    }
    int mid = (l + r) >> 1;
    if (v <= mid) insert(tr[x].ls, l, mid, v);
    else insert(tr[x].rs, mid + 1, r, v);
    update(x);
}
int merge(int x, int y) {
    if (!x) return y;
    if (!y) return x;
    tr[x].ls = merge(tr[x].ls, tr[y].ls);
    tr[x].rs = merge(tr[x].rs, tr[y].rs);
    update(x);
    return x;
}
int query(int x, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (tr[tr[x].ls].sum >= k) return query(tr[x].ls, l, mid, k);
    else return query(tr[x].rs, mid + 1, r, k - tr[tr[x].ls].sum);
}
int main() {
    R(n), R(m);
    for (int i = 1; i <= n; i++) f[i] = i;
    for (int i = 1; i <= n; i++) R(v[i]);
    for (int p, i = 1; i <= n; i++) insert(root[i], 1, n, v[i]), id[v[i]] = i;
    for (int x, y, i = 1; i <= m; i++) {
        R(x), R(y);
        x = getfa(x), y = getfa(y);
        f[y] = x;
        root[x] = merge(root[x], root[y]);
    }
    R(q);
    for (int x, y, i = 1; i <= q; i++) {
        scanf("%s", ch);
        R(x), R(y);
        if (ch[0] == 'Q') {
            x = getfa(x);
            if (tr[root[x]].sum < y) {
                puts("-1");
                continue;
            }
            else printf("%d\n", id[query(root[x], 1, n, y)]);
        } else {
            x = getfa(x); y = getfa(y);
            if (x ^ y) f[y] = x, root[x] = merge(root[x], root[y]);
        }
    }
    return 0;
}
