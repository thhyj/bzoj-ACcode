
#include<iostream>
#include<cstring>
#include<cmath>
#include<ctime>
#include<algorithm>
#include<cstdio>
#include<cctype>
#include<queue>
using namespace std;
const int INF=2000000000;
inline void R(int &v)
{
    static char ch;
    v=0;
    bool p=0;
    do{
        ch=getchar();
        if(ch=='-')
        p=1;
    }while(!isdigit(ch));
    while(isdigit(ch))
    {
        v=(v<<1)+(v<<3)+(ch^'0');
        ch=getchar();
    }
    if(p)
    v=-v;
}
int first[20005],nxt[500005],to[500005],length[500005],tot,temp[20005],dis[20005];
inline void create(int x,int y,int z)
{
    nxt[tot]=first[x];
    first[x]=tot;
    to[tot]=y;
    length[tot]=z;
    ++tot;
}
inline bool bfs(const int &s,const int &t)
{
    queue<int>q;
    memset(dis,-1,sizeof(dis));
    dis[s]=0;
    q.push(s);
    int j,p;
    while(!q.empty())
    {
        j=q.front();
        q.pop();
        for(p=first[j];~p;p=nxt[p])
        {
            if(length[p]&&dis[to[p]]==-1)
            {
                dis[to[p]]=dis[j]+1;
                q.push(to[p]);
                if(to[p]==t)return 1;
            }
        }
    }
    return 0;
}
int cnt[10001];
int dfs(const int  &x,const int &flow,const int &t )
{
    if(x==t)
    return flow;
    int res=0,f;
    for(int &p=temp[x];~p;p=nxt[p])
    {
        if(dis[to[p]]>dis[x]&&length[p])
        {
            f=dfs(to[p],min(length[p],flow-res),t);
            if(f)
            {
                length[p]-=f;
                length[p^1]+=f;
                res+=f;
                if(res==flow)break;
            }
        }
    }
    if(res<flow)dis[x]=-1;
    return res;
}
int a[10005],zhu[10005];
int main()
{
    int sum=0;
    int n,m;
    register int x,y,z,i;
    memset(first,-1,sizeof(first));
	R(m);
	R(n);
    int s=0,t=(n<<1)+1;
    for(int i=1;i<=m;++i)
    {
        R(a[i]);
    }
    for(int i=1;i<=n;++i)
    {
        R(x);
        for(int j=1;j<=x;++j)
        {
            R(y);
            if(!zhu[y])
            {
                create(s,i,a[y]);
                create(i,s,0);
                zhu[y]=i;
            }
            else
            {
                create(zhu[y],i,INF);
                create(i,zhu[y],0);
                zhu[y]=i;
            }
        }
        R(z);
        create(i,t,z);
        create(t,i,0);
    }
    int ans=0;
    while(bfs(s,t))
    {
        memcpy(temp, first, (2 * n + 5 << 2));
        ans+=dfs(s,INF,t);
    }
    cout<<ans;
    return 0;
}
