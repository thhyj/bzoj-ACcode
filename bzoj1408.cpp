
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
int k;
int now;
const int mod = 10000;
inline int ksm(int x, int y) {
	int ret =  1;
	while (y) {
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}
int p[100005];
int main () {
	now = 1;
	R(k);
	int cnt, m = 1;
	for (int i = 1; i <= k; ++i) {
		R(p[i]);
		R(cnt);
		m = m * ksm(p[i], cnt) % mod;
	}
	int ans1 = 1, ans2 = 0, temp1, temp2;
	for (int i = 1; i <= k ; ++i) {
		if (p[i] == 2) continue;
		temp1 = (ans1 + ans2 * (p[i] - 1)) % mod;
		temp2 = (ans2 + ans1 * (p[i] - 1)) % mod;
		ans1 = temp1, ans2 = temp2;
	}
	ans1--;
	int ans3 = ((m - 1) - ans1 - ans2 + mod + mod + mod ) % mod;
	printf("%d\n%d\n%d\n", ans1, ans2, ans3 );

}
