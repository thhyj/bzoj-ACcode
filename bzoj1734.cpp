
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cctype>
using namespace std;
char ch;
inline void R(int &v)
{
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
int n,m;
int a[1000005];
inline bool check(const int &mid)
{
    int l=1,cnt=1;
    while(cnt<m)
    {
        if(a[n]-a[l]<mid)return 0;
        for(int i=l+1;i<=n;++i)
        {
            if(a[i]-a[l]<mid)continue;
            ++cnt;
            l=i;
        }
    }
    return 1;
}
int main()
{
    R(n);R(m);
    for(int i=1;i<=n;++i)
    {
        R(a[i]);
    }
    sort(a+1,a+n+1);
    int l=-1,r=1000000009,mid;
    while(l<r-1)
    {
        mid=l+r>>1;
        if(check(mid))l=mid;
        else r=mid;
    }
    cout<<l;
    return 0;
}
