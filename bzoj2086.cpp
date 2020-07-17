
#include <bits/stdc++.h>
using namespace std;
inline void R (long long &v) {
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
long long n, m;
long long a[1000005], sum[1000005], mi[1000005];
int main() {
	//freopen("problem.in", "r", stdin);
//	freopen("problem.out", "w",stdout);
	R(n), R(m);
	for (long long i = 1; i <= n; ++i) {
		R(a[i]);
	}
	long long k;
	long long len, l;
	for (long long i = 1; i < m; ++i) {
		R(k);
		sum[0] = 0;
		len = 0;
		memset(mi, 127, sizeof(mi));
		mi[0] = 0;
		for (long long j = 1; j <= n; ++j) {
			sum[j] = sum[j - 1] + a[j] - k;
			mi[j] = min(mi[j - 1], sum[j]);
		}
//		for (long long j = 1; j <= n; ++j) {
//			printf("sum[%d] = %d ", j, sum[j]);
//		}
//		puts("");
		/*for (long long j = n; j > len ; --j) {
			long long temp = (*ma.lower_bound(sum[j])).second;
			len = max(len, j - temp);
		}*/
		long long now = n;
		for (long long j = n; j; --j) {
			now = min(now, j);
			while (now >= 1 && mi[now - 1] <= sum[j]) {
				--now;
			}
			len = max(len, j - now);
		}
		printf("%d ", len);
	}
	R(k);
		sum[0] = 0;
		len = 0;
		memset(mi, 127, sizeof(mi));
		mi[0] = 0;
		for (long long j = 1; j <= n; ++j) {
			sum[j] = sum[j - 1] + a[j] - k;
			mi[j] = min(mi[j - 1], sum[j]);
		}
//		for (long long j = 1; j <= n; ++j) {
//			printf("sum[%d] = %d ", j, sum[j]);
//		}
//		puts("");
		/*for (long long j = n; j > len ; --j) {
			long long temp = (*ma.lower_bound(sum[j])).second;
			len = max(len, j - temp);
		}*/
		long long now = n;
		for (long long j = n; j; --j) {
			now = min(now, j);
			while (now >= 1 && mi[now - 1] <= sum[j]) {
				--now;
			}
			len = max(len, j - now);
		}
		printf("%d", len);
	return 0;
}
