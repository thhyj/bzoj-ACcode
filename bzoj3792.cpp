
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<string>
#define inf 1000000000
#define maxn 500
#define maxm 500+100
#define eps 1e-10
#define ll long long
#define pa pair<int,int>
#define for0(i,n) for(int i=0;i<=(n);i++)
#define for1(i,n) for(int i=1;i<=(n);i++)
#define for2(i,x,y) for(int i=(x);i<=(y);i++)
#define for3(i,x,y) for(int i=(x);i>=(y);i--)
#define for4(i,x) for(int i=head[x],y;i;i=e[i].next)
#define mod 45989
using namespace std;
inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=10*x+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,s,tot,cnt,num[maxn],c[maxn][2];
struct matrix
{
    int d[maxn][maxn];
    matrix(){memset(d,0,sizeof(d));}
}a,b;
inline matrix operator *(matrix &x,matrix &y)
{
    matrix z;
    for1(i,m)
     for1(j,m)
      for1(k,m)
       (z.d[i][j]+=x.d[i][k]*y.d[k][j])%=mod;
    return z;
}
inline void print(matrix x)
{
    for1(i,m)for1(j,m)cout<<i<<' '<<j<<' '<<x.d[i][j]<<endl;
}
void ksm(ll y)
{
    for(;y;y>>=1,a=a*a)
     if(y&1)b=b*a;
}
int main()
{
  //  freopen("input.txt","r",stdin);
   // freopen("output.txt","w",stdout);
    n=read();m=read();s=read();ll q=read();tot=1;
    for1(i,m)
    {
        int x=read(),y=read();
        c[++tot][0]=x;c[tot][1]=y;
        c[++tot][0]=y;c[tot][1]=x;
    }
    m=tot;
    for1(i,m)for1(j,m)if(i!=j&&i!=(j^1)&&c[i][1]==c[j][0])a.d[i][j]=1;
    for1(i,m)b.d[i][i]=1;
    ksm(q-1);
    for1(i,m)if(c[i][0]==s)num[++cnt]=i;
    for1(i,n)
    {
        int ans=0;
        for1(j,m)if(c[j][1]==i)
        for1(k,cnt)(ans+=b.d[num[k]][j])%=mod;
        printf("%d\n",ans);
    }
    return 0;
}
