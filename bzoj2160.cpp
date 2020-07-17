
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
int n;
long long k;
char s[1000005];
int id, mx, p[1000005];
inline void manacher() {
	for (int i = 0; i < n; ++i) {
		if (i < mx) {
			p[i] = min(p[id + id - i], mx - i + 1);
		} else p[i] = 1;
		while (i + p[i] < n && i - p[i] >= 0 && s[i + p[i]] == s[i - p[i]]) ++p[i];
		if (p[i] + i - 1 > mx) {
			mx = p[i] + i - 1;
			id = i;
		}
	}
}
long long tong[1000005];
const int mod = 19930726;
inline int ksm(int x, int y) {
	int ret = 1;
	while (y) {
		if (y & 1) ret = (long long)ret * x % mod;
		x = (long long) x * x % mod;
		y >>= 1;
	}
	return ret;
}
int main() {
	R(n), R(k);
	scanf("%s", s);
	manacher();
	for (int i = 0 ; i < n; ++i) {
		//printf("p[%d] = %d\n", i, p[i]);
		tong[p[i] * 2 - 1]++;
	}
	if (n % 2 == 0) --n;
	for (int i = n; i >= 2; i -= 2) {
		tong[i - 2] += tong[i];
	}
	int ans = 1;
	for (int i = n; i >= 0 && k; i -= 2) {
//		printf("tong[%d] = %I64d, k = %d\n", i, tong[i], k);
		ans = (long long)ans * ksm(i, min(tong[i], k)) % mod;
		k -= min(tong[i], k);
	}
	cout << ans;
	return 0;
}
