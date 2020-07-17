
#include <bits/stdc++.h>
using namespace std;
inline void R(int &v) {
    v=0;
    static char ch;
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
    int x, y;
    node (int x, int y):x(x),y(y) {}
    node() {}
} a[200005], del[100005];
set<node>q;
double now;
inline double dis(const node &a, const node &b) {
    return sqrt((double)(a.x-b.x)*(double)(a.x-b.x)+(double)(a.y-b.y)*(double)(a.y-b.y));
}
inline node operator - (const node &a, const node &b) {
    return node(a.x-b.x, a.y-b.y);
}
inline double operator * (const node &a, const node &b) {
    return a.x*b.y-a.y*b.x;
}
inline bool operator< (const node &a, const node &b) {
    return a.x<b.x||(a.x==b.x&&a.y<b.y);
}
int cnt;
bool des[200005];
bool que[200005];
inline void insert(const node &x) {
//	cerr<<233<<'\n';
    set<node>::iterator r=q.lower_bound(x),l=r,t;
    --l;
    if((*r-*l)*(x-*l)<0) return;
    now-=dis(*l,*r);
    while(1) {
        t=r++;
        if(r==q.end())break;
        if((*r-x)*(*t-x)>0) break;
      //  cerr<<"t.x="<<(*t).x<<" t.y="<<(*t).y<<" r.x="<<(*r).x<<" r.y="<<(*r).y<<'\n';
        now-=dis(*t,*r);
        q.erase(t);
    }
    while(l!=q.begin()) {
        t=l--;
         //cerr<<"t.x="<<(*t).x<<" t.y="<<(*t).y<<" l.x="<<(*l).x<<" l.y="<<(*l).y<<'\n';
        if((*t-x)*(*l-x)>0) break;
        //cerr<<"t.x="<<(*t).x<<" t.y="<<(*t).y<<" l.x="<<(*l).x<<" l.y="<<(*l).y<<'\n';
        now-=dis(*l, *t);
        q.erase(t);
    }
    q.insert(x);
    l=r=t=q.find(x);
    --l;++r;
    now+=dis(*l,x)+dis(*r,x);
}
double ans[200005];
int tot;
int main() {
    int n, x, y;
    R(n),R(x),R(y);
    q.insert(node(0,0));
    q.insert(node(n,0));
    q.insert(node(x,y));
    int m;
    R(m);
    for(int i=1; i<=m; ++i) {
        R(a[i].x),R(a[i].y);
    }
    now+=dis(node(0,0),node(x,y))+dis(node(x,y),node(n,0));
    int q;
    R(q);
    int kind;
    for(int i=1; i<=q; ++i) {
        R(kind);
        if(kind==1) {
            R(x);
            del[++cnt]=a[x];
            des[x]=1;
        } else {
            que[++cnt]=1;
        }
    }
    for(int i=1;i<=m;++i) {
    	if(!des[i]) {
    		insert(a[i]);
		}
	}
    for(int i=q; i; --i) {
        if(que[i]) {
            ans[++tot]=now;
        } else {
        //	cerr<<"i="<< " del[i].x="<<del[i].x<<" del[i].y="<<del[i].y<<'\n';
            insert(del[i]);
        }
    }
    for(int i=tot;i;--i)printf("%0.2lf\n",ans[i]);
    return 0;
}
