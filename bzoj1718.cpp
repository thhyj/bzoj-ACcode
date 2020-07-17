
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<ctime>
#include<cctype>
using namespace std;
inline void R(int &v)
{
    static char ch;
    bool p=0;
    v=0;
    do{
        ch=getchar();
        if(ch=='-')
        {
            p=1;
        }
    }while(!isdigit(ch));
    while(isdigit(ch))
    {
        v=(v<<1)+(v<<3)+(ch^'0');
        ch=getchar();
    }
    if(p)
    {
        v=-v;
    }
}
int first[5005],to[20005],nxt[20005],tot,top,cnt,indx,dfn[5005],low[5005],chudu[5005],lef,exist[5005],st[5005],num[5005],rudu[5005];
inline void create(int &x,int &y)
{
    nxt[tot]=first[x];
    first[x]=tot;
    to[tot]=y;
    ++tot;
}
void tarjan(int x,int fa)
{
    dfn[x]=++indx;
    low[x]=indx;
    exist[x]=1;
    st[++top]=x;
    for(int p=first[x];~p;p=nxt[p])
    {
        if(p==fa||p==(fa^1))continue;
        if(!dfn[to[p]])
        {
            tarjan(to[p],p);
            low[x]=min(low[x],low[to[p]]);
        }
        else
        if(exist[to[p]])
        {
            low[x]=min(low[x],dfn[to[p]]);
        }
    }
    if(low[x]==dfn[x])
    {
        ++cnt;
        //cout<<"cnt="<<cnt<<'\n';
        do{
            //cout<<"st[top]="<<st[top]<<'\n';
            num[st[top]]=cnt;
            exist[st[top]]=0;
        }while(st[top--]^x);
    }
}
int main()
{
    memset(first,-1,sizeof(first));
    int n,m;
    R(n);R(m);
    int x,y;
    for(int i=1;i<=m;++i)
    {
        R(x);R(y);
        create(x,y);
        create(y,x);
    }
    for(int i=1;i<=n;++i)
    {
        if(!dfn[i])
        tarjan(i,-1000);
    }
    for(int i=1;i<=n;++i)
    {
        for(int p=first[i];~p;p=nxt[p])
        {
            if(num[i]^num[to[p]])
            {
                ++chudu[num[i]];
            }
        }
    }
//    for(int i=1;i<=cnt;++i)
    //cout<<"i="<<i<<" chudu="<<chudu[i]<<'\n';
    for(int i=1;i<=cnt;++i)
    {
        if(chudu[i]==1)
        {
            ++lef;
        }
    }
    cout<<(lef+1)/2;
    return 0;
}
