
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

int n,a[200005],q[200005];
int main(){
	scanf("%d",&n); int i;
	for (i=1; i<=n; i++){
		scanf("%d",&a[i]); a[i+n]=a[i];
	}
	int tmp=0,mx=0,t,now=1;
	for (i=1; i<=n+n; i++){
		if (tmp<0){ now=i; tmp=a[i]-1; }else tmp+=a[i]-1;
		if (tmp>mx){ mx=tmp; t=now; }
	}
	int head=1,tail=0; ll ans=0;
	for (i=t; i<=t+n-1; i++){
		while (a[i]--) q[++tail]=i;
		ans+=(ll)(i-q[head])*(i-q[head]); head++;
	}
	printf("%lld\n",ans);
	return 0;
}
