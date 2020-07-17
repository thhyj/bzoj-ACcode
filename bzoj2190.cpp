
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
int n;
int prime[40005], phi[40005];
int tot;
bool heshu[40005];
inline void init() {
	phi[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!heshu[i]) prime[++tot] = i, phi[i] = i - 1;
		for (int j = 1; j <= tot && i * prime[j] <= n; ++j) {
			heshu[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = prime[j] *  phi[i];
				break;
			} else {
				phi[i * prime[j]] = (prime[j] - 1) * phi[i];
			}
		}
	}
}
long long ans = 0;
int main () {
	R(n);
	init();
//	for(int i = 1; i <= 10; ++i) {
//		printf("phi[%d] = %d\n", i, phi[i]);
//	}
	for (int i = 1; i <= n - 1; ++i) {
		ans += phi[i];
	}
	cout << ans * 2 + 1;
	return 0;
}
