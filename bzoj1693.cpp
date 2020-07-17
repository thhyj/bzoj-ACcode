
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
int first[2005],nxt[40005],to[40005],length[40005],tot,temp[2005],dis[2005];
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
int main()
{
    memset(first,-1,sizeof(first));
    int n,m,s,t;
    R(n);
    R(m);
    s=0,t=2*n+1;
    int x,y,z;
    for(int i=1;i<=n;++i)
    {
        create(s,i,1);
        create(i,s,0);
    }
    for(int i=n+1;i<=2*n;++i)
    {
        create(i,t,1);
        create(t,i,0);
    }
    for(int i=1;i<=m;++i)
    {
        R(x);R(y);
        create(x,y+n,1);
        create(y+n,x,0);
    }
    int ans=0;
    while(bfs(s,t))
    {
        for(int i=0;i<=2*n+1;++i)
            temp[i]=first[i];
        ans+=dfs(s,INF,t);
    //    cout<<"ans="<<ans<<'\n';
    }
    cout<<ans<<'\n';
    return 0;
}
