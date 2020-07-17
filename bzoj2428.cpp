
#include <bits/stdc++.h>
using namespace std;
int n,m,sum[25],bl[25],a[25];
double minans;
double aver;
inline void R(int &v) {
	static char ch;
	v=0;
	bool p=0;
	do {
		ch=getchar();
		if(ch=='-') {
			p=1;
		}
	} while(!isdigit(ch));
	while(isdigit(ch)) {
		v=(v+(v<<2)<<1)+(ch^'0');
		ch=getchar();
	}
	if(p) v=-v;
}
inline void sa() {
	memset(sum,0,sizeof(sum));
	double ans=0,T=10000;
	for(int i=1;i<=n;++i) {
		bl[i]=rand()%m+1;
		sum[bl[i]]+=a[i];
	}
	for(int i=1;i<=m;++i) {
		ans+=(sum[i]-aver)*(sum[i]-aver);
	}
	int t,x,y;
	double temp;
	while(T>0.1) {
		T*=0.9;
		t=rand()%n+1,x=bl[t];y=rand()%m+1;
		if(x==y) continue;
		temp=ans;
		ans-=(sum[x]-aver)*(sum[x]-aver);
		ans-=(sum[y]-aver)*(sum[y]-aver);
		sum[x]-=a[t],sum[y]+=a[t];
		ans+=(sum[x]-aver)*(sum[x]-aver);
		ans+=(sum[y]-aver)*(sum[y]-aver);
		if(ans<temp) {
			bl[t]=y;
		} else {
			if(T>rand()%10000) {
				bl[t]=y;
			} else {
				sum[x]+=a[t],sum[y]-=a[t];
				ans=temp;
			}
		}
	}
	minans=min(minans,ans);
}
int main () {
	R(n),R(m);
	srand(233);
	for(int i=1;i<=n;++i) {
		R(a[i]);
		aver+=a[i];
	}
	aver/=(double)m;
	minans=1e30;
	for(int i=1;i<=50000;++i) {
		sa();
	//	cout<<minans<<'\n';
	}
	printf("%0.2f",sqrt(minans/m));
	return 0;
}
