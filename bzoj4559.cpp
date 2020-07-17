
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define F(i,j,n) for(int i=j;i<=n;i++)
#define D(i,j,n) for(int i=j;i>=n;i--)
#define ll long long
#define N 105
#define mod 1000000007
using namespace std;
int n,m,k;
ll ans,s[N],rnk[N],fac[N],inv[N],f[N],g[N];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
inline ll getpow(ll x,ll y)
{
	ll ret=1;
	for(;y;y>>=1,x=x*x%mod) if (y&1) ret=ret*x%mod;
	return ret;
}
inline ll C(int x,int y)
{
	return fac[x]*inv[y]%mod*inv[x-y]%mod;
}
int main()
{
	n=read();m=read();k=read();
	F(i,1,m) s[i]=read();
	F(i,1,m) rnk[i]=read();
	fac[0]=inv[0]=1;
	F(i,1,100) fac[i]=fac[i-1]*i%mod,inv[i]=getpow(fac[i],mod-2);
	D(i,n-1,k)
	{
		f[i]=C(n-1,i);
		F(j,1,m) f[i]=f[i]*C(n-1-i,rnk[j]-1)%mod;
		F(j,i+1,n-1) f[i]=(f[i]-f[j]*C(j,i)%mod+mod)%mod;
	}
	ans=1;
	F(i,1,m)
	{
		g[0]=s[i];
		F(j,1,n)
		{
			g[j]=(getpow(s[i]+1,j+1)-1+mod)%mod;
			F(l,0,j-1) g[j]=(g[j]-C(j+1,l)*g[l]%mod+mod)%mod;
			g[j]=g[j]*getpow(j+1,mod-2)%mod;
		}
		ll tmp=0,p=1;
		F(j,0,rnk[i]-1) tmp=(tmp+C(rnk[i]-1,j)*getpow(s[i],rnk[i]-1-j)%mod*g[n-rnk[i]+j]%mod*p+mod)%mod,p=-p;
		ans=ans*tmp%mod;
	}
	cout<<ans*f[k]%mod<<endl;
	return 0;
}
