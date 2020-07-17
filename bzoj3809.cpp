
#include <bits/stdc++.h>
using namespace std;
void R (int &v) {
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
int siz;
int n, m;
int a[100005];
int l[10005], r[10005], bl[100005], bloans[10005], c[100005];
struct qu {
	int l, r, a, b, id;
} q[1000005];
inline bool cmp(const qu &a, const qu &b) {
	return bl[a.l] < bl[b.l] || (bl[a.l] == bl[b.l] && (a.r < b.r));
}
int nowl, nowr;
inline void add(int x) {
	if (!c[a[x]]) {
		bloans[bl[a[x]]]++;
	}
	++c[a[x]];
}
inline void del(int x) {
	if (c[a[x]] == 1) {
		bloans[bl[a[x]]]--;
	}
	--c[a[x]];
}
int ans[1000005];
inline int getans(int a, int b) {
	int L = bl[a], R = bl[b], ret = 0;
	if (L == R) {
		for (int i = a; i <= b ; ++i) {
			if (c[i]) ret++;
		}
		return ret;
	} else {
		for (int i = L + 1 ; i <= R - 1; ++i) {
			ret += bloans[i];
		}
		for (int i = a; i <= r[L]; ++i) {
			if (c[i]) ++ret;
		}
		for (int i = l[R]; i <= b; ++i) {
			if (c[i]) ++ret;
		}
	}
	return ret;
}
inline int solve(int l1, int r1, int a, int b) {
	while (nowr < r1) {
		add(++nowr);
	}
	while (nowr > r1) {
		del(nowr--);
	}
	while (nowl < l1) {
		del(nowl++);
	}
	while (nowl > l1) {
		add(--nowl);
	}
	return getans(a, b);
}
int main() {
	R(n), R(m);
	siz = sqrt(n);
	memset(l, 127, sizeof(l));
	for (int i = 1; i <= n; ++i) {
		R(a[i]);
		bl[i] = i / siz + 1;
		l[bl[i]] = min(l[bl[i]], i);
		r[bl[i]] = max(r[bl[i]], i);
	}
	for (int i = 1; i <= m; ++i) {
		R(q[i].l), R(q[i].r);
		R(q[i].a), R(q[i].b);
		q[i].id = i;
	}
	sort(q + 1, q + m + 1, cmp);
	nowl = 1;
	nowr = 0;
	for (int i = 1; i <= m; ++i) {
		ans[q[i].id] = solve(q[i].l, q[i].r, q[i].a, q[i].b);
	}
	for (int i = 1; i <= m; ++i) {
		printf("%d\n", ans[i]);
	}
}
