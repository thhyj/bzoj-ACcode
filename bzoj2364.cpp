
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
inline void R(long long &v) {
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
long long h[1000005], st[1000005], top, sum[1000005], pow_sum[1000005], f[1000005];
int n;
long long C;
const long long inf = 1e4;
inline long long calc(long long a, long long b, long long c, long long l, long long r) {
	double t = -((double)b / (2 *a));
	long long x;
//	printf("x=%I64d\n",x);
	if (t >= l && t <= r) x = round(t);
	else if (t > r) x = r;
	else if (t < l) x = l;
	return a * x * x + b * x + c;
}
inline long long cal(long long l, long long r, long long mi) {
	if (l + 1 == r) return (l == 0 || r == n + 1) ? 0 : abs(h[r] - h[l]) * C;
	long long a = r - l - 1, b = -2 * (sum[r - 1] - sum[l]), c = pow_sum[r - 1] - pow_sum[l], mx = min(h[l], h[r]);
	if (l != 0) b -= C, c += C * h[l];
	if (r != n + 1) b -= C, c += C * h[r];
	//cerr<<"a="<<a<<" b="<<b<<" c="<<c<<'\n';
	//printf("a=%I64d, b= %I64d, c= %I64d\n",a,b,c);
	return calc(a, b, c, mi, mx);
}
int main() {
	R(n), R(C);
	h[0] = h[n + 1] = inf;
	for (int i = 1; i <= n; ++i) {
		R(h[i]);
	}
	sum[0] = pow_sum[0] = h[0];
	for (int i = 1; i <= n+1; ++i) {
		sum[i] = sum[i - 1] + h[i];
		pow_sum[i] = pow_sum[i - 1] + h[i] * h[i];
//		cout<<sum[i]<<' '<<pow_sum[i]<<'\n';
	}
	int last = 0;
	st[++top] = 0;
	for (int i = 1; i <= n + 1; ++i) {
		f[i] = 1e18;
		last = 0;
		while (top && h[st[top]] < h[i]) {
			f[i] = min(f[i], f[st[top]] + cal(st[top], i, last));
			last = h[st[top--]];
		}
		f[i] = min(f[i], f[st[top]] + cal(st[top], i, last));
		st[++top] = i;
	}
	printf("%lld",f[n+1]);
	return 0;
}
