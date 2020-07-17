
#include <bits/stdc++.h>
using namespace std;
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
int T, n, m;
int miu[10000007], prime[10000007], cnt, g[10000005];
bool heshu[10000007];
inline void init(int n) {
	miu[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!heshu[i]) prime[++cnt] = i, miu[i] = -1;
		for (int j = 1; j <= cnt && prime[j] * i <= n; ++j) {
			heshu[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				miu[i * prime[j]] = 0;
				break;
			} else miu[i * prime[j]] = -miu[i];
		}
	}
	for (int i = 1; i <= cnt; ++i) {
		for (int j = prime[i], k = 1; j <= n; j += prime[i], ++k) {
			g[j] += miu[k];
		}
	}
	for (int i = 1; i <= n; ++i) {
		g[i] += g[i - 1];
	}
}
long long ans;
int main () {
	
	R(n);
	init(n);
	int j;
	ans = 0;
	for (int i = 1; i <= n; i = j + 1) {
		j = n / (n / i);
		ans += (long long)(n / i) * (long long)(n / i) * ((long long) g[j] - (long long)g[i - 1]);
	}
	cout << ans << '\n';
	return 0;
}
