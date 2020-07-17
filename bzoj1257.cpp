
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int main() {
	long long n,k;
	cin>>n>>k;
	long long j;
	long long ans=n*k,mx=min(n,k);
	for(long long l=1,r;l<=mx;l=r+1) r=min(k/(k/l),mx),ans-=((l+r)*(r-l+1)>>1)*(k/l);
	cout<<ans;
	return 0;
}
