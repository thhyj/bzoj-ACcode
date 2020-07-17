
#include <bits/stdc++.h>
using namespace std;
inline void R (long long &v) {
    static char ch;
    v = 0;
    bool p = 0;
    do {
        ch=getchar();
        if(ch=='-') p = 1;
    } while(!isdigit(ch));
    while(isdigit(ch)) {
        v=(v+(v<<2)<<1)+(ch^'0');
        ch=getchar();
    }
    if(p) v = -v;
}
long long sum[50005], a[50005];
long long L;
struct data {
    long long l, r, pos;
    data(long long l, long long r, long long pos) : l(l), r(r), pos(pos) {}
    data() {}
} q[50005];
long long f[50005];
long long head, tail;
inline long long cal(long long l, long long r) {
    return f[l] + (r - l -1 + sum[r] - sum[l] - L) * (r - l -1 + sum[r] - sum[l] - L);
}
inline long long find(data p, long long x) {
    long long l = p.l, r = p.r+1, mid;
    while(l<r-1) {
        mid = l+r>>1;
        if(cal(p.pos, mid) > cal(x, mid)) r = mid;
        else l = mid;
    }
    //cout<<"l="<<l<<" r="<<r<<'\n';
    return r;
}
int main () {
    long long n;
    R(n), R(L);
    for(long long i = 1; i <= n; ++i) {
        R(a[i]);
        sum[i] = sum[i-1] + a[i];
    }
    head = 1, tail = 0;
    q[++tail] = data(0, n, 0);
    for(long long i = 1 ; i <= n; ++i) {
        if(q[head].r < i) ++head;
        f[i] = cal(q[head].pos, i);
        if(head>tail||cal(i,n)<cal(q[tail].pos,n)){
        while(tail >= head && cal(i, q[tail].l) < cal(q[tail].pos, q[tail].l)) --tail;
        if(head<=tail) {
           // cout<<"tail="<<tail<<" q[tail].l="<<q[tail].l<<" q[tail].r="<<q[tail].r<<'\n';
            long long pos = find(q[tail], i);
            q[tail].r = pos - 1;
            q[++tail] = data(pos, n, i);
        } else q[++tail] = data(i, n, i);}
    }
    cout<<f[n]<<'\n';
    return 0;
}
