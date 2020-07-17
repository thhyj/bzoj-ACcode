
#include<bits/stdc++.h>
const int N=5000007;
long long n,s,ans,a[N];
int m,i,j;
int main()
{
    scanf("%lld%d",&n,&m);
    if(n==1)return puts("1"),0;
    if(n<=m+2)return printf("%lld",n-1),0;
    for(i=0;i<=m;i++)a[i]=1;
    a[m+1]=2;
    s=m+4;
    for(i=m+2;s<=n;i++)
        s+=a[i]=a[i-1]+a[i-m];
    i--;
    for(j=0;j+1<i;j++)ans+=a[j];
    n-=s-a[i];
    for(;n>1;i--)
        if(n>=a[i])n-=a[i],ans+=a[i-1];
    printf("%lld",ans+1);
}
