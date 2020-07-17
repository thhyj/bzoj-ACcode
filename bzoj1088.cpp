
#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <ctime>
using namespace std;
inline void R(int &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
	   ch = getchar();
	   if(ch == '-')
		   p = 1;
	}while(!isdigit(ch));
	while(isdigit(ch)) {
		v = (v + (v << 2) <<1) + (ch ^ '0');
		ch = getchar();
	}
	if(p)
		 v = -v;
}
int dp[100005][2][2][2];
int main() {
	int n;
	R(n);
	int x;
	R(x);
	if(x==0)
	dp[1][0][0][0]=1;
	if(x==1) 
	dp[1][0][1][0]=dp[1][0][0][1]=1;
	if(x==2)
	dp[1][0][1][1]=1;
	for(int i=2;i<n;++i)  {
		R(x);
		if(x==0) {
			dp[i][0][0][0]=dp[i-1][0][0][0]+dp[i-1][1][0][0];
		} 
		if(x==1) {
			dp[i][1][0][0]=dp[i-1][0][1][0]+dp[i-1][1][1][0];
			dp[i][0][1][0]=dp[i-1][0][0][1]+dp[i-1][1][0][1];
			dp[i][0][0][1]=dp[i-1][0][0][0]+dp[i-1][1][0][0];
		}
		if(x==2) {
			dp[i][1][1][0]=dp[i-1][0][1][1]+dp[i-1][1][1][1];
			dp[i][1][0][1]=dp[i-1][0][1][0]+dp[i-1][1][1][0];
			dp[i][0][1][1]=dp[i-1][0][0][1]+dp[i-1][1][0][1];
		}
		if(x==3) {
			dp[i][1][1][1]=dp[i-1][0][1][1]+dp[i-1][1][1][1];
		}
	}
	R(x);
	if(x==0) dp[n][0][0][0]=dp[n-1][0][0][0]+dp[n-1][1][0][0];
	if(x==1) {
			dp[n][1][0][0]=dp[n-1][0][1][0]+dp[n-1][1][1][0];
			dp[n][0][1][0]=dp[n-1][0][0][1]+dp[n-1][1][0][1];
		}
	if(x==2) {
			dp[n][1][1][0]=dp[n-1][0][1][1]+dp[n-1][1][1][1];
	}
	cout<<dp[n][0][0][0]+dp[n][0][0][1]+dp[n][0][1][0]+dp[n][1][0][0]+dp[n][0][1][1]+dp[n][1][0][1]+dp[n][1][1][0]+dp[n][1][1][1];
	return 0;
} 
