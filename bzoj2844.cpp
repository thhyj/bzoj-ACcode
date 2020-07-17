
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
		v = (v + (v << 2) << 1) + (ch ^ '0');
		ch = getchar();
	}
	if (p) v = -v;
}
int a[40], c[100005];
int n;
std::vector<int> v;
inline void xianxingji() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 30; j >= 0; --j) {
			if (!(c[i] & (1 << j))) continue;
			if (a[j]) c[i] ^= a[j];
			else {
				for (int k = 0; k < j; ++k) {
					if (c[i] & (1 << k)) c[i] ^= a[k];
				}
				for (int k = j + 1; k <= 30; ++k) {
					if (a[k] & (1 << j)) a[k] ^= c[i];
				}
				a[j] = c[i];
				break;
			}
		}
	}
	v.clear();
	for (int i = 0; i <= 30; ++i) if (a[i]) v.push_back(i);
}
const int mod = 10086;
inline int getans(int x) {
	int ret = 0;
	for (int i = 0 ; i < v.size(); ++i) if (x & (1 << v[i])) ret |= 1 << i;
	return ret;
}
inline int ksm(int x, int y) {
	int ret = 1;
	while (y) {
		if (y & 1)ret =  ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}
int main() {
	R(n);
	for (int i = 1; i <= n; ++i) {
		R(c[i]);
	}
	xianxingji();
	int ans = 0;
	int x;
	R(x);
//	printf("v.size() = %d\n", v.size());
	ans = getans(x) % mod;
	//cout<<"ans = "<<ans<<'\n';
	ans = (ans * (ksm(2, n - v.size()) % mod) + 1) % mod;
	printf("%d", ans);
	return 0;
}
