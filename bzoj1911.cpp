
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
int n, x[1000005];
int s[1000005];
long double a, b, c;
long long dp[1000005];
inline long double getslope(int j, int k) {
	return (long double)((long double)dp[j] + (long double)s[j] * (a * s[j] - b) - dp[k] - (long double)s[k] * (a * s[k] - b)) / (long double)(2 * a * (s[j] - s[k]));
}
int q[1000005];
int head, tail;
int main () {
//	freopen("in.in","r",stdin);
	R(n);
	int t1, t2, t3;
	R(t1), R(t2), R(t3);
	a = t1, b = t2, c = t3;
	for (int i = 1; i <= n; ++i) {
		R(x[i]);
		s[i] = s[i - 1] + x[i];
	}
	head = 1;
	//dp[1] = (long long)a * x[1] * x[1] + (long long)b * x[1] + c;
	//q[++tail] = 1;
	q[++tail] = 0;
	for (int i = 1; i <= n; ++i) {
		while (head < tail && getslope(q[head], q[head + 1]) < s[i]) ++head;
		dp[i] = dp[q[head]] + (long long)a * (s[i] - s[q[head]]) * (s[i] - s[q[head]]) + (long long)b * (s[i] - s[q[head]]) + c;
		while (head < tail && getslope(q[tail - 1], q[tail]) > getslope(q[tail], i)) --tail;
		q[++tail] = i;
	}
	cout << dp[n];
	return 0;
}
