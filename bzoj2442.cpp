
#include <bits/stdc++.h>
using namespace std;
long long f[100005], sum[100005], q[100005];
int a[100005], l, r;
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
int n, k;
int main() {
	R(n); R(k);
	for (int i = 1; i <= n; ++i) {
		R(a[i]);
		sum[i] = sum[i - 1] + a[i];
	}
	l = 1, r = 0;
	for (int i = 0; i <= n; ++i) {
		while (l <= r && q[l] < i - k - 1) ++l;
		if (i <= k) f[i] = sum[i]; else
			f[i] = f[q[l]] + sum[i] - sum[q[l] + 1];
		while (l <= r && f[q[r]] - sum[q[r] + 1] <= f[i] - sum[i + 1]) --r;
		q[++r] = i;
	}
	printf("%lld\n", f[n]);
}
