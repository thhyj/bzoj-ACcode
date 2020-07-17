
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
struct niu {
	int l, r;
} p[100005], temp[100005];
inline bool cmp(const niu&a, const niu &b) {
	return a.l < b.l;
}
int main () {
	R(n);
	for (int i = 1; i <= n; ++i) {
		R(p[i].l), R(p[i].r);
	}
	int mid , l = 1, r = n + 1;
	while (l < r - 1) {
		mid = l + r >> 1;
		for (int i = 1; i <= mid; ++i) {
			temp[i] = p[i];
		}
		sort(temp + 1, temp + mid + 1, cmp);
		int ma = 0;
		bool pd = 1;
		for (int i = 1; i <= mid; ++i) {
			if (temp[i].r <= ma) {
				pd = 0;
				break;
			}
			ma = temp[i].r;
		}
		if (!pd) r = mid;
		else l = mid;
	}
	printf("%d\n", l);
}
