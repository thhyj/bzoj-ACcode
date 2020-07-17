
#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<string>
#include<bitset>
#include<queue>
#include<set>
#include<map>
using namespace std;

typedef long long ll;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return f*x;
}
void print(int x)
{if(x<0)putchar('-'),x=-x;if(x>=10)print(x/10);putchar(x%10+'0');}

const int N=300100,mod=19260817;

int n,a[N],b[N],c[N],pos[N];

int bit[N];

inline void modify(int x,int val)
{for(;x<=n;x+=(x&-x))(bit[x]+=val)%=mod;}

inline int query(int x)
{
	int res=0;
	for(;x;x-=(x&-x))(res+=bit[x])%=mod;
	return res;
}

inline bool cmp(int x,int y)
{return a[x]<a[y];}

int main()
{
	n=read();
	register int i,ans=0,tmp=1;
	for(i=1;i<=n;++i)a[i]=read(),b[i]=i;
	sort(b+1,b+1+n,cmp);
	pos[b[1]]=1;
	for(i=2;i<=n;++i){if(a[b[i]]^a[b[i-1]])tmp++;pos[b[i]]=tmp;}
	for(i=1;i<=n;++i)a[i]%=mod;
	for(i=1;i<=n;++i)c[i]=1ll*a[i]*query(pos[i]-1)%mod,modify(pos[i],a[i]);
	memset(bit,0,sizeof(bit));
	for(i=1;i<=n;++i)(ans+=1ll*a[i]*query(pos[i]-1)%mod)%=mod,modify(pos[i],c[i]);
	print(ans);puts("");
}