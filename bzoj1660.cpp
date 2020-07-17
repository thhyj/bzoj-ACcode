
#include <bits/stdc++.h>
using namespace std;
inline void R(int &v) {
	static char ch;
	v = 0;
	bool p = 0 ;
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
int n, st[80005], top;
int main() {
	int n;
	R(n);
	int x;
	long long t = 0, ans = 0;
	for (int i = 1; i <= n; ++i) {
		R(x);
		t = 0;
		while (top && x >= st[top]) {
			//ans += t;
			--top;
			++t;
		}
		ans += top;
		st[++top] = x;
	}
	printf("%lld\n", ans);
}
