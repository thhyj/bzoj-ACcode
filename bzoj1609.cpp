
#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

int n,d[30010],f[30010],cnt;
int x,y,z;

inline void R(int &v) {
    v=0;
    char c=0;
    bool p=true;
    while(c>'9'||c<'0') {
        if(c=='-') {
            p=false;
        }
        c=cin.get();
    }
    while(c<='9'&&c>='0') {
        v=(v<<3)+(v<<1)+c-'0';
        c=cin.get();
    }
    if(p==false) {
        v=-v;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    R(n);
    for(int i=1; i<=n; ++i) {
        R(d[i]);
    }
    int ma=0;
    int mi=0;
    for(int i=n; i>=1; --i) {
        if(d[i]==1) {
            cnt++;
        }
        f[i]=cnt;
    }
    x=0;
    for(int i=n; i>=1; --i) {
        if(d[i]==2) {
            f[i]=max(f[i]+1,x+1);
            if(f[i]>x) {
                x=f[i];
            }
        }
        if(x>f[i]) {
            f[i]=x;
        }
    }
    x=0;
    for(int i=n; i>=1; --i) {
        if(d[i]==3) {
            f[i]=max(f[i]+1,x+1);
            if(f[i]>x) {
                x=f[i];
            }
        }
        if(x>f[i]) {
            f[i]=x;
        }
    }
    ma=n-f[1];
    memset(f,0,sizeof(f));
    cnt=0;
    for(int i=n; i>=1; --i) {
        if(d[i]==3) {
            cnt++;
        }
        f[i]=cnt;
    }
    x=0;
    for(int i=n; i>=1; --i) {
        if(d[i]==2) {
            f[i]=max(f[i]+1,x+1);
            if(f[i]>x) {
                x=f[i];
            }
        }
        if(x>f[i]) {
            f[i]=x;
        }
    }
    x=0;
    for(int i=n; i>=1; --i) {
        if(d[i]==1) {
            f[i]=max(f[i]+1,x+1);
            if(f[i]>x) {
                x=f[i];
            }
        }
        if(x>f[i]) {
            f[i]=x;
        }
    }
    mi=n-f[1];
    cout<<min(ma,mi);
    return 0;
}
