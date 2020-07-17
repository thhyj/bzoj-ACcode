
#include<iostream>
#include<cstring>
#include<cmath>
#include<ctime>
#include<algorithm>
#include<cstdio>
#include<cctype>
#include<queue>
using namespace std;
const int INF=2147483647;
inline void R(int &v)
{
    static char ch;
    v=0;
    do{
        ch=getchar();
    }while(!isdigit(ch));
    while(isdigit(ch))
    {
        v=(v<<1)+(v<<3)+(ch^'0');
        ch=getchar();
    }
}
int first[1000005],nxt[10000005],to[10000000],length[10000005],tot,temp[1000005],dis[1000005];
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
    static int st[1000005],top,tail;
    top=tail=0;
    memset(dis,-1,sizeof(dis));
    dis[s]=0;
    st[top++]=s;
    register int j,p;
    while(tail<top)
    {
        //cout<<"top="<<top<<" tail="<<tail<<'\n';
        j=st[tail++];
        for(p=first[j];~p;p=nxt[p])
        {
            if(length[p]&&dis[to[p]]==-1)
            {
                dis[to[p]]=dis[j]+1;
                st[top++]=to[p];
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
    register int i;
    R(n);R(m);
    int x,y,z;
    for(int i=1;i<=n;++i)
        for(int j=1;j<m;++j)
        {
            R(z);
        //  cout<<"(i-1)*m+j="<<(i-1)*m+j<<" (i-1)*m+j+1="<<(i-1)*m+j+1<<" z="<<z<<'\n';
            create((i-1)*m+j,(i-1)*m+j+1,z);
            create((i-1)*m+j+1,(i-1)*m+j,z);
           }
    for(int i=1;i<n;++i)
        for(int j=1;j<=m;++j)
        {
            R(z);
        //  cout<<"j+(i-1)*m="<<j+(i-1)*m<<" j+i*m="<<j+i*m<<" z="<<z<<'\n';
            create(j+(i-1)*m,j+i*m,z);
            create(j+i*m,j+(i-1)*m,z);
           }
    for(int i=1;i<n;++i)
        for(int j=1;j<m;++j)
        {
            R(z);
        //  cout<<"j+(i-1)*m="<<j+(i-1)*m<<" 1+j+i*m="<<1+j+i*m<<" z="<<z<<'\n';
            create(j+(i-1)*m,1+j+i*m,z);
            create(j+i*m+1,j+(i-1)*m,z);
           }
    s=1;t=n*m;
    int ans=0;
    while(bfs(s,t))
    {
        for(i=1;i<=n*m;++i)
            temp[i]=first[i];
        ans+=dfs(s,INF,t);
    }
    cout<<ans;
    return 0;
}
