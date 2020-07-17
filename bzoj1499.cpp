
#include<map>
#include<cmath>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define inf 1000000000
#define ll long long
using namespace std;
ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
char a[205][205];
int f[205][205][205];
int xx[]={0,-1,1,0,0},yy[]={0,0,0,-1,1};
int q[205],pos[205],head,tail;
int n,m,sx,sy,K,ans;
void push(int now,int val,int x,int y)
{
	if(val==-inf)return;
	while(val-now>q[tail]&&head<=tail)tail--;
	q[++tail]=val-now;
	pos[tail]=now;
}
void dp(int p,int x,int y,int d,int T)
{
	head=1;tail=0;int now=1;
	while(x<=n&&y<=m&&x>=1&&y>=1)
	{
		if(a[x][y]=='x')
			head=1,tail=0;
		else push(now,f[p-1][x][y],x,y);
		while(now-pos[head]>T&&head<=tail)head++;
		if(head<=tail)
			f[p][x][y]=q[head]+now;
		else f[p][x][y]=-inf;
		ans=max(ans,f[p][x][y]);
		x+=xx[d];y+=yy[d];
		now++;
	}
}
int main()
{
	n=read();m=read();sx=read();sy=read();K=read();
	for(int i=1;i<=n;i++)
		scanf("%s",a[i]+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			f[0][i][j]=-inf;
	f[0][sx][sy]=0;
	for(int i=1;i<=K;i++)
	{
		int x=read(),y=read(),d=read();
		if(d==1)for(int j=1;j<=m;j++)dp(i,n,j,d,y-x+1);
		if(d==2)for(int j=1;j<=m;j++)dp(i,1,j,d,y-x+1);
		if(d==3)for(int j=1;j<=n;j++)dp(i,j,m,d,y-x+1);
		if(d==4)for(int j=1;j<=n;j++)dp(i,j,1,d,y-x+1);				
	}
	printf("%d\n",ans);
	return 0;
}
