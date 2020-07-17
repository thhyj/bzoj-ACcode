
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
#define pa pair<long long,int>
#define inf 1000000000000000ll
#define maxn 500010
#define maxm 6000100

using namespace std;

int head[maxn],to[maxm],next[maxm],a[20];
long long dis[maxn],len[maxm];
bool vis[maxn];
int n,m,num,mn;
long long L,R;
priority_queue<pa,vector<pa>,greater<pa> >q;

void addedge(int x,int y,int z)
{
	num++;to[num]=y;len[num]=z;next[num]=head[x];head[x]=num;
}

void dijkstra()
{
	for (int i=1;i<mn;i++) dis[i]=inf;
	q.push(make_pair(0,0));
	while (!q.empty())
	{
		int x=q.top().second;q.pop();
		if (vis[x]) continue;vis[x]=1;
		for (int p=head[x];p;p=next[p])
		  if (dis[x]+len[p]<dis[to[p]])
		  {
		  	dis[to[p]]=dis[x]+len[p];
		  	q.push(make_pair(dis[to[p]],to[p]));
		  }
	}
}

int main()
{
	scanf("%d%lld%lld",&n,&L,&R);
	mn=500000;
	for (int i=1;i<=n;i++) {scanf("%d",&a[i]);mn=min(mn,a[i]);}
	for (int i=0;i<mn;i++)
	  for (int j=1;j<=n;j++)
	    if (a[j]%mn!=0) addedge(i,(i+a[j])%mn,a[j]);
	dijkstra();
	long long ans=0;
	L--;
	for (int i=0;i<mn;i++)
	{
		if (dis[i]<=L) ans-=(L-dis[i])/mn+1;
		if (dis[i]<=R) ans+=(R-dis[i])/mn+1;
	}
	printf("%lld\n",ans);
	return 0;
}
