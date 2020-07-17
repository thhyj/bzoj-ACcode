
#include <bits/stdc++.h>
using namespace std;
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
struct node {
	long long x, y;
	double slop;
	node(long long x, long long y): x(x), y(y) {}
	node() {}
};
inline long long operator * (const node &a, const node &b) {
	return a.x * b.y - a.y * b.x;
}
inline node operator -(const node &a, const node &b) {
	return node (a.x - b.x, a.y - b.y);
}
long long n;
node p[100005];
inline bool cmp(const node &a, const node &b) {
	return a.slop < b.slop;
}
node q[1000005];
int main () {
	R(n);
	for (long long i = 1; i <= n; ++i) {
		R(p[i].x), R(p[i].y);
		p[i].slop = atan2(p[i].y, p[i].x);
	}
	node o(0, 0);
	sort(p + 1, p + n + 1, cmp);
	long long l = 1, r = 0;
	for (long long i = 2; i <= n; ++i) {
		q[++r] = p[i];
	}
	long long mi = 0;
	for (long long i = 1; i <= n; ++i) {
		while (l <= r && p[i] * q[l] > 0) ++l;
		mi += (r - l + 1) * (r - l) / 2;
		q[++r] = p[i];
	}
	long long ans = (long long) n * (n - 1) * (n - 2) / 6 - mi;
	printf("%lld\n", ans);
}
