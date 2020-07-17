
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cctype>
using namespace std;
const int mp=10000000;
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
int task;
struct shu
{
	int zhi;
	int pos;
}num[200001];
struct tree
{
	int lson,rson,sum,ans;
}t[5000001];
int root[200001];
inline bool cmp1(const shu & a,const shu & b)
{
	return a.pos<b.pos;
}
int tot;
inline void update(int x)
{
	t[x].sum=t[t[x].lson].sum+t[t[x].rson].sum;
	t[x].ans=t[t[x].lson].ans+t[t[x].rson].ans;
}
bool pd;
void build(int now,int prev,int l,int r,int x,int fuhao)
{
	if(l==r)
	{
		if(fuhao==1)
		t[now].sum=t[prev].sum+1;
		else
		t[now].sum=t[prev].sum-1;
		t[now].ans=t[prev].ans+x*fuhao;
		return ;
	}
	int mid=l+r>>1;
	if(x<=mid)
	{
		t[now].lson=++tot;
		t[now].rson=t[prev].rson;
		build(t[now].lson,t[prev].lson,l,mid,x,fuhao);
	}
	else
	{
		t[now].rson=++tot;
		t[now].lson=t[prev].lson;
		build(t[now].rson,t[prev].rson,mid+1,r,x,fuhao);
	}
	update(now);
}
long long query(int now,int l,int r,int k)
{
	if(l==r)
	{
		return k*l;
	}
	if(t[now].sum<=k){
	return t[now].ans;
	}
	int mid=l+r>>1;
	long long ret=0;
	if(k<=t[t[now].lson].sum)
	{
		ret+=query(t[now].lson,l,mid,k);
	}
	else
		ret+=query(t[now].rson,mid+1,r,k-t[t[now].lson].sum)+t[t[now].lson].ans;
	return ret;
}
int top;
int pointer;
int shijian[100001];
int main()
{
	int n,m;
	R(m);
	R(n);
	int x,y,z;
	for(int i=1;i<=m;++i)
	{
		R(x);
		R(y);
		R(z);
		num[++task].pos=x;
		num[task].zhi=z;
		if(y+1<=n)
		{num[++task].pos=y+1;
		num[task].zhi=-z;}
	}
	sort(num+1,num+task+1,cmp1);
	pointer=0;
	int cnt=0;
	for(int i=1;i<=task&&pointer<=n;++i)
	{
		root[i]=++tot;
		build(root[i],root[i-1],1,mp,abs(num[i].zhi),num[i].zhi>=0?1:-1);
		shijian[num[i].pos]=i;
	}
	for(int i=1;i<=n;++i)
	{
		if(!shijian[i])
		shijian[i]=shijian[i-1];
	}
	int w,k;
	long long pre=1;
	for(int i=1;i<=n;++i)
	{
		R(x);
		R(y);
		R(z);
		R(w);
		k=1+(y*pre+z)%w;
		pre=query(root[shijian[x]],1,mp,k);
		cout<<pre<<"\n";
	}

	return 0;
}
