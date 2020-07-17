
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <cstdlib>
using namespace std;
inline void R(int &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
		ch = getchar();
		if (ch == '-') {
			p = 1;
		}
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = (v + (v << 2) << 1) + (ch^'0');
		ch = getchar();
	}
	if (p)v = -v;
}
int ma[1005][1005];
int dp[1005][1005];
int main() {
	//freopen("in.in","r",stdin);
	int T;
	int n,m;
	R(T);
	for(int o=1;o<=T;++o) {
		memset(ma,0,sizeof(ma));
		memset(dp,0,sizeof(dp));
		R(n),R(m);								//n hang m lie
		for(int i=1;i<=n;++i) {
			for(int j=1;j<=m;++j) {
				R(ma[i][j]);					//j heng i zong
			}
		}
		for(int i=1;i<=n;i++)
			for(int j=m;j;j--)
				dp[i][j]=max(dp[i-1][j+1]+ma[i][j],max(dp[i-1][j],dp[i][j+1]));
		cout<<dp[n][1]<<'\n';
	}
	return 0;
}
