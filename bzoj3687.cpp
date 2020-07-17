
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
int n;
int a[1005];
bitset<2000010>f;
int main () {
	scanf("%d", &n);
	f[0] = 1;
	int x;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &x);
		f ^= f << x;
	}
	int ans = 0;
	for (int i = 1; i <= 2000000; ++i) {
		if (f.test(i)) {
			ans ^= i;
		}
	}
	cout << ans << '\n';
}
