
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
using namespace std;
int n,m;
int d[10001],dp[10001][501],i,j;
bool pd[10001][501];
inline void R(int &v)
{
	v=0;
	char c=0;
	bool p=true;
	while(c>'9'||c<'0')
	{
		if(c=='-')
		{
			p=false;
		}
		c=cin.get();
	}
	while(c>='0'&&c<='9')
	{
		v=(v<<3)+(v<<1)+c-'0';
		c=cin.get();
	}
	if(p==false)
	{
		v=-v;
	}
}
int main()
{
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);
    //freopen("cowrun.in","r",stdin);
	//freopen("cowrun.out","w",stdout);
	R(n);
	R(m);
	for(i=1;i<=n;i++)
	{
		R(d[i]);
	}
	for(i=1;i<=n;i++)
	 {dp[i][0]=dp[i-1][0];
	for(j=1;j<=m&&j<=i;j++)
	 {
	 	
		dp[i][j]=dp[i-1][j-1]+d[i];
		dp[i][0]=max(dp[i][0],dp[i-j][j]);
		
	 } 
	 } 
	 cout<<dp[n][0];
	 return 0;
}
