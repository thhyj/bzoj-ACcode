
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
const int MAXN=2501;
int dp[MAXN];
int a[MAXN],b[MAXN];
int main(int argc, char *argv[])
{
    memset(dp,0x7f,sizeof(dp));
    dp[0]=0;
    int n,i,j,m;
    char x;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)
    {
        scanf("\n%c",&x);
        a[i]=a[i-1],b[i]=b[i-1];
        if(x=='H') a[i]++;
        else b[i]++;
    }
    for(i=1;i<=n;i++)
    for(j=0;j<i;j++)
    {
        if((abs(a[i]-a[j]-b[i]+b[j])<=m)||(a[i]-a[j]==0)||(b[i]-b[j]==0)) dp[i]=min(dp[i],dp[j]+1);
    }
    printf("%d\n",dp[n]);
    return 0;
}
