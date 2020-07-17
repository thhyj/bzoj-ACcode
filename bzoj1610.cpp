
#include<iostream> 
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<ctime>
#include<cctype>
using namespace std;
int main()
{
	int x[301],y[301],n;
	double f[90001];
	cin>>n;
	int t=1;
	for(int i=1;i<=n;i++)
	  cin>>x[i]>>y[i];
	for(int i=1;i<=n;i++)
	  for(int j=i+1;j<=n;j++)
	  {
	  	if(x[i]==x[j])
	  	{
	  		f[t]=100000000;
	  		t++;
	  	}
	  	else
	  	{
	  		f[t]=y[i]-y[j];
	  		f[t]=f[t]/(x[i]-x[j]);
	  		t++;
	  	}
	  }
	sort(f+1,f+t);
	int ans=0;
	for(int i=2;i<=t;i++)
	{
		if(f[i]!=f[i-1])
		  ans++;
	}
	cout<<ans;
}
