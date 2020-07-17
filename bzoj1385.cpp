
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
int n;
int a[10005];
int main() {
	int T;
	R(T);
	while (T--) {
		R(n);
		for (int i = 1; i <= n; ++i) {
			R(a[i]);
		}
		int temp = a[2];
		for (int i = 1; i <= n; ++i) {
			if (i == 2) continue;
			temp /= __gcd(temp, a[i]);
		}
		puts(temp == 1 ? "YES" : "NO");
	}
	return 0;
}
