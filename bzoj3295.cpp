
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
using namespace std;
inline void R(long long &v) {
	static char ch;
	v=0;
	bool p=0;
	do {
		ch=getchar();
		if(ch=='-')
			p=1;
	} while(!isdigit(ch));
	while(isdigit(ch)) {
		v=(v<<1)+(v<<3)+(ch^'0');
		ch=getchar();
	}
	if(p)
		v=-v;
}
long long n,m;
struct shu {
	long long zhi,ti,x;
} a[100006],temp[100005];
bool used[100005];
long long cnt;
long long ans[100005];
long long tr[100005];
inline long long lowbit (const long long & x) {
	return x&-x;
}
inline void add(long long x,long long y) {
	for(; x<=n; x+=lowbit(x)) {
		tr[x]+=y;
	}
}
inline long long ask(long long x) {
	long long res=0;
	for(; x; x-=lowbit(x)) {
		res+=tr[x];
	}
	return res;
}
void fenzhi(long long l,long long r) {
	if(l>=r)return;
	long long mid=l+r>>1;
//	cout<<"l="<<l<<" r="<<r<<'\n';
	int i,j=l,k=mid+1;
	for(i=l;i<=r;i++)
        if(a[i].ti<=mid)
            temp[j++]=a[i];
        else
            temp[k++]=a[i];
    for(i=l;i<=r;i++)
        a[i]=temp[i];
	i=l;
	for(j=mid+1; j<=r; j++) {
		for(; i<=mid&&a[i].x<a[j].x; i++)
			add(a[i].zhi,1);
		ans[a[j].ti]+=(i-l)-ask(a[j].zhi);
	}
	for(i--; i>=l; i--)
		add(a[i].zhi,-1);
	i=mid;
	for(j=r; j>mid; j--) {
		for(; i>=l&&a[i].x>a[j].x; i--)
			add(a[i].zhi,1);
		ans[a[j].ti]+=ask(a[j].zhi);
	}
	for(i++; i<=mid; i++)
		add(a[i].zhi,-1);
	fenzhi(l,mid);
	fenzhi(mid+1,r);
}
long long tong[100005];
int main() {
	R(n);
	R(m);
	for(long long i=1; i<=n; ++i)
		R(a[i].zhi),a[i].x=i;//,tong[a[i].zhi]=i;
	long long t;
	int j=0;
	for(long long i=1; i<=m; ++i) {
		R(t);
	//	a[tong[t]].ti=n-i+1;
		tong[t]=i;
		used[t]=1;
	}
	for(long long i=1; i<=n; ++i) {
		if(!used[a[i].zhi]) {
			a[i].ti=++j;
		}
		else
			a[i].ti=n-tong[a[i].zhi]+1;
	}
	fenzhi(1,n);
//	cout<<233<<'\n';
	int i;
    for(i=2;i<=n;i++)
        ans[i]+=ans[i-1];
    for(i=n;i>n-m;i--)
       cout<<ans[i]<<'\n';
	return 0;
}
