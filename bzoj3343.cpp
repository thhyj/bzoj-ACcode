
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
int n, q;
int siz;
int bl[1000005], st[1000005], ed[1000005], add[1000005];
struct node {
	int x, id;
} a[1000005];
inline bool operator < (const node &a , const node &b) {
	return a.x < b.x;
}
inline bool cmp(const node &a , const node &b) {
	return a.x < b.x;
}
int main() {
	R(n); R(q);
	siz = sqrt(n * log2(n));
	memset(st, 127, sizeof(st));
	for (int i = 1; i <= n; ++i) {
		R(a[i].x); a[i].id = i;
		bl[i] = i / siz + 1;
		st[bl[i]] = min(st[bl[i]], i);
		ed[bl[i]] = max(ed[bl[i]], i);
	}
	int tot = n / siz + 1;
	for (int i = 1; i <= tot; ++i) {
		sort(a + st[i], a + ed[i] + 1, cmp);
	}
	char ch;
	int l, r, c;
	int l1, r1;
	int ans = 0;
	for (int i = 1; i <= q; ++i) {
		do {
			ch = getchar();
		} while (!isupper(ch));
		int temp;
		switch (ch) {
		case 'A' :
			R(l), R(r), R(c);
			ans = 0;
			l1 = bl[l], r1 = bl[r];
			if (l1 == r1) {
				for (int i = st[l1]; i <= ed[r1]; ++i) {
					if (a[i].id >= l && a[i].id <= r && a[i].x + add[l1] >= c) {
						++ans;
					}
				}
				printf("%d\n", ans);
			} else {
				for (int i = l1 + 1; i <=  r1 - 1; ++i) {
					temp = lower_bound(a + st[i], a + ed[i] + 1, (node){c - add[i], 0}) - a;
					//if(temp == ed[i] + 1) temp = ed[i];
					ans += ed[i] - temp + 1;
				}
				for (int i = st[l1]; i <= ed[l1]; ++i) {
					if (a[i].id >= l && a[i].id <= r && a[i].x + add[l1] >= c) {
						++ans;
					}
				}
				for (int i = st[r1]; i <= ed[r1]; ++i) {
					if (a[i].id >= l && a[i].id <= r && a[i].x + add[r1] >= c) {
						++ans;
					}
				}
				printf("%d\n", ans);
			}
			break;
		case 'M':
			R(l), R(r), R(c);
			l1 = bl[l], r1 = bl[r];
			if (l1 == r1) {
				for (int i = st[l1]; i <= ed[r1]; ++i) {
					if (a[i].id >= l && a[i].id <= r) {
						a[i].x += c;
					}
				}
				sort(a + st[l1], a + ed[r1] + 1, cmp);
			} else {
				for (int i = l1 + 1; i <=  r1 - 1; ++i) {
					add[i] += c;
				}
				for (int i = st[l1]; i <= ed[l1]; ++i) {
					if (a[i].id >= l && a[i].id <= r) {
						a[i].x += c;
					}
				}
				sort(a + st[l1], a + ed[l1] + 1, cmp);
				for (int i = st[r1]; i <= ed[r1]; ++i) {
					if (a[i].id >= l && a[i].id <= r) {
						a[i].x += c;
					}
				}
				sort(a + st[r1], a + ed[r1] + 1, cmp);
			}
		}
	}
	return 0;
}
