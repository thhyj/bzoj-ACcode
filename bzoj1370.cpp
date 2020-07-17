
#include<iostream>
#include<set>
#include<map>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
#define inf 2000000000
#define pa pair<int,int>
#define ll long long 
using namespace std;
ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,ans;
int fa[2005],a[2005];
int find(int x)
{
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=2*n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		char ch[5];scanf("%s",ch);
		int x=read(),y=read();
		if(ch[0]=='F')fa[find(x)]=find(y);
		else fa[find(x)]=find(y+n),fa[find(y)]=find(x+n);
	}
	for(int i=1;i<=n;i++)a[i]=find(i);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
		if(a[i]!=a[i-1])
			ans++;
	printf("%d",ans);
	return 0;
}
