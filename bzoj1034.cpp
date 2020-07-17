
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
int n;
inline int solve(const int *a, const int *b) {
	int l1 = 1, r1 = n, l2 = 1, r2 = n, ret = 0;
	while (l1 <= r1 && l2 <= r2)
	{
		if (a[l1] > b[l2]) {ret += 2; l1++; l2++;}
		else if (a[r1] > b[r2]) {ret += 2; r1--; r2--;}
		else {ret += (a[l1] == b[r2]); l1++; r2--;}
	}
	return ret;

}
int a[100005], b[100005];
bool vis[100005];
int main () {
	R(n);
	for (int i = 1; i <= n; ++i) {
		R(a[i]);
	}
	for (int i = 1; i <= n; ++i) {
		R(b[i]);
	}
	sort(a + 1, a + n + 1), sort(b + 1, b + n + 1);
	cout << solve(a, b) << ' ' << 2 * n - solve(b, a);
	return 0;
}
