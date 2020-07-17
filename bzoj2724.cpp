
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
int n,Q,S,s,ans,l,r,m;
const int N=4e4+5,B=205,INF=0x3f3f3f3f;
int a[N],b[N],rk[N],br[N],bl[N],sum[N],f[B][B],cnt[N][B];
bool vis[N];
inline void Init()
{
	int k,cur,maxv,h,t,c;
	for(int i=1;i<=s;i++)
	{
		k=bl[i],cur=INF,maxv=-INF;
		for(int j=k;j<n;j++)sum[a[j]]=0;
		for(int j=i;j<=s;j++)
		{
			t=br[j];
			while(k<=t)
			{
				c=++sum[a[k]];
				if(c>maxv)maxv=c,cur=a[k];
				else if(c==maxv&&a[k]<cur)cur=a[k];
				++k;
			}
			f[i][j]=cur;
		}
	}
	memset(sum,0,sizeof(sum));
	for(int i=1;i<=s;i++)
	{
		for(int j=0;j<m;j++)cnt[j][i]=cnt[j][i-1];
		h=bl[i],t=br[i];
		while(h<=t)
		{
			cnt[a[h]][i]=++sum[a[h]];
			h++;
		}
	}
	return;
}

inline int Query(const int &l,const int &r)
{
	int maxv=-INF,res=-INF,c;
	if(r-l<2*S)
	{
		for(int i=l;i<=r;i++)
		if(!vis[a[i]])vis[a[i]]=true,sum[a[i]]=1;
		else sum[a[i]]++;
		for(int i=l;i<=r;i++)
		if(vis[a[i]])
		{
			if(sum[a[i]]>maxv)maxv=sum[a[i]],res=a[i];
			else if(sum[a[i]]==maxv&&a[i]<res)res=a[i];
			vis[a[i]]=false;
		}
		return b[res];
	}
	int L=l/S+1,R=r/S+1,st,ed;
	if(l==bl[L])L--;
	if(r==br[R])R++;
	res=f[L+1][R-1],maxv=cnt[res][R-1]-cnt[res][L];
	ed=br[L];st=bl[R];
	for(int i=l;i<=ed;i++)
		if(!vis[a[i]])vis[a[i]]=true,sum[a[i]]=1;
		else ++sum[a[i]];
	for(int i=st;i<=r;i++)
		if(!vis[a[i]])vis[a[i]]=true,sum[a[i]]=1;
		else ++sum[a[i]];
	for(int i=l;i<=ed;i++)
	if(vis[a[i]])
	{
		c=cnt[a[i]][R-1]-cnt[a[i]][L];c+=sum[a[i]];
		if(c>maxv)maxv=c,res=a[i];
		else if(c==maxv&&a[i]<res)res=a[i];
		vis[a[i]]=false;
	}
	for(int i=st;i<=r;i++)
	{
		if(vis[a[i]])
		{
			c=cnt[a[i]][R-1]-cnt[a[i]][L];c+=sum[a[i]];
			if(c>maxv)maxv=c,res=a[i];
			else if(c==maxv&&a[i]<res)res=a[i];
			vis[a[i]]=false;
		}
	}
	return b[res];
}
int main()
{
	scanf("%d%d",&n,&Q);
	S=sqrt(n);
	for(int i=0;i<n;i++)scanf("%d",&a[i]),b[i]=a[i];
	sort(b,b+n);m=unique(b,b+n)-b;
	for(int i=0;i<=n;i++)a[i]=lower_bound(b,b+m,a[i])-b;
	for(int i=0;i<n;i++)
		if(i%S==0)br[s]=i-1,bl[++s]=i;
	br[s]=n-1;bl[s+1]=br[s+1]=n;
	Init();
	while(Q--)
	{
		scanf("%d%d",&l,&r);
		l=(l+ans-1)%n;r=(r+ans-1)%n;
		if(l>r)swap(l,r);
		printf("%d\n",ans=Query(l,r));
	}
	return 0;
}
