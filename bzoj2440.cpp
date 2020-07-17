
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<set>
#include<ctime>
#include<vector>
#include<cmath>
#include<algorithm>
#include<map>
#define N 50000
#define ll long long 
using namespace std;
inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int T;
ll ans,K;
int tot;
int mu[50005],pri[50005];
bool mark[50005];
void getmu()
{
    mu[1]=1;
    for(int i=2;i<=N;i++)
    {
		if(!mark[i])pri[++tot]=i,mu[i]=-1;
		for(int j=1;j<=tot&&pri[j]*i<=N;j++)
		{
			mark[i*pri[j]]=1;
			if(i%pri[j]==0){mu[i*pri[j]]=0;break;}
			else mu[i*pri[j]]=-mu[i];
		}
    }
}
ll cal(int x)
{
    ll sum=0;
    int t=sqrt(x);
    for(int i=1;i<=t;i++)
		sum+=x/(i*i)*mu[i];
    return sum;
}
int main()
{
    getmu();
    T=read();
    while(T--)
    {
		K=read();
		ll l=K,r=1644934081;
		while(l<=r)
		{
			ll mid=(l+r)>>1;
			if(cal(mid)>=K)ans=mid,r=mid-1;
			else l=mid+1;
		}
		printf("%lld\n",ans);
    }
    return 0;
}
