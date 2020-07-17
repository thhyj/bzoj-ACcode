
#include<bits/stdc++.h>
using namespace std;
int main () {
	int n ;
	scanf("%d",&n);
	long long ans = 0;
	for(int i = 1; i<=n;++i) {
		ans += n / i;
	}
	cout<<ans<<'\n';
}
