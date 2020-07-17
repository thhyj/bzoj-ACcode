
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
	int n,k,h;
	int a[100001];
using namespace std;
inline void R(int &v)
{
	static char ch;
	v=0;
	bool p=0;
	do
	{
		ch=getchar();
		if(ch=='-')
		p=1;
	}while(!isdigit(ch));
	while(isdigit(ch))
	{
		v=(v<<1)+(v<<3)+(ch^'0');
		ch=getchar();
	}while(isdigit(ch));
	if(p)v=-v;
}
inline bool check(const int &mid)
{
	int pos=1,sum=0,cnt=1;
	bool pd=0;
	while(1)
	{
		for(int i=pos;i<=n;++i)
		{
		//	cout<<"sum="<<sum<<" cnt="<<cnt<<" i="<<i<<" a[i]="<<a[i]<<'\n';
			if(cnt>k)return 0;
			if(sum+a[i]>mid){++cnt,sum=0;pos=i;break;}
			sum+=a[i];
			if(i==n)return 1;
		}
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	R(n);R(k);
	int l=0,r=1000000005,mid;
	for(int i=1;i<=n;++i)
	{
		R(a[i]);
	}
	while(l<r-1)
	{
		mid=l+r>>1;
		//cout<<"l="<<l<<" r="<<r<<" mid="<<mid<<'\n';
		if(check(mid))r=mid;
		else l=mid;
		//cout<<"l="<<l<<" r="<<r<<" mid="<<mid<<'\n';
	}
	cout<<r;
	return 0;
}
