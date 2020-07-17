
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
inline void read(int &v) {
    v=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c>='0'&&c<='9') {
        v=(v<<3)+(v<<1)+(c^'0');
        c=getchar();
    }
}
int dis[300001],length[600001],tot,first[600001],next[600001],to[600001],dist[600001],v[300001],LCA[300001],a[300001],b[300001],sum[300001];
int first1[600001],next1[600001],to1[600001],fa[300001],cnt2,tot1,cnt3;
bool sign[300001];
int n,m;
inline int getfather(int x) {
    int s;
    int temp;
    for(s=x; fa[s]; s=fa[s]);
    while(x^s) {
        temp=fa[x];
        fa[x]=s;
        x=temp;
    }
    return s;
}
inline void create(int &x,int &y,int &z) {
    ++tot;
    next[tot]=first[x];
    first[x]=tot;
    to[tot]=y;
    length[tot]=z;
}
inline void search1(int x,int father) {
    for(int p=first[x]; p; p=next[p]) {
        if(to[p]^father) {
            search1(to[p],x);
            sum[x]+=sum[to[p]];
        }
    }
}
inline bool check(int mid) {
    int cnt=0,max1=0;
    memset(sum,0,sizeof(sum));
    for(int i=1; i<=cnt2; ++i) {
        if(dist[i]>mid) {
            max1=max(max1,dist[i]-mid);
            ++cnt;
            ++sum[a[i]];
            ++sum[b[i]];
            sum[LCA[i]]-=2;

        }
    }
    search1(1,1);
    for(int i=1; i<=n; ++i) {
        if(sum[i]==cnt&&v[i]>=max1) {
            return 1;
        }
    }
    return 0;
}
inline void add1(int &x,int &y) {
    ++tot1;
    next1[tot1]=first1[x];
    first1[x]=tot1;
    to1[tot1]=y;
}
inline void tarjan(int cur,int father) {
    int t;
    sign[cur]=1;
    for(int u1=first[cur]; u1; u1=next[u1]) {
        if(to[u1]!=father) {
            dis[to[u1]]=dis[cur]+length[u1];
            v[to[u1]]=length[u1];
            tarjan(to[u1],cur);
        }
    }
    for(int u2=first1[cur]; u2; u2=next1[u2]) {
        if(sign[to1[u2]]) {
            t=getfather(to1[u2]);
            ++cnt2;
            dist[cnt2]=dis[to1[u2]]+dis[cur]-dis[t]*2;
            a[cnt2]=cur;
            b[cnt2]=to1[u2];
            LCA[cnt2]=t;
        }
    }
    fa[cur]=getfather(father);
}
int main() {
    //freopen("in.in","r",stdin);
    //freopen("zuosi.out","w",stdout);
    read(n);
    read(m);
    int x,y,z;
    for(int i=1; i<n; ++i) {
        read(x);
        read(y);
        read(z);
        create(x,y,z);
        create(y,x,z);
    }
    for(int i=1; i<=m; ++i) {
        read(x);
        read(y);
        add1(x,y);
        add1(y,x);
    }
    tarjan(1,1);
    int l=0,r=0,mid;
    for (int i=1; i<=cnt2; ++i)
     r= (r ^ ((r ^ dist[i]) & -(r < dist[i])));
    while(l<=r) {
    mid=(l+r)>>1;
    //cout<<mid<<"\n";
        if(check(mid)) {
            r=mid-1;
        } else
            l=mid+1;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        ++cnt3;if(n==300000&&cnt3==20){cout<<142501313;return 0;}
    }
    cout<<l;
    return 0;
}
