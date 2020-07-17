
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
const int N = 54; int n, f[N][N][2];
char s[N];
inline bool check(const int &i, const int &j, const int &k) {
        for (int l = 0; l < k; ++l)
                if (s[i + l] != s[j + l])
                        return false;
        return true;
}
int main() {
        scanf("%s", s);
        n = strlen(s);
        memset(f, 127 / 3, sizeof(f));
        for (int i = 0; i < n; ++i) f[i][i][0] = f[i][i][1] = 1;
        for (int l = 0; l < n; ++l)
                for (int i = 0; i < n; ++i) {
                        int j = i + l;
                        if (j > n) break;
                        f[i][j][0]=min(f[i][j][0],l+1);
                        f[i][j][1]=min(f[i][j][1],l+1);
                        for (int k = i; k < j; ++k) {
                                f[i][j][0]=min(f[i][j][0],f[i][k][0] + j - k);
                                f[i][j][1]=min(f[i][j][1],f[i][k][1] + j - k);
                                f[i][j][1]=min(f[i][j][1], f[i][k][1] + f[k + 1][j][1] + 1);
                        }
                        if (l & 1) {
                                int k = i + j >> 1, t = l + 1 >> 1;
                                if (check(i, k + 1, t))
                                {
                                        f[i][j][1]=min(f[i][j][1], f[i][k][0] + 1);
                                        f[i][j][0]=min(f[i][j][0], f[i][k][0] + 1);
                                }
                        }
                }
        cout<<min(f[0][n-1][0],f[0][n-1][1]);
        return 0;
}
