
#include <bits/stdc++.h>
#include <tr1/unordered_map>
using namespace std;
tr1::unordered_map<long long , long long>s;
const int N = 2000000;
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
inline long long gets(long long x) {
	if (x <= N) {
		return sum[x];
	} else {
		if (s.find(x) != s.end()) {
			return s[x];
		} else {
			long long ret = 1, j;
			for (long long i = 2; i <= x; i = j + 1) {
				j = x / (x / i);
				ret -= (j - i + 1) * gets(x / i);
			}
			return s[x] = ret;
		}
	}
}
const int mod = 1000000007;
long long cal2(long long n)
{
	long long ans = 0 , i , last;
	for (i = 1 ; i <= n ; i = last + 1) last = n / (n / i) , ans = (ans + n / i * (last - i + 1)) % mod;
	return ans * ans % mod;
}
int main () {
	int n;
	init();
	scanf("%d", &n);
	long long j;
	long long ans = 0;
	for (long long i = 1; i <= n; i = j + 1) {
		j = n / (n / i);
		ans = (ans + (gets(j) - gets(i - 1)) % mod * cal2(n / i)) % mod;
	}
	cout << (ans % mod + mod) % mod;
	return 0;
}
