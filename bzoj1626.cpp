
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<queue>
using namespace std;
int n,m,f[1001],i,j,p,k,x,y;
double ans=0;
struct pp{
	int x;
	int y;
	double v;
}; 
pp l[500501],zb[1001];
int find(int x)
{
	if(x==f[x])return f[x];
	f[x]=find(f[x]);
	return f[x];
} 
void hb(int x,int y)
{
	int fx=find(x);
	int fy=find(y);
	if(fx!=fy)f[fx]=fy;
}
bool com(pp a,pp b)
{
	return a.v<b.v;
}
int main()
{
	/////freopen("a.in","r",stdin);
	//////freopen("a.out","w",stdout);
	k=0;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	  f[i]=i;
	for(i=1;i<=n;i++)
	{
	  scanf("%d%d",&x,&y);
	  zb[i].x=x;
	  zb[i].y=y;
    }
    for(i=1;i<=m;i++)
    {
    	scanf("%d%d",&x,&y);
    	if(find(x)!=find(y)) 
    	   hb(x,y),k++;
    }
    if(k>=n-1)printf("0.00"),exit(0);
    p=0;
    for(i=1;i<=n;i++)
    {
    	for(j=i+1;j<=n;j++)
    	{
    		p++;
    		l[p].x=i;
    		l[p].y=j;
    		l[p].v=sqrt(double(zb[i].x-zb[j].x)*(zb[i].x-zb[j].x)+double(zb[i].y-zb[j].y)*(zb[i].y-zb[j].y));
    	}
    }
    sort(l+1,l+p+1,com);
    for(i=1;i<=p;i++)
    {
    	if(find(l[i].x)!=find(l[i].y))
    	{
    		hb(l[i].x,l[i].y);
    		k++;
    		ans=ans+l[i].v;
    	}
    	if(k==n-1)break;
    }
    printf("%.2f",ans);
	return 0;
}
