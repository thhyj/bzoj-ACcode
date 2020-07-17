
#include <bits/stdc++.h>
using namespace std;
inline void R(int &v) {
    static char ch;
    v=0;
    bool p=0;
    do {
        ch=getchar();
        if(ch=='-') {
            p=1;
        }
    } while(!isdigit(ch));
    while(isdigit(ch)) {
        v=(v+(v<<2)<<1)+(ch^'0');
        ch=getchar();
    }
    if(p) v=-v;
}
    int n;
struct po {
    double x,y;
}zb[10005],daan,st;
double w[10005];
double minans=1e100;
inline double dis(const po &x, const po &y) {
    return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));
}
inline double getrand() {
    return rand()%10000/10000.0;
}
inline double calc(const po &now) {
    double ret=0.0;
    for(int i=1;i<=n;++i) {
        ret+=dis(zb[i],now)*w[i];
    }
//  cout<<"ret="<<ret<<'\n';
    if(ret<minans) {
    //  cout<<"ret="<<ret<<" minans="<<minans<<" now.x="<<now.x<<" now.y="<<now.y<<'\n';
        daan=now,minans=ret;
    }
    return ret;
}
inline void sa() {
    po now=daan;
    double ans=0;
    double T=1000000.0;
    po nxt;
    double temp;
    double de;
    while(T>0.001) {
        //nxt=now;
        nxt.x=now.x+T*sin(rand());  
        nxt.y=now.y+T*sin(rand());  
        de=calc(now)-calc(nxt);
        if(de>0||exp(de/T)>getrand()) {
            now=nxt;
        }
        T*=0.991;
    }
//  printf("%0.3f %0.3f\n",daan.x,daan.y);
    for (int i=1;i<=1000;i++){  
        po newp;  
        newp.x=daan.x+T*sin(rand());  
        newp.y=daan.y+T*sin(rand());  
        calc(newp);  
    }  
}
int main () {
    srand(233);
    R(n);
    int x,y,z;
    for(int i=1;i<=n;++i) {
        R(x), R(y), R(z);
        zb[i].x=x,zb[i].y=y,w[i]=z;
        st.x+=zb[i].x,st.y+=zb[i].y;
    }
    st.x/=(double)n,st.y/=(double)n;
    daan=st;
    minans=1e100;
//  cout<<"minans="<<minans<<'n';
    //printf("%0.3f %0.3f\n",st.x,st.y);
    sa();
    printf("%0.3f %0.3f",daan.x,daan.y);
}
