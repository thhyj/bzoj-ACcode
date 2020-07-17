
#include <bits/stdc++.h>
#include <tr1/unordered_map>
using namespace std;
tr1::unordered_map<long long , long long> s;
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
const int N = 1587401;
int prime[N + 50], phi[N + 50], cnt;
long long  sum[N + 50];
bool heshu[N + 50];
inline void init() {
	phi[1] = 1;
	for (int i = 2; i <= N; ++i) {
		if (!heshu[i]) prime[++cnt] = i, phi[i] = i - 1;
		for (int j = 1; j <= cnt && prime[j] * i <= N; ++j) {
			heshu[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			} else phi[i * prime[j]] = phi[i] * phi[prime[j]];
		}
	}
//	for(int i = 1; i <= 10; ++i) {
//		printf("phi[%d] = %d\n", i, phi[i]);
//	}
	for (int i = 1; i <= N; ++i) {
		sum[i] = sum[i - 1] + phi[i];
	}
}
inline long long gets(long long x) {
	if (x <= N) {
		return sum[x];
	} else {
		if (s[x]) {
			return s[x];
		} else {
			long long j, ans = x * (x + 1) / 2;
			for (long long i = 2; i <= x; i = j + 1) {
				j = x / (x / i);
				ans -= (j - i + 1) * (gets(x / i));
			}
			return s[x] = ans;
		}
	}
}
int main () {
	init();
	int n;
	scanf("%d", &n);
	cout << gets(n);
	return 0;
}
