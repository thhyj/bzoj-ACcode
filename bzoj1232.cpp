
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
#define N 100005
#define inf 2100000000

int n,m,x,y,z,Min,ans,cnt;
int val[N],f[N];
struct hp{int x,y,z;}e[N];

int cmp(hp a,hp b)
{
    return a.z<b.z;
}
int find(int x)
{
    if (x==f[x]) return x;
    f[x]=find(f[x]);
    return f[x];
}
int main()
{
    scanf("%d%d",&n,&m);Min=inf;
    for (int i=1;i<=n;++i) scanf("%d",&val[i]),Min=min(Min,val[i]);
    for (int i=1;i<=m;++i)
    {
        scanf("%d%d%d",&x,&y,&z);
        e[i].x=x,e[i].y=y,e[i].z=z*2+val[x]+val[y];
    }
    sort(e+1,e+m+1,cmp);
    for (int i=1;i<=n;++i) f[i]=i;
    for (int i=1;i<=m;++i)
    {
        int f1=find(e[i].x),f2=find(e[i].y);
        if (f1!=f2)
        {
            f[f1]=f2;ans+=e[i].z;
            cnt++;
            if (cnt==n-1) break;
        }
    }
    printf("%d\n",ans+Min);
}
