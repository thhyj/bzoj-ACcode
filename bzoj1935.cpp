
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,m,tot,que;
int disc[1500005];
int x[500005],y[500005];
int a[500005],b[500005],c[500005],d[500005];
int t[1500005];
int ans[500005][5];
struct data{int x,y,id,f;}q[2500005];
inline int lowbit(int x){return x&(-x);}
inline bool operator<(data a,data b)
{
	return a.x<b.x||(a.x==b.x&&a.f<b.f);
}
inline void add(int x,int y)
{
	for(int i=x;i<=tot;i+=lowbit(i))
		t[i]+=y;
}
inline int query(int x)
{
	int sum=0;
	for(int i=x;i;i-=lowbit(i))
		sum+=t[i];
	return sum;
}
int find(int x)
{
	int l=1,r=tot;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(disc[mid]==x)return mid;
		else if(disc[mid]<x)l=mid+1;
		else r=mid-1;
	}
}
void solve()
{
	sort(q+1,q+que+1);
	for(int i=1;i<=que;i++)
	{
		if(!q[i].f)add(q[i].y,1);
		else 
		{
			int t=query(q[i].y);
			ans[q[i].id][q[i].f]=t;
		}
	}
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)
	{
		x[i]=read(),y[i]=read();
	    disc[++tot]=y[i];
	}
	for(int i=1;i<=m;i++)
	{
		a[i]=read(),b[i]=read(),c[i]=read(),d[i]=read();
		disc[++tot]=b[i];disc[++tot]=d[i];
	}
	sort(disc,disc+tot+1);
	for(int i=1;i<=n;i++)
	{
	    y[i]=find(y[i]);
		q[++que].x=x[i];q[que].y=y[i];
	}
	for(int i=1;i<=m;i++)
	{
	    b[i]=find(b[i]);d[i]=find(d[i]);
		q[++que].x=c[i];q[que].y=d[i];q[que].id=i;q[que].f=1;
		q[++que].x=a[i]-1;q[que].y=d[i];q[que].id=i;q[que].f=2;
		q[++que].x=c[i];q[que].y=b[i]-1;q[que].id=i;q[que].f=3;
		q[++que].x=a[i]-1;q[que].y=b[i]-1;q[que].id=i;q[que].f=4;
	}
	solve();
	for(int i=1;i<=m;i++)
	{
		int t=ans[i][1]+ans[i][4]-ans[i][2]-ans[i][3];
		printf("%d\n",t);
	}
	return 0;
}
