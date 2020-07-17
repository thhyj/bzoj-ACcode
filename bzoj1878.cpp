
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
        ch = getchar();
    }
    if (p) v = -v;
}
int a[1000005], pre[1000005], sum[1000005], shang[1000005];
#define lowbit(x) (x&-x)
int n, c, m;
int ans[1000005];
struct que {
    int l, r, ori;
} q[1000005];
inline bool cmp(const que &a, const que &b) {
    return a.r < b.r || (a.r == b.r && a.l < b.l);
}
inline void add(int x) {
    for (; x <= n; x += lowbit(x)) {
        sum[x]++;
    }
}
inline void mi(int x) {
    for (; x <= n; x += lowbit(x)) {
        sum[x]--;
    }
}
inline int query(int x) {
    int ret = 0 ;
    for (; x ; x -= lowbit(x)) {
        ret += sum[x];
    }
    return ret;
}
int main() {
    R(n);
    for (int i = 1; i <= n; ++i) {
        R(a[i]);
        if (shang[a[i]]) {
            pre[i] = shang[a[i]];
        }
        shang[a[i]] = i;
    }
    //for (int i = 1; i <= n; ++i)
    //{
    //  printf("pre[%d] = %d\n", i, pre[i]);
//      /* code */
//  }
    R(m);
    for (int i = 1; i <= m; ++i) {
        R(q[i].l), R(q[i].r);
        q[i].ori = i;
    }
    sort(q + 1, q + m + 1, cmp);
    int now = 0;
    for (int i = 1; i <= m; ++i) {
        while (now < q[i].r) {
            ++now;
            add(now);
            if (pre[now]) {
                mi(pre[now]);
            }
        }
        ans[q[i].ori] = query(q[i].r) - query(q[i].l - 1);
    }
    for (int i = 1; i <= m; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
