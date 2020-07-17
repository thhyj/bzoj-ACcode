
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
int n,K,m,ans;
int fa[10005];
struct data{int x,y,c1,c2;}e[20005];
int find(int x)
{return x==fa[x]?x:fa[x]=find(fa[x]);}
bool jud(int x)
{
	for(int i=1;i<=n;i++)fa[i]=i;
	int cnt=0;
	for(int i=1;i<=m;i++)
	{
		if(e[i].c1>x)continue;
		int p=find(e[i].x),q=find(e[i].y);
		if(p!=q)
		{fa[p]=q;cnt++;}
	}
	if(cnt<K)return 0;
	for(int i=1;i<=m;i++)
	{
		if(e[i].c2>x)continue;
		int p=find(e[i].x),q=find(e[i].y);
		if(p!=q)
		{fa[p]=q;cnt++;}
	}
	if(cnt!=n-1)return 0;
	return 1;
}
int main()
{
	n=read(),K=read(),m=read();
	for(int i=1;i<m;i++)
	    e[i].x=read(),e[i].y=read(),e[i].c1=read(),e[i].c2=read();
	int l=1,r=30000;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(jud(mid)){ans=mid;r=mid-1;}
		else {l=mid+1;}
	}
	printf("%d",ans);
	return 0;
}
