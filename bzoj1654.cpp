
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cctype>
#include<ctime>
#include<algorithm>
using namespace std;
inline void R(int &v)
{
    static char ch;
    v=0;
    bool p=0;
    do {
        ch=getchar();
        if(ch=='-')
        {
            p=1;
        }
    } while(!isdigit(ch));
    while(isdigit(ch))
    {
        v=(v<<1)+(v<<3)+(ch^'0');
        ch=getchar();
    }
    if(p)
    v=-v;
}
int first[10005],low[10005],dfn[10005],to[50005],nxt[50005],st[50005],cnt,top,indx,tot,ans;
bool exist[10005];
inline void create(const int &x,const int &y)
{
    ++tot;
    nxt[tot]=first[x];
    first[x]=tot;
    to[tot]=y;
}
void tarjan(int x)
{
    low[x]=++indx;
    dfn[x]=indx;
    exist[x]=1;
    st[++top]=x;
    for(int p=first[x];p;p=nxt[p])
    {
        if(!dfn[to[p]])
        {
            tarjan(to[p]);
            low[x]=min(low[x],low[to[p]]);
        }
        else
        if(exist[to[p]])
        {
            low[x]=min(low[x],dfn[to[p]]);
        }
    }
    if(dfn[x]==low[x])
    {
        int sum=0;
        ++cnt;
        do{
            ++sum;
            exist[st[top]]=0;
        }while(st[top--]^x);
        if(sum>=2)
        ++ans;
    }
}
int main()
{
    int n,m;
    R(n);R(m);
    int x,y;
    for(int i=1;i<=m;++i)
    {
        R(x);R(y);
        create(x,y);
    }
    for(int i=1;i<=n;++i)
    {
        if(!dfn[i])
        {
            tarjan(i);
        }
    }
    cout<<ans;
    return 0;
}
