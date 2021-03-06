
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
#define ll long long 
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int tot;
int mu[50005],sum[50005],pri[50005];
bool mark[50005];
void get()
{
	mu[1]=1;
	for(int i=2;i<=50000;i++)
	{
		if(!mark[i])pri[++tot]=i,mu[i]=-1;
		for(int j=1;j<=tot&&i*pri[j]<=50000;j++)
		{
			mark[i*pri[j]]=1;
			if(i%pri[j]==0){mu[i*pri[j]]=0;break;}
			else mu[i*pri[j]]=-mu[i];
		}
	}
	for(int i=1;i<=50000;i++)
		sum[i]=sum[i-1]+mu[i];
}
int cal(int n,int m)
{
	if(n>m)swap(n,m);
	long long ans=0,pos;
	for(int i=1;i<=n;i=pos+1)
	{
		pos=min(n/(n/i),m/(m/i));
		ans+=(sum[pos]-sum[i-1])*(n/i)*(m/i);
	}
	return ans;
}
int main()
{
	get();
	int T=read();
	while(T--)
	{
		int a=read(),b=read(),d=read();
		printf("%d\n",cal(a/d,b/d));
	}
	return 0;
}
