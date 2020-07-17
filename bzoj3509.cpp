
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
struct E {
    double r, i;
    E(double r, double i): r(r), i(i) {}
    E() {}
};
inline E operator +(const E &a, const E&b) {
    return E(a.r + b.r, a.i + b.i);
}
inline E operator - (const E &a, const E &b) {
    return E(a.r - b.r, a.i - b.i);
}
inline E operator * (const  E &a, const E &b) {
    return E(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
}
int n;
int a[100005];
E a1[40004<<1], a2[40004<<1];
int rev[40004<<1];
const int L = 16;
const int len = 1 << L;
const int sz = 4000;
const double pi=acos(-1);
inline void fft(E *a, const int &f) {
    for(int i=0;i<len;++i) {
        if(i<rev[i]) {
    //  if(i>=59000)
    //  printf("i=%d ,rev[i]=%d\n",i,rev[i]);
        swap(a[i],a[rev[i]]);
        }
    }
    for(int i=1;i<len;i<<=1) {
        E wn=E(cos(pi/i),f*sin(pi/i));
        for(int j=0;j<len;j+=i<<1) {
            E w=E(1,0);
            for(int k=0;k<i;++k,w=w*wn) {
                E x=a[j+k],y=a[j+k+i]*w;
                a[j+k]=x+y;
                a[j+k+i]=x-y;
            }
        }
    }
}
int main () {
//  freopen("in.in","r",stdin);
//  freopen("out.out","w",stdout);
    R(n);
    for (int i = 1; i <= n; ++i) {
        R(a[i]);
    }
//  cout<<"len="<<len<<'\n';
    for(int i=0;i<len;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
//  for(int i=59999;i<=60100;++i) cout<<"i="<<i<<" rev[i]="<<rev[i]<<'\n';
    long long ans=0;
    for (int i = sz+1; i+sz <= n; i += sz) {
         memset(a1,0,sizeof(a1));   
        memset(a2,0,sizeof(a2));
        for (int j = 1; j < i; ++j) a1[a[j]] =a1[a[j]] + E(1, 0);
        for (int j = i + sz; j <= n; ++j) a2[a[j]] = a2[a[j]] + E(1, 0);
        fft(a1,1),fft(a2,1);
        for(int j=0;j<len;++j)a1[j]=a1[j]*a2[j];
        fft(a1,-1);
        for(int j=i;j<i+sz;++j) ans+=(long long)(a1[a[j]<<1].r/len+0.5);
    }
//  cout<<"ans="<<ans<<'\n';
    int ed=0;
    int temp;
    int tot[70004];
    memset(tot,0,sizeof(tot));
    for(int i=1;i<=n;i+=sz) {
        ed=i;
        for(int j=i;j<min(i+sz,n+1);++j) {
            for(int k=j+1;k<min(i+sz,n+1);++k) {
                temp=(a[j]<<1)-a[k];
                if(temp<=70000&&temp>0) {
                    ans+=tot[temp];
                }
            }
            tot[a[j]]++;
        }
    }
    //cout<<"ans="<<ans<<" ed="<<ed<<'\n';
    memset(tot,0,sizeof(tot));
    for(int i=ed;i>0;i-=sz) {
        for(int j=min(i+sz-1,n);j>=i;--j) {
            for(int k=j-1;k>=i;--k) {
                //cout<<"k="<<k<<" j="<<j<<'\n';;
                temp=(a[j]<<1)-a[k];
                if(temp<=70000&&temp>0) {
                    ans+=tot[temp];
                }
            }
        }
        for(int j=min(i+sz-1,n);j>=i;--j)tot[a[j]]++;
    }
    cout<<ans;
    return 0;
}
