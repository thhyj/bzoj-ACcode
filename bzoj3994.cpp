
#include <bits/stdc++.h>
#include <tr1/unordered_map>
using namespace std;
tr1::unordered_map<long long , long long>s;
long long s1[50005];
inline void R (int &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
		ch = getchar();
		if (ch == '-') p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = (v + (v << 2) << 1) + (ch ^ '0');
		ch = getchar();
	}
	if (p) v = -v;
}
const int N = 50000;
int cnt, prime[N + 50], miu[N + 50];
int sum[N + 50];
bool heshu[N + 50];
inline void init() {
	miu[1] = 1;
	for (int i = 2;  i <= N; ++i) {
		if (!heshu[i]) prime[++cnt] = i, miu[i] = -1;
		for (int j = 1 ; j <= cnt && prime[j] * i <= N; ++j) {
			heshu[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				miu[i * prime[j]] = 0;
				break;
			} else miu[i * prime[j]] = -miu[i];
		}
	}
	for (int i = 1; i <= N; ++i) {
		sum[i] = sum[i - 1] + miu[i];
	}
}
int T;
long long cal2(int n)
{
	if(s1[n] != -1) return s1[n];
	long long ans = 0 , i , last;
	for (i = 1 ; i <= n ; i = last + 1) last = n / (n / i) , ans = (ans + (long long)n / i * (last - i + 1));
	return s1[n] = ans;
}
int main () {
	memset(s1, -1, sizeof(s1));
	int n, m;
	init();
	R(T);
	while (T--) {
		R(n), R(m);
		int j;
		long long ans = 0;
		if(n > m) swap(n, m);
		for (int i = 1; i <= n; i = j + 1) {
			j = min(n / (n / i), m / (m / i));
			ans = (ans + (long long)(sum[j] - sum[i - 1]) * cal2(n / i) * cal2(m / i));
		}
		printf("%lld\n", ans);
	}
	return 0;
}
