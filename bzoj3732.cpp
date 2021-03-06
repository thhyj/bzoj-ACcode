
#include<bits/stdc++.h>
using namespace std;

const int N=200500;
int n,m;
struct node
{
    int x,y,c,no;
}E[N<<1];
int pre[N],to[N<<1],w[N<<1],nxt[N<<1],k;
int fa[N],lca[N][22],p[N][22],dep[N],cnt;

void makeedge(int x,int y,int c)
{
    to[cnt]=x;w[cnt]=c;nxt[cnt]=pre[y];pre[y]=cnt++;
    to[cnt]=y;w[cnt]=c;nxt[cnt]=pre[x];pre[x]=cnt++;
}
int getfather(int x)
{
    if(fa[x]==x) return fa[x];else return fa[x]=getfather(fa[x]);
}
void dfs(int x)
{
    for(int it=pre[x];~it;it=nxt[it])
    {
        int y=to[it],c=w[it];
        if(y==lca[x][0]) continue;
        dep[y]=dep[x]+1,lca[y][0]=x,p[y][0]=c;
        dfs(y);
    }
}
int query(int x,int y)
{
    int ret=0;
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=21;i>=0;i--)
        if(dep[x]-(1<<i)>=dep[y])
            ret=max(ret,p[x][i]),x=lca[x][i];
    if(x==y) return ret;
    for(int i=21;i>=0;i--)
        if(lca[x][i]!=lca[y][i])
            ret=max(ret,max(p[x][i],p[y][i])),x=lca[x][i],y=lca[y][i];
    ret=max(ret,max(p[y][0],p[x][0]));
    return ret;
}
bool cmp(node t1,node t2)
{
    return t1.c<t2.c;
}

int main()
{
    scanf("%d%d%d",&n,&m,&k);
    memset(pre,-1,sizeof(pre));
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&E[i].x,&E[i].y,&E[i].c);
        E[i].no=i;
    }
    sort(E+1,E+m+1,cmp);
    long long tot=0;
    for(int i=1;i<=m;i++)
    {
        int x=E[i].x,y=E[i].y;
        int f1=getfather(x),f2=getfather(y);
        if(f1!=f2)
        {
            fa[f2]=f1;
            tot+=(long long)E[i].c;
            makeedge(x,y,E[i].c);
        }
    }
    dfs(1);
    for(int j=1;j<=21;j++)
        for(int i=1;i<=n;i++)
            if(lca[i][j-1])
            {
                lca[i][j]=lca[lca[i][j-1]][j-1];
                p[i][j]=max(p[i][j-1],p[lca[i][j-1]][j-1]);
            }
    for(int i=1;i<=k;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",query(x,y));
    }
}
