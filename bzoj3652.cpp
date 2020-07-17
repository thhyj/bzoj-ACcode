
#include <bits/stdc++.h>
using namespace std;
long long n;
double p;
double ans1, ans2, pi[65], ans;
long long pow1[65];
int bit[65], cnt;
long double f[65][2][2], g[65][2][2];
int main () {
	cin >> n;
	cin >> p;
	pow1[0] = 1;
	for (int i = 1; i <= 62; ++i) {
		pow1[i] = pow1[i - 1] * 2;
	}
	int up = log2(n);
	cout << setiosflags(ios::fixed) << setprecision(6);
//	cout<<"up = "<<up<<'\n';
	for (long long i = 0; i <= up; ++i) {
		pi[i] = ((double)(n / pow1[i + 1]) * pow1[i] + (double)max(n % pow1[i + 1] - pow1[i], 0ll)) / n;
//		printf("pi[%d] = ",i);
		//	cout<< pi[i]<<'\n';
	}
	for (int i = 0; i <= up; ++i) {
		ans1 += 2 * pi[i] * (1 - pi[i]) * pow1[i];
	}
	long long t = n - 1;
	for (; t; t >>= 1)bit[++cnt] = t & 1;
	f[cnt][0][1] = f[cnt][1][0] = pow1[cnt - 1];
	g[cnt][0][1] = g[cnt][1][0] = 1;
	int nxtj, nxtk;
	long long nxtans;
	for (int i  = cnt ; i ; --i) {
		for (int j = 0 ; j < 2; ++j) {
			for (int k = 0; k < 2; ++k) {
				if (g[i][j][k])
				for (int x = 0; x < 2; ++x) {
					if (j && (x > bit[i - 1])) continue;
					nxtj = 1, nxtk = 1;
					nxtans = 0;
					if (!j || x < bit[i - 1])nxtj = 0;
					if (!k || !x < bit[i - 1]) nxtk = 0;
					if (!k || !x <= bit[i - 1]) nxtans = pow1[i - 2] ; else nxtans = 0;
					f[i - 1][nxtj][nxtk] += f[i][j][k] + g[i][j][k] * nxtans;
					g[i - 1][nxtj][nxtk] += g[i][j][k] ;
				}
			}
		}
	}
	for (int i = 0 ; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
			//	printf("f[%d][%d][%d] = %lf\n", k, i, j, (double)f[k][i][j]);
				ans2 += (long double)f[1][i][j] * p / (long double)n;
			}
		}
	ans += ans1 * (1 - p) + ans2;
	cout << ans << '\n';
}
