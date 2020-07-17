
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
#define Mod 5000011
#define N 100005

int n,k,sum,ans;
int f[N];
int main()
{
    scanf("%d%d",&n,&k);
    for (int i=0;i<=n;++i) f[i]=1;
    sum=0;
    for (int i=k+1;i<=n;++i)
    {
        f[i]=(f[i]+sum)%Mod;
        sum=(sum+f[i-k])%Mod;
    }
    //  for (int j=1;j<=i-k-1;++j)
    //      f[i]=(f[i]+f[j])%Mod;
    for (int i=0;i<=n;++i) ans=(ans+f[i])%Mod;
    printf("%d\n",ans);
}
