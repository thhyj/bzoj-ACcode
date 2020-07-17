
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
int n,m,top,mx;
int a[100005];
int f1[105][105],f2[100005];
int ans[2][100005];
struct data{int x,f,p,k,num;}q[200005];
inline bool cmp(data a,data b)
{return a.x<b.x;}
void add(int x)
{
     for(int i=1;i<=100;i++)
         f1[i][x%i]++;
     f2[x]++;
}
int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++)
        a[i]=read(),mx=max(mx,a[i]);
    for(int i=1;i<=m;i++)
    {
        int l=read(),r=read(),p=read(),k=read();
        q[++top].x=l-1;q[top].p=p;q[top].k=k;q[top].num=i;
        q[++top].x=r;q[top].p=p;q[top].k=k;q[top].num=i;q[top].f=1;
    }
    sort(q+1,q+top+1,cmp);
    int now=0;
    for(int i=1;i<=top;i++)
    {
        while(now<q[i].x){now++;add(a[now]);}
        int p=q[i].p,k=q[i].k;
        if(p<=100)ans[q[i].f][q[i].num]=f1[p][k];
        else 
        for(int j=k;j<=mx;j+=p)
            ans[q[i].f][q[i].num]+=f2[j];
    }
    for(int i=1;i<=m;i++)
        printf("%d\n",ans[1][i]-ans[0][i]);
    return 0;
}
