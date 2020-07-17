
#include <bits/stdc++.h>
#include <tr1/unordered_map>
using namespace std;
tr1::unordered_map<long long , long long> s1, s2;
inline void R (int &v) {
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
const int N = 1664510;
int prime[N + 50], phi[N + 50], cnt;
int miu[N + 50];
long long  sum1[N + 50], sum2[N + 50];
bool heshu[N + 50];
inline void init() {
	phi[1] = miu[1] = 1;
	for (int i = 2; i <= N; ++i) {
		if (!heshu[i]) prime[++cnt] = i, phi[i] = i - 1, miu[i] = -1;;
		for (int j = 1; j <= cnt && prime[j] * i <= N; ++j) {
			heshu[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				miu[i * prime[j]] = 0;
				break;
			} else phi[i * prime[j]] = phi[i] * phi[prime[j]], miu[i * prime[j]] = -miu[i];
		}
	}
//	for(int i = 1; i <= 10; ++i) {
//		printf("phi[%d] = %d\n", i, phi[i]);
//	}
	for (int i = 1; i <= N; ++i) {
		sum1[i] = sum1[i - 1] + phi[i];
		sum2[i] = sum2[i - 1] + miu[i];
	}
}
#define pll pair<long long, long long>
#define mk make_pair
inline pll gets(long long x) {
	if (x <= N) {
		return mk(sum1[x], sum2[x]);
	} else {
		if (s1.find(x) != s1.end() && s2.find(x) != s2.end()) {
			return mk(s1[x], s2[x]);
		} else {
			long long j, ans1 = x * (x + 1) / 2, ans2 = 1;
			pll temp;
			for (long long i = 2; i <= x; i = j + 1) {
				j = x / (x / i);
				temp = gets(x / i);
				ans1 -= (j - i + 1) * temp.first;
				ans2 -= (j - i + 1) * temp.second;
			}
			return mk(s1[x] = ans1, s2[x] = ans2);
		}
	}
}
int main () {
	init();
	int T;
	R(T);
	int x;
	while (T--) {
		R(x);
		pll temp = gets(x);
		printf("%lld %lld\n", temp.first, temp.second);
	}
	return 0;
}
