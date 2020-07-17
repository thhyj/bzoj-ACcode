
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
int a[1000005], b[1000005], n, ans, q[1000005], q1[1000005];
int main() {
//	freopen("in.in","r",stdin);
//	freopen("out.out","w",stdout);
	R(n);
	for (int i = 1; i <= n; ++i) {
		R(a[i]); R(b[i]);
	}
	int l = 1, r = 0, minl = 1;
	bool pd = 0;
	for (int i = 1; i <= n; ++i) {
		pd = 0;
		while (a[q[l]] > b[i] && l <= r) {++l;}
		if (l <= r) ans = max(ans, i - q[l] + 1);
		int t = i;
		while (l <= r && a[q[r]] <= a[i]) t = q[r--];
		a[t] = a[i];q[++r] = t;
		q[++r] = i;
	}
	printf("%d\n", ans);
}
