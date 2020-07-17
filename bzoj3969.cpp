
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
int n, k;
int a[1000005];
int tot;
int main () {
	R(n), R(k);
	tot = 2 * n * k;
	for (int i = 1; i <= tot; ++i) {
		R(a[i]);
	}
	sort(a + 1, a + tot + 1);
	reverse(a + 1, a + tot + 1);
	int l = -1, r = 1000000000;
	int mid;
	int cnt = 0, ans = 0;
	while (l < r - 1) {
		mid = l + r >> 1;
		cnt = 0;
		ans = 0;
		for (int i = 1; i < tot; ++i) {
			if (a[i] - a[i + 1] <= mid && cnt >= 2 * (k - 1)) {
				cnt -=	2 * (k - 1);
				++ans;
				if (ans == n) {
					break;
				}
				i = i + 1;
				continue;
			} else {
				++cnt;
			}
		}
		if (ans >= n) r = mid;
		else l = mid;
	}
	printf("%d\n", r);
	return 0;
}
