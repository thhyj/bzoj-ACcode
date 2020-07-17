
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
struct e {
	int fr, to, length;
} bian[1000005];
int n, tot;
inline bool cmp(const e &a, const e &b) {
	return a.length < b.length;
}
int fa[1005];
inline int getfather(int x) {
	return (x == fa[x]) ? (x) : (fa[x] =  getfather(fa[x]));
}
int main () {
//	freopen("in.in", "r", stdin);
	R(n);
	int x;
	for (int i = 1; i <= n; ++i) {
		R(x);
		bian[++tot].to = i, bian[tot].length = x;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			R(x);
			if (i == j) continue;
			bian[++tot].fr = i, bian[tot].to = j, bian[tot].length = x;
		}
	}
	sort(bian + 1, bian + tot + 1, cmp);

	for (int i = 0; i <= n; ++i) {
		fa[i] = i;
	}
	int y, fx, fy, ans = 0;
	for (int i = 1,cnt = 1; i <= tot;++i) {
		x = bian[i].fr, y = bian[i].to;
		fx = getfather(x), fy = getfather(y);
	//	printf("x = %d, y = %d,fx = %d, fy = %d, bian[%d].length = %d\n", x, y,fx, fy, i, bian[i].length);
		if (fx != fy) {
			fa[fx] = fy;
			ans += bian[i].length;
			++cnt;
		}
	}
	printf("%d\n", ans);
	return 0;
}
