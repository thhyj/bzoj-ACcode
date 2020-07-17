
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
inline void R(char &ch) {
    do {
        ch = getchar();
    } while (!isupper(ch));
}
int n, m;
char ma[1005][1005];
int sum[1005], st[1005], cnt[1005], top;
int main( ) {
   // freopen("jademoon.in", "r", stdin);
   //   freopen("jademoon.out", "w", stdout);
    R(n), R(m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            R(ma[i][j]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (ma[i][j] == 'R') break;
            ++sum[i];
        }
    }
    int ans = 0;
    int mi = 100000000;

    for (int i = 1; i <= m; ++i) {
        //      for (int j = 1; j <= n; ++j) printf("sum[%d] = %d\n", j, sum[j]);
        for (int j = 1; j <= n; ++j) {
            //  printf("ma[%d][%d]=%c\n", j, i, ma[j][i]);
            if (ma[j][i - 1] == 'R' || (!ma[j][i - 1])) {
                sum[j] = 0;
                for (int k = i; k <= m; ++k) {
                    if (ma[j][k] == 'R') break;
                    ++sum[j];
                }
            } else sum[j]--;
        }
        for (int j = 1; j <= n; ++j) {
            if (st[top] < sum[j]) {
                st[++top] = sum[j];
                cnt[top] = j;
            } else {
                mi = j;
                while (top && st[top] > sum[j]) {
                    //printf("st[%d] = %d, cnt[%d] = %d \n", top, st[top], top, cnt[top]);
                    ans = max(ans, (j - cnt[top]) * st[top]);
                    mi = min(mi, cnt[top]);
                    --top;
                }
                st[++top] = sum[j];
                cnt[top] = mi;
            }

        }
        while (top) {
            //  printf("st[%d] = %d, cnt[%d] = %d \n", top, st[top], top, cnt[top]);
            ans = max(ans, (n + 1 - cnt[top]) * st[top]);
            //  printf("ans=%d\n", ans);
            --top;
        }
    }
    printf("%d", ans * 3);
    return 0;
}


