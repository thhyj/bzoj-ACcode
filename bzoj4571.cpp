
#include <iostream>
#include <cstring>
#include <ctime>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstdlib>
using namespace std;
const int M=100000;
inline void read(int &v){
	static char ch;
	v=0;
	bool p=0;
	do {
		ch=getchar();
		if(ch=='-')
			p=1;
	}while(!isdigit(ch));
	while(isdigit(ch)) {
		v=(v+(v<<2)<<1)+(ch^48);
		ch=getchar();
	}
	if(p)
		v=-v;
}
int a[200005];
int root[200005];
int tot;
struct node{
	int ls,rs,cnt;
}tr[8000005];
inline void build(int prev,int now,int l,int r,int x){
	tr[now].cnt=tr[prev].cnt+1;
	if(l==r){
		return;
	}
	int mid=l+r>>1;
	if(x<=mid)
	{
		tr[now].rs=tr[prev].rs;
		tr[now].ls=++tot;
		build(tr[prev].ls,tr[now].ls,l,mid,x);
	}
	else{
		tr[now].ls=tr[prev].ls;
		tr[now].rs=++tot;
		build(tr[prev].rs,tr[now].rs,mid+1,r,x);
	}
}
inline bool query(int prev, int now, int l,int r,int L,int R){
	if(!(tr[now].cnt-tr[prev].cnt)){
		return 0;
	}
	if(l>=L&&r<=R) return 1;
	int mid=l+r>>1;
	int ret=0;
	if(L<=mid)ret|=query(tr[prev].ls,tr[now].ls,l,mid,L,R);
	if(R>mid) ret|=query(tr[prev].rs,tr[now].rs,mid+1,r,L,R);
	return ret;
}
int main() {
	//freopen("in.in","r",stdin);
	int n,m;
	read(n);
	read(m);
	for(int i=1;i<=n;++i){
		read(a[i]);
	}
	for(int i=1;i<=n;++i) {
		root[i]=++tot;
		build(root[i-1],root[i],0,M,a[i]);
	}
	int l,r,b,x;
	int s[30],t;
	int L,R,mid;
	int ans=0;
	for(int i=1;i<=m;++i){
		ans=0;
		//R(b);
		read(b),read(x),read(l),read(r);
		t=b;
		L=0,R=(1<<20)-1;
		for(int j=20;j>=1;--j) {
			s[j]=t&1;
			t>>=1;
		}
		for(int j=1;j<=20;++j) {
			mid=L+R>>1;
			if(!s[j])
			{if(query(root[l-1],root[r],0,M,mid+1-x,R-x)){
				L=mid+1;
			}
			else{
				R=mid;
			}}
			else{
				if(query(root[l-1],root[r],0,M,L-x,mid-x)){
				R=mid;
			}
			else{
				L=mid+1;
			}
		}
		}
		cout<<(b^L)<<'\n';
	}
	return 0;
}
