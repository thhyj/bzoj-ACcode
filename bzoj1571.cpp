
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
struct class1 {
    int beg;
    int en;
    int ab;
} huaxue[10001];
struct place {
    int need;
    int time;
} pla[100001];
int shangke[100001];
int dp[10001][101];
int need[10001];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T, S, N, mi;
    memset(need, 15, sizeof(need));
    memset(dp, 128, sizeof(dp));
    cin >> T >> S >> N;
    for (int i = 1; i <= S; i++) {
        cin >> huaxue[i].beg >> huaxue[i].en >> huaxue[i].ab;
        shangke[huaxue[i].beg] = 1;
    }
    for (int i = 1; i <= N; i++) {
        cin >> pla[i].need >> pla[i].time;
        if (pla[i].time < need[pla[i].need])
            need[pla[i].need] = pla[i].time;
    }
    mi = need[0];

    for (int i = 1; i <= 100; i++) {
        if (need[i] >= mi)
            need[i] = mi;
        if (need[i] < mi)
            mi = need[i];
    }

    dp[0][1] = 0;
    for (int i = 0; i <= T; i++) {
        for (int j = 1; j <= 100; j++) {
            if (dp[i][j] >= 0) {
                if (dp[i + 1][j] < dp[i][j]) {
                    dp[i + 1][j] = dp[i][j];
                }
                if ((i + need[j] <= T) && (dp[i + need[j]][j] < dp[i][j] + 1)) {
                    dp[i + need[j]][j] = dp[i][j] + 1;
                }
                if (shangke[i] != 0) {
                    for (int k = 1; k <= S; k++) {
                        if (huaxue[k].beg == i)
                            if (dp[huaxue[k].en + i][huaxue[k].ab] < dp[i][j] && huaxue[k].ab > j)
                            {
                                dp[huaxue[k].en + i][huaxue[k].ab] = dp[i][j];
                            }
                    }
                }
            }
        }
    }
    int ma = 0;
    {
        for (int i = 1; i <= 100; i++) {
            if (dp[T][i] > ma)
                ma = dp[T][i];
        }
    }
    cout << ma;
    return 0;
}
