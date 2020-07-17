
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#define ll long long
#define inf 1000000000
using namespace std;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
ll ans1,ans2;
int n;
int a[100005];
int main()
{
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=2;i<=n;i++)
		if(a[i]>a[i-1])ans1+=a[i]-a[i-1];
		else ans2+=a[i-1]-a[i];
	printf("%lld\n%d",max(ans1,ans2),abs(ans1-ans2)+1);
	return 0;
}
