
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<set>
#define inf 1000000000
#define ll long long
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,l1,l2,ans;
struct data{int x,y;}a[155];
inline bool operator<(data a,data b)
{
	return a.y<b.y;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i].x=read(),a[i].y=read();
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		if(a[i].x>=l1)l1=a[i].y,ans++;
		else if(a[i].x>=l2)l2=a[i].y,ans++;
		if(l1<l2)swap(l1,l2);
	}
	printf("%d",ans);
	return 0;
}
