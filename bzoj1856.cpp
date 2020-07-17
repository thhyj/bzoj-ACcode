
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
int zong;
int n, m;
const int mod = 20100403;
inline int ksm(int x, int y) {
	int ret = 1;
	while (y) {
		if (y & 1) ret = (long long)ret * x % mod;
		x = (long long)x * x % mod;
		y >>= 1;
	}
	return ret;
}
int jiecheng[2000005];
inline int C(int a, int b) {
	return ((long long) jiecheng[a] * ksm(jiecheng[b], mod - 2) % mod) * ksm(jiecheng[a - b], mod - 2) % mod;
}
int main() {
	R(n), R(m);
	jiecheng[0] = 1;
	for (int i = 1; i <= n + m; ++i) jiecheng[i] = (long long)jiecheng[i - 1] * i % mod;
	printf("%d\n", (C(n + m, m) - C(n + m, m - 1) + mod) % mod); 
}
