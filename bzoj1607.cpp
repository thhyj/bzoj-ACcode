
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
int ans[1000005];
int a[1000005];
int tong[1000005];
bool vis[1000005];
int main () {
	R(n);
	int x;
	for (int i = 1; i <= n; ++i) {
		R(a[i]);
		tong[a[i]]++;
	}
	for (int i = 1; i <= n; ++i) {
		if (vis[a[i]] == 0) {
		//	ans[a[i]] = 0;
			vis[a[i]] = 1;
			for (int j = a[i] ; j <= 1000000; j += a[i]) {
				ans[j] += tong[a[i]];
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		printf("%d\n", ans[a[i]]- 1);
	}
}
