
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<queue>
using namespace std;
int n,m,i,j,w[3500],c[3500];
int f[13000]; 
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	memset(f,0,sizeof(f));
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	  scanf("%d%d",&w[i],&c[i]);
	for(i=1;i<=n;i++)
	  for(j=m;j>=w[i];j--)
	    f[j]=max(f[j],f[j-w[i]]+c[i]);
	printf("%d",f[m]);
	return 0;
}
