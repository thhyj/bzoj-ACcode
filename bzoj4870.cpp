
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
struct matrix {
    long long x[50][50];
    matrix() {
        memset(x, 0, sizeof(x));
    }
};
long long n;
int p, K, r1;
matrix c, x, r;
matrix operator *(const matrix &x, const matrix &y) {
    int i, j, k;
    matrix z;
    int temp;
    for (i = 0; i < K; i++) {
        for (k = 0; k < K; k++) {
            temp = x.x[i][k];
            for (j = 0; j < K; j++) {
                (z.x[i][j] += temp * y.x[k][j]) %= p;
            }
        }
    }
    return z;
}
int main() {
    int i;
    R(n), R(p), R(K), R(r1);
    c.x[0][0] = 1;
    for (i = 0; i < K; i++) {
        x.x[(i - 1 + K) % K][i]++;
        x.x[i][i]++;
        r.x[i][i] = 1;
    }
    n *= K;
    while (n) {
        if (n & 1) {
            r = r * x;
        }
        x = x * x;
        n >>= 1;
    }
    cout << (c * r).x[0][r1];
    return 0;
}
