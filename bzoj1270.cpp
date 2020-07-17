
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<queue>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
#include<iostream>
using namespace std;
int sc()
{
	int i=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')i=i*10+c-'0',c=getchar();
	return i;
}
int a[2002][2002],f[2002][2002],mxh[2002];
int n,h,delta;
int main()
{
	n=sc(),h=sc(),delta=sc();
	for(int i=1;i<=n;i++)
	{
		int x=sc(),y;
		for(int j=1;j<=x;j++)y=sc(),a[i][y]++;
	}
	for(int i=1;i<=n;i++)f[i][h]=a[i][h],mxh[h]=max(mxh[h],f[i][h]);
	for(int i=h-1;i;i--)
	{
		int mx=0;
		if(i+delta<=h) mx=mxh[i+delta];
		for(int j=1;j<=n;j++)
		{
			f[j][i]=max(f[j][i+1],mx);
			f[j][i]+=a[j][i];
			mxh[i]=max(mxh[i],f[j][i]);
		}
	}
	cout << mxh[1];
	return 0;
}
