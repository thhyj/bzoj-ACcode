
#include<bits/stdc++.h>
using namespace std;
inline void R(int &v) {
    static char ch;
    v=0;
    bool p=0;
    do {
        ch=getchar();
        if(ch=='-') p=1;
    } while(!isdigit(ch));
    while(isdigit(ch)) {
        v=(v+(v<<2)<<1)+(ch^'0');
        ch=getchar();
    }
    if(p) v=-v;
}
struct node {
    int x,y;
    node (int x, int y):x(x),y(y){}
    node (){}
}a[10005],q[10005];
inline node operator -(const node &a, const node &b) {
    return node (a.x-b.x, a.y-b.y);
}
inline double  operator *(const node &a, const node &b) {
    return a.x*b.y-a.y*b.x;
}
inline double dis(const node &a ,const node &b) {
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
inline bool  operator <(const node &a, const node &b) {
    return a.x<b.x||(a.x==b.x&&a.y<b.y);
}
int tot;
    int n;
inline void gao() {
	    sort(a+1,a+n+1);
    for(int i=1;i<=n;++i) {
        while(tot>1&&((q[tot-1]-q[tot-2])*(a[i]-q[tot-2])<=0))--tot;
        q[tot++]=a[i];
    }
    int k=tot;
    for(int i=n-1;i;--i) {
        while(tot>k&&((q[tot-1]-q[tot-2])*(a[i]-q[tot-2])<=0))--tot;
        q[tot++]=a[i];
    }
    if(n>1)--tot;
}
int main () {

    R(n);
    for(int i=1;i<=n;++i) {
        R(a[i].x),R(a[i].y);
    }
    gao();
    q[++tot]=q[1];
    double ans=0;
    for(int i=1;i<tot;++i) {
    //	printf("i=%d,q[i].x=%d,q[i].y=%d\n",i,q[i].x,q[i].y);
        ans+=dis(q[i],q[i+1]);
      //  cout<<"ans="<<ans<<'\n';
    }
    printf("%0.2lf",ans);
}
