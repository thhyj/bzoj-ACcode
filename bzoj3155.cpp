
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
int n,m;
int a[100005];
ll t[2][100005];
inline int lowbit(int x){return x&(-x);}
void update(int f,int x,ll val)
{
     for(int i=x;i<=n;i+=lowbit(i))
         t[f][i]+=val;
}
inline ll ask(int f,int x)
{
     ll tmp=0;
     for(int i=x;i;i-=lowbit(i))
         tmp+=t[f][i];
     return tmp;
}
int main()
{
     n=read();m=read();
     int x,y;
     for(int i=1;i<=n;i++)
     {
          a[i]=read();
          update(0,i,a[i]);
          update(1,i,(ll)(n-i+1)*a[i]);
     }
     for(int i=1;i<=m;i++)
     {
         char ch[10];
         scanf("%s",ch);
         if(ch[0]=='Q')
         {
              x=read();
              printf("%lld\n",ask(1,x)-ask(0,x)*(n-x));
         }
         else 
         {
              x=read(),y=read();
              update(0,x,y-a[x]);
              update(1,x,(ll)(n-x+1)*(y-a[x])); 
              a[x]=y;
         }
     }
     return 0;
}
