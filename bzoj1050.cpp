
#include<stdio.h>
#include<stdlib.h>
int fa[10005]={0},u[10005]={0},v[10005]={0},w[10005]={0};
int father(int x)
{
	if(fa[x]!=x) fa[x]=father(fa[x]);
	return fa[x];
}
void jh(int* a,int* b)
{
	int t=*a;
	*a=*b;
	*b=t;
}
void kp(int low,int high)
{
	int i=low,j=high,mid=w[(i+j)/2];
	while(i<j)
	{
		while(w[i]<mid) i++;
		while(w[j]>mid) j--;
		if(i<=j)
		{
			jh(&u[i],&u[j]);
			jh(&v[i],&v[j]);
			jh(&w[i],&w[j]);
			i++;
			j--;
		}
	}
	if(j>low) kp(low,j);
	if(i<high) kp(i,high);
}
int gcd(int a,int b)
{
	if(b==0) return a;
	return gcd(b,a%b);
}
int main()
{
	int n,m,i,j,s,t,min=-1,max=-1;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
		scanf("%d%d%d",&u[i],&v[i],&w[i]);
	scanf("%d%d",&s,&t);
	kp(1,m);
	for(i=1;i<=m;i++)//枚举最小边权:w[i]
	{
		if(w[i]==w[i-1]) continue;//快得不止一点点 
		for(j=1;j<=n;j++)
			fa[j]=j;
		for(j=i;j<=m;j++)
		{
			if(father(u[j])!=father(v[j])) fa[father(u[j])]=father(v[j]);
			if(father(s)==father(t)) break;
		}
		if(j<=m&&(min==-1||(double)max/(double)min>(double)w[j]/(double)w[i]))
		{
			min=w[i];
			max=w[j];
		}
	}
	if(min==-1) printf("IMPOSSIBLE");
	else
	{
		if(max%min==0) printf("%d",max/min);
		else printf("%d/%d",max/gcd(max,min),min/gcd(max,min));
	}
	return 0;
}
