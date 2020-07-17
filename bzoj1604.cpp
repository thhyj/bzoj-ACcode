
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<set>
#define inf 10000000000LL
#define ll long long 
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,c,ans,mx;
int fa[100005],tot[100005];
struct data{ll x,y;int id;}a[100005];
multiset <data> b;
set <data>::iterator it;
inline bool operator<(data a,data b)
{
    return a.y<b.y;
}
inline bool cmpx(data a,data b)
{
    return a.x<b.x;
}
int find(int x)
{
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
inline void un(int x,int y)
{
    int p=find(x),q=find(y);
    if(p!=q)
    {
        fa[p]=q;
        ans--;
    }
}
void solve()
{
    b.insert((data){0,inf,0});b.insert((data){0,-inf,0});   
    int now=1;b.insert(a[1]);
    for(int i=2;i<=n;i++)
    {
        while(a[i].x-a[now].x>c)
        {
            b.erase(b.find(a[now]));
            now++;
        }
        it=b.lower_bound(a[i]);
        data r=*it,l=*--it;
        if(a[i].y-l.y<=c)
            un(a[i].id,l.id);
        if(r.y-a[i].y<=c)
            un(a[i].id,r.id);
        b.insert(a[i]);
    }
}
int main()
{
    n=read();c=read();ans=n;
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=n;i++)
    {
        int t1=read(),t2=read();
        a[i].x=t1+t2,a[i].y=t1-t2;a[i].id=i;
    }
    sort(a+1,a+n+1,cmpx);
    solve();
    for(int i=1;i<=n;i++)
        tot[find(i)]++;
    for(int i=1;i<=n;i++)
        mx=max(mx,tot[i]);
    printf("%d %d\n",ans,mx);
    return 0;
}
