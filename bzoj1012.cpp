
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>
using namespace std;
inline void R(int &v)
{
	static char ch;
	v=0;
	bool p=0;
	do {
		ch=getchar();
		if(ch=='-')
		{
			p=1;
		}
	}while(!isdigit(ch));
	while(isdigit(ch))
	{
		v=(v<<1)+(v<<3)+(ch^'0');
		ch=getchar();
	}
	if(p)v=-v;
}
struct node
{
	int ls,rs,ma;
}tr[800006];
int tot;
inline void update(int now)
{
	tr[now].ma=max(tr[tr[now].ls].ma,tr[tr[now].rs].ma);
 } 
void add(int now,int pos,int l,int r,int x)
{
	if(l==r)
	{
		tr[now].ma=x;
		return;
	}
	int mid=l+r>>1;

	if(pos<=mid)
	{
			if(!tr[now].ls)tr[now].ls=++tot;
			add(tr[now].ls,pos,l,mid,x);
	}
	else {
			if(!tr[now].rs)tr[now].rs=++tot;
			add(tr[now].rs,pos,mid+1,r,x);
	}
	update(now);
}
int query(int now,int ql,int qr,int l,int r)
{
	if(l>=ql&&r<=qr)
	{
		return tr[now].ma;
	}
	int mid=l +r>>1;
	int ret=0;
	if(ql<=mid)
	{
		ret=max(ret,query(tr[now].ls,ql,qr,l,mid));
	}
	if(qr>mid)
	{
		ret=max(ret,query(tr[now].rs,ql,qr,mid+1,r));
	}
	return ret;
}
int main()
{
	int m,d;
//	freopen("in.out","w",stdout);
	R(m);R(d);
	tot=1;
	//cout<<m<<'\n';
	int tail=0;
	char kind;
	int n,l,t=0;
	for(int i=1;i<=m;++i)
	{
		kind=getchar();
		R(n);
		if(kind=='A')
		{
			
			add(1,++tail,1,200000,(n+t)%d);
		}
		if(kind=='Q')
		{
			//cout<<"tail-l+1="<<tail-l+1<<" tail="<<tail<<'\n';
			t=query(1,tail-n+1,tail,1,200000);
			cout<<t<<'\n';
		}
	}
	return 0;
}
