
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <set>
#include <ctime>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <cmath>
#define inf 1000000000
#define pa pair <int, int>
#define ll long long
using namespace std;
inline void R(int &v) {
    static char ch;
    v = 0;
    bool p = 0;
    do {
        ch = getchar();
        if (ch == '-')
            p = 1;
    } while ( !isdigit(ch) );
    while ( isdigit(ch) ) {
        v = ( v << 1 ) + ( v << 3 ) + ( ch ^ '0' );
        ch = getchar();
    }
    if (p)
        v = -v;
}
inline void R(long long &v) {
    static char ch;
    v = 0;
    bool p = 0;
    do {
        ch = getchar();
        if (ch == '-')
            p = 1;
    } while ( !isdigit(ch) );
    while ( isdigit(ch) ) {
        v = ( v << 1 ) + ( v << 3 ) + ( ch ^ '0' );
        ch = getchar();
    }
    if (p)
        v = -v;
}
int s, w, m;
int ans[10005];
int t[2000005];
int cnt9;
int tim[2000005];
struct que {
    int x, y, val, pos, id, kind;
} q[200005], temp[200005];
bool operator < (que a, que b) {
    if (a.x == b.x && a.y == b.y) return a.kind < b.kind;
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}
void add(int x, int val) {
    for (int i = x; i <= w; i += i & - i) t[i] += val;
}
int query(int x) {
    int temp = 0;
    for (int i = x; i; i -= i & - i) temp += t[i];
    return temp;
}
int T;
void update(int x, int y)
{
    for (; x <= w; x += x & -x)
    {
        if (tim[x] != T)
            t[x] = 0;
        tim[x] = T;
        t[x] += y;
    }
}
int getans(int x)
{
    int re = 0;
    for (; x; x -= x & -x)
        if (tim[x] == T)
            re += t[x];
    return re;
}
void mergesort(int l, int r) {
    if (l == r) return;
    int mid = ( l + r ) >> 1, l1 = l, l2 = mid + 1;
    for (int i = l; i <= r; i++)
        if (q[i].id <= mid) temp[l1++] = q[i];
        else temp[l2++] = q[i];
    for (int i = l; i <= r; i++)
        q[i] = temp[i];
    mergesort(l, mid);
    int j = mid + 1, i = l;
    ++T;
    while (j <= r) {
        while (i <= mid && q[i].x <= q[j].x) {
            if (!q[i].kind)
                update(q[i].y, q[i].val);
            i++;
        }
        if (q[j].kind)
            ans[q[j].pos] += q[j].val * getans(q[j].y);
        j++;
    }
    //for (int j = l; j < i; j++) if (!q[j].kind) add(q[j].y, -q[j].val);
    mergesort(mid + 1, r);
    l1 = l, l2 = mid + 1;
    for (int i = l; i <= r; ++i) {
        if (l1 > mid || q[l2] < q[l1] && l2 <= r) temp[i] = q[l2++];
        else temp[i] = q[l1++];
    }
    for (int i = l; i <= r; ++i) q[i] = temp[i];
}
int main() {
    R(s), R(w);
    int kind;
    int x1, y1, x2, y2;
    while (1) {
        R(kind);
        if (kind == 1) {
            R(q[++m].x), R(q[m].y), R(q[m].val);
            q[m].id = m;
        } else if (kind == 2) {
            R(x1), R(y1), R(x2), R(y2);
            int pos = ++cnt9;
            q[++m].pos = pos, q[m].id = m, q[m].x = x1 - 1, q[m].y = y1 - 1, q[m].val = 1, q[m].kind = 1;
            q[++m].pos = pos, q[m].id = m, q[m].x = x2, q[m].y = y2, q[m].val = 1, q[m].kind = 1;
            q[++m].pos = pos, q[m].id = m, q[m].x = x1 - 1, q[m].y = y2, q[m].val = -1, q[m].kind = 1;
            q[++m].pos = pos, q[m].id = m, q[m].x = x2, q[m].y = y1 - 1, q[m].val = -1, q[m].kind = 1;
        } else break;
    }
    sort(q + 1, q + m + 1);
    mergesort(1, m);
    for (int i = 1; i <= cnt9; i++)
        printf("%d\n", ans[i]);
    return 0;
}
