
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
int n, m;
bitset<1005> ma[1005];
int main() {
	R(n), R(m);
	int x, y;
	for (register int i = 1; i <= m; ++i) {
		R(x), R(y);
		ma[x][y] = 1;
	}
	for (register int k = 1; k <= n; ++k) {
		for (register int i = 1; i <= n; ++i) {
			if (ma[i].test(k))
					ma[i] |= ma[k];
		}
	}
	int ans = 0;
	for (register int i = 1; i <= n; ++i) {
		for (register int j = i + 1; j <= n; ++j) {
			if ((!ma[i].test(j)) && (!ma[j].test(i))) {
				++ans;
			}
		}
	}
	printf("%d\n", ans);
}
