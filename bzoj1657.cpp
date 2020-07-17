
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
int n, st[50005], top, a[50005], b[50005], yin[50005];
int main() {
	int n;
	R(n);
	for (int i = 1; i <= n; ++i) {
		R(a[i]), R(b[i]);
		while (top && a[st[top]] < a[i]) {
			yin[i] += b[st[top]];
			top--;
		}
		st[++top] = i;
	}
	top = 0;
	for (int i = n; i ; --i) {
		while (top && a[st[top]] < a[i]) {
			yin[i] += b[st[top]];
			top--;
		}
		st[++top] = i;
	}
	int mx = 0;
	for (int i = 1; i <= n; ++i) {
		mx = max(yin[i], mx);
	}
	printf("%d\n", mx);
}
