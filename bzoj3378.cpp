
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cctype>
using namespace std;
char ch;
inline void R(long long &v)
{
	v=0;
	do
	{
		ch=getchar();
	}while(!isdigit(ch));
	while(isdigit(ch))
	{
		v=(v<<1)+(v<<3)+(ch^'0');
		ch=getchar();
	}
}
long long n;
long long ans[100001];
long long sum[100001],dis[100001];
inline long long lowbit(long long x)
{
	return x&-x;
}
inline void add(long long x)
{
	for(x;x<=20000;x+=lowbit(x))
	{
		sum[x]+=1;
	}
}
inline long long query(long long x)
{
	long long ret=0;
	for(x;x>0;x-=lowbit(x))
	{
		ret+=sum[x];
	}
	return ret;
}
inline void add1(long long x,long long y)
{
	for(x;x<=20000;x+=lowbit(x))
	{
		dis[x]+=y;
	}
}
inline long long query1(long long x)
{
	long long ret=0;
	for(x;x>0;x-=lowbit(x))
	{
		ret+=dis[x];
	}
	return ret;
}
struct ox
{
	long long x,v;	
}niu[30000];
inline bool cmp1(const ox &a,const ox &b)
{
	return a.x<b.x;
}
inline bool cmp2(const ox &a,const ox &b)
{
	return a.x>b.x;
}
int main()
{
	R(n);
	long long x,y;
	for(long long i=1;i<=n;++i)
	{
		R(niu[i].v);
		R(niu[i].x);
}
	sort(niu+1,niu+n+1,cmp1);
	long long ans=0;
	for(long long i=1;i<=n;++i)
	{
	//	cout<<"query(niu[i].v)="<<query(niu[i].v)<<'\n';
	//	cout<<"niu[i].x*query(niu[i].v)-query1(niu[i].v)="<<niu[i].x*query(niu[i].v)-query1(niu[i].v)<<'\n';
		ans+=niu[i].v*(niu[i].x*query(niu[i].v)-query1(niu[i].v));
		add(niu[i].v);
		add1(niu[i].v,niu[i].x);
	}
	memset(sum,0,sizeof(sum));
	memset(dis,0,sizeof(dis));
/*	sort(niu+1,niu+n+1,cmp2);
	for(long long i=1;i<=n;++i)
	{
		cout<<"query(niu[i].v)="<<query(niu[i].v)<<'\n';
				cout<<"query1(niu[i].v-niu[i].x*query(niu[i].v))="<<query1(niu[i].v-niu[i].x*query(niu[i].v))<<'\n';

		ans+=niu[i].v*(query(niu[i].v))*(query1(niu[i].v-niu[i].x*query(niu[i].v)));
		add(niu[i].v);
		add1(niu[i].v,niu[i].x);
	}*/
	for(long long i=n;i>=1;--i)
	{
		//cout<<"query(niu[i].v-1)="<<query(niu[i].v-1)<<'\n';
		//cout<<"query1(niu[i].v-1)-niu[i].x*query(niu[i].v-1)="<<query1(niu[i].v-1)-niu[i].x*query(niu[i].v-1)<<'\n';
		ans+=niu[i].v*(query1(niu[i].v-1)-niu[i].x*query(niu[i].v-1));
		add(niu[i].v);
		add1(niu[i].v,niu[i].x);
	}
	cout<<ans;
	return 0;
}
