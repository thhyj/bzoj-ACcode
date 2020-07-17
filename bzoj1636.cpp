
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
inline void R(int &v)
{
	char c=getchar();
	v=0;
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
	{
		v=(v<<1)+(v<<3)+(c^'0');
		c=getchar();
	}
}
int a[50010];
int st1[50010][20];
int st2[50010][20];
int logtable[50010];
int n,m;
inline void rmq()
{
	for(register int i=1;i<=n;++i)
	{
		st1[i][0]=a[i];
		st2[i][0]=a[i];
	}
	for(register int j=1;(1<<j)<=n;++j)
		for(register int i=1;i+(1<<j)-1<=n;++i)
		{
			st1[i][j]=min(st1[i][j-1],st1[i+(1<<(j-1))][j-1]);
			st2[i][j]=max(st2[i][j-1],st2[i+(1<<(j-1))][j-1]);
		}
		logtable[0]=-1;
	for(register int i=1;i<=n;++i)
		logtable[i]=logtable[i>>1]+1;
}

inline int getmin(int &l,int &r)
{
	if(l==r)
		return a[l];
	else
		return min(st1[l][logtable[r-l]],st1[r-(1<<logtable[r-l])+1][logtable[r-l]]);
}
inline int getmax(int &l,int &r)
{
	if(l==r)
		return a[l];
	else
		return max(st2[l][logtable[r-l]],st2[r-(1<<logtable[r-l])+1][logtable[r-l]]);
}
int main()
{
	//ios::sync_with_stdio(0);
	//cin.tie(0);
	//freopen("in.in","r",stdin);
	//freopen("out.out","w",stdout);
	R(n);
	R(m);
	for(register int i=1;i<=n;++i)
	{
		R(a[i]);
	}
	rmq();
		//for(int j=0;(1<<j)<=n;++j)
		//for(int i=1;i+(1<<j)-1<=n;++i)
		//{
		//	cout<<st1[i][j]<<" "<<st2[i][j]<<"\n";
		//}
	int x,y;
	for(register int i=1;i<=m;++i)
	{
		R(x);
		R(y);
		cout<<getmax(x,y)-getmin(x,y)<<"\n";
	}
	return 0;
}
