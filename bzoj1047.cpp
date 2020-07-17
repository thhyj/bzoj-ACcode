
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
#include<deque>
#define inf 2000000000
#define ll long long 
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int a,b,n;
int v[1005][1005],mx[1005][1005],mn[1005][1005],t1[1005],t2[1005];
int val[1005],pos[1005];
void pre()
{
	int l,r;
	for(int i=1;i<=a;i++)
	{
	    l=1,r=1;
		for(int j=1;j<=b;j++)
		{
			while(l<r&&val[r-1]<=v[i][j])r--;
			val[r]=v[i][j];pos[r]=j;r++;
			if(pos[l]==j-n)l++;
			if(j>=n)mx[i][j]=val[l];
		}
		l=1,r=1;
		for(int j=1;j<=b;j++)
		{
			while(l<r&&val[r-1]>=v[i][j])r--;
			val[r]=v[i][j];pos[r]=j;r++;
			if(pos[l]==j-n)l++;
			if(j>=n)mn[i][j]=val[l];
		}
	}
}
void solve()
{
	int ans=inf;
	int l,r;
	for(int i=n;i<=b;i++)
	{
		l=1,r=1;
		for(int j=1;j<=a;j++)
		{
			while(l<r&&val[r-1]>=mn[j][i])r--;
			val[r]=mn[j][i];pos[r]=j;r++;
			if(pos[l]==j-n)l++;
			if(j>=n)t1[j]=val[l];
		}
		l=1,r=1;
		for(int j=1;j<=a;j++)
		{
			while(l<r&&val[r-1]<=mx[j][i])r--;
			val[r]=mx[j][i];pos[r]=j;r++;
			if(pos[l]==j-n)l++;
			if(j>=n)t2[j]=val[l];
		}
		for(int i=n;i<=a;i++)ans=min(ans,t2[i]-t1[i]);
	}
	printf("%d\n",ans);
}
int main()
{
	a=read();b=read();n=read();
	for(int i=1;i<=a;i++)
		for(int j=1;j<=b;j++)
			v[i][j]=read();
	pre();
	solve();
	return 0;
}
