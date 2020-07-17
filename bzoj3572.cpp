
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define inf 1000000000
using namespace std;

int n,m,tot,dfsclk,bin[25],fst[300005],to[600010],next[600010],fa[300005][19],d[300005],dfn[300005];
int a[300005],p[300005],id[300005],val[300005],anc[300005],len[300005],ans[300005],sz[300005],q[300005];
struct node {
    int x,y;
} g[300005];
inline void R(int &v) {
    v=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c<='9'&&c>='0') {
        v=(v<<3)+(v<<1)+(c^'0');
        c=getchar();
    }
}
void add(int x,int y) {
    to[++tot]=y;
    next[tot]=fst[x];
    fst[x]=tot;
}
void dfs(int x) {
    dfn[x]=++dfsclk;
    sz[x]=1;
    int p,i;
    for (i=1; bin[i]<=x; i++) fa[x][i]=fa[fa[x][i-1]][i-1];
    for (p=fst[x]; p; p=next[p]) {
        int y=to[p];
        if (y!=fa[x][0]) {
            fa[y][0]=x;
            d[y]=d[x]+1;
            dfs(y);
            sz[x]+=sz[y];
        }
    }
}
int lca(int x,int y) {
    if (d[x]<d[y]) swap(x,y);
    int tmp=d[x]-d[y],i;
    for (i=0; bin[i]<=tmp; i++)
        if (tmp&bin[i]) x=fa[x][i];
    for (i=18; i>=0; i--)
        if (fa[x][i]!=fa[y][i]) {
            x=fa[x][i];
            y=fa[y][i];
        }
    return (x==y)?x:fa[x][0];
}
int find(int x,int dep) {
    int i;
    for (i=18; i>=0; i--) if (d[fa[x][i]]>=dep) x=fa[x][i];
    return x;
}
bool cmp(int x,int y) {
    return dfn[x]<dfn[y];
}
bool lss(node u,node v) {
    return u.x<v.x || u.x==v.x && u.y<v.y;
}
void solve() {
    R(m);
    int i,cnt=m,tp=0;
    node t;
    for (i=1; i<=m; i++) {
        R(p[i]);
        a[i]=p[i];
        id[i]=p[i];
        g[a[i]].y=a[i];
        g[a[i]].x=ans[a[i]]=0;
    }
    sort(a+1,a+m+1,cmp);
    for (i=1; i<=m; i++)
        if (!tp) {
            q[++tp]=a[i];
            anc[a[i]]=0;
        } else {
            int tmp=lca(a[i],q[tp]);
            for (; d[q[tp]]>d[tmp]; tp--)
                if (d[q[tp-1]]<=d[tmp]) anc[q[tp]]=tmp;
            if (q[tp]!=tmp) {
                p[++cnt]=tmp;
                anc[tmp]=q[tp];
                q[++tp]=tmp;
                g[tmp].x=inf;
                g[tmp].y=0;
            }
            anc[a[i]]=tmp;
            q[++tp]=a[i];
        }
    sort(p+1,p+cnt+1,cmp);
    for (i=1; i<=cnt; i++) {
        int x=p[i];
        val[x]=sz[x];
        if (i>1) len[x]=d[x]-d[anc[x]];
    }
    for (i=cnt; i>1; i--) {
        int x=p[i];
        t=g[x];
        t.x+=len[x];
        if (lss(t,g[anc[x]])) g[anc[x]]=t;
    }
    for (i=2; i<=cnt; i++) {
        int x=p[i];
        t=g[anc[x]];
        t.x+=len[x];
        if (lss(t,g[x])) g[x]=t;
    }
    for (i=1; i<=cnt; i++) {
        int x=p[i],y=anc[x];
        if (i==1) ans[g[x].y]+=n-sz[x];
        else {
            int tmp=find(x,d[y]+1),sum=sz[tmp]-sz[x];
            val[y]-=sz[tmp];
            if (g[x].y==g[y].y) ans[g[x].y]+=sum;
            else {
                int z=d[x]-((g[y].x+len[x]-g[x].x)>>1);
                if (!((g[y].x+g[x].x+len[x])&1) && g[x].y>g[y].y) z++;
                z=sz[find(x,z)]-sz[x];
                ans[g[x].y]+=z;
                ans[g[y].y]+=sum-z;
            }
        }
    }
    for (i=1; i<=cnt; i++) ans[g[p[i]].y]+=val[p[i]];
    for (i=1; i<=m; i++) printf("%d ",ans[id[i]]);
    puts("");
}
int main() {
    R(n);
    int i;
    bin[0]=1;
    for (i=1; i<=19; i++) bin[i]=bin[i-1]<<1;
    int x,y;
    for (i=1; i<n; i++) {
        R(x);
        R(y);
        add(x,y);
        add(y,x);
    }
    d[1]=1;
    dfs(1);
    int cas;
    R(cas);
    while (cas--) solve();
    return 0;
}
