
#include <bits/stdc++.h>
using namespace std;
inline void R(int &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
		ch = getchar();
		if (ch == '-') p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = (v + (v << 2) << 1) + (ch^'0');
		ch = getchar();
	}
	if (p) v = -v;
}
int n, m;
std::vector<int> q[1005];
inline void create(int x, int y) {
	q[x].push_back(y);
	q[y].push_back(x);
}
const int mod = 2017;
int rd[1005];
int dp[34][34][100];
int ret[34][10000];
int boom[34][10000];
int bo[10000];
int top;
int ans;
int main () {
	//freopen("cola.in", "r", stdin);
	//freopen("cola.out","w",stdout);
	R(n), R(m);
	int x, y;
	for (int i = 1; i <= m; ++i) {
		R(x), R(y);
		create(x, y);
		rd[x]++, rd[y]++;
	}
	int t;
	int temp = 1;
	R(t);
	while ((temp << 1) <= t) {
		temp = temp << 1;
		++top;
	}
	for (int j = 1; j <= n; ++j) {
		for (int i = 0; i < q[j].size(); ++i) {
			dp[j][q[j][i]][0]++;
		}
		dp[j][j][0]++;
	}
	for (int i = 1; i <= n; ++i)
		boom[i][0] = 1;
//	for (int j = 1; j <= n; ++j) {
//		for (int k = 1; k <= n; ++k) {
///			printf("dp[%d][%d][0] = %d\n", j, k, dp[j][k][0]);
///		}
//	}
//	cout<<"top="<<top<<'\n';
	for (int i = 1; i <= top; ++i) {
		for (int j = 1; j <= n; ++j) {
			boom[j][i] = boom[j][i - 1];
			for (int k = 1; k <= n; ++k) {
				boom[j][i] = (boom[j][i] + dp[j][k][i - 1] * boom[k][i - 1]) % mod;
				for (int l = 1; l <= n; ++l) {
					dp[j][l][i] = (dp[j][l][i] + dp[j][k][i - 1] * dp[k][l][i - 1]) % mod;
				}
			}
	//		printf("boom[%d][%d]=%d\n",j,i,boom[j][i]);
		}

	}
//	for (int i = 1; i <= 3; ++i) {
///		for (int j = 1; j <= n; ++j) {
//			for (int k = 1; k <= n; ++k) {
//				printf("dp[%d][%d][%d] = %d\n", j, k, i, dp[j][k][i]);
//			}
//		}
//	}
	int now = 1 << top;
//	cout << "top=" << top << " now=" << now << '\n';
	for (int i = 1; i <= n; ++i) {
		ret[i][1] = dp[1][i][top];
	}
	bo[1] = boom[1][top];
//	cout << "bo[1]=" << bo[1] << '\n';
	int cnt = 1;
	while (now < t) {
		for (int i = top; i >= 0; --i) {
			if ((1 << i) + now <= t) {
		//		cout << "i=" << i << '\n';
				++cnt;
				bo[cnt] = bo[cnt-1];
				for (int j = 1; j <= n; ++j) {
					//bo[cnt] = (bo[cnt] + )
					bo[cnt] = (bo[cnt] + ret[j][cnt-1] * boom[j][i])%mod;
					for (int k = 1; k <= n; ++k) {
						ret[k][cnt] = (ret[k][cnt] + ret[j][cnt - 1] * dp[j][k][i]) % mod;
					}
				}
				now += (1 << i);
				break;
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		ans = (ans + ret[i][cnt]) % mod;
	}
//	cout<<"ans="<<ans<<'\n';
//	cout<<"bo[cnt]="<<bo[cnt]<<'\n';
	ans+=bo[cnt];
	cout << ans%mod;
	return 0;
}
