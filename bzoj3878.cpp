
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
struct shu {
	int zhi, id;
} a[100005];
struct caozuo {
	int kind, zhi;
} b[100005];
struct tree {
	int l, r;
	long long mx, mn, tagx, tagj, tagg, tagf;
} tr[400005];
int n, L1, R1;
inline bool cmp (const shu &a, const shu &b) {
	return a.zhi < b.zhi;
}
inline void build(int x, int l, int r) {
	tr[x].l = l, tr[x].r = r;
	tr[x].mx = min(a[r].zhi, R1), tr[x].mn = max(a[l].zhi, L1);
	tr[x].tagx = 1, tr[x].tagj = 0, tr[x].tagg = 0;
	tr[x].tagf = -1;
	if (l == r) return;
	int mid = l + r >> 1;
	build(x << 1, l, mid);
	build(x << 1 | 1, mid + 1, r);
}
inline void modifyf(int x, int v) {
	tr[x].tagf = tr[x].mn = tr[x].mx = v;
	tr[x].tagx = 1;
	tr[x].tagg = tr[x].tagj = 0;
}
inline void modifyj(int x, int v) {
	tr[x].tagj += v;
	tr[x].mx += v;
	tr[x].mn += v;
}
inline void modifyx(int x, int v) {
	tr[x].tagx *= v;
	tr[x].tagj *= v;
	tr[x].tagg *= v;
	tr[x].mx *= v;
	tr[x].mn *= v;
}
inline void modifyg(int x, int v) {
	tr[x].tagg += v;
	tr[x].mn += (long long)v * a[tr[x].l].zhi;
	tr[x].mx += (long long)v * a[tr[x].r].zhi;
}
inline void pushdown(int x) {
	if (tr[x].tagf > -1) {
		modifyf(x << 1, tr[x].tagf);
		modifyf(x << 1 | 1, tr[x].tagf);
		tr[x].tagf = -1;
	}
	if (tr[x].tagx > 1) {
		modifyx(x << 1, tr[x].tagx);
		modifyx(x << 1 | 1, tr[x].tagx);
		tr[x].tagx = 1;
	}
	if (tr[x].tagj) {
		modifyj(x << 1, tr[x].tagj);
		modifyj(x << 1 | 1, tr[x].tagj);
		tr[x].tagj = 0;
	}
	if (tr[x].tagg) {
		modifyg(x << 1, tr[x].tagg);
		modifyg(x << 1 | 1, tr[x].tagg);
		tr[x].tagg = 0;
	}
}
inline void updata(int x) {
	tr[x].mx = max(tr[x << 1].mx, tr[x << 1 | 1].mx);
	tr[x].mn = min(tr[x << 1].mn, tr[x << 1 | 1].mn);
}
inline void updatal(int x) {
	if (tr[x].l == tr[x].r) {
		modifyf(x, L1);
		return;
	}
	pushdown(x);
	if (tr[x << 1 | 1].mn >= L1)
		updatal(x << 1);
	else {
		modifyf(x << 1, L1);
		updatal(x << 1 | 1);
	}
	updata(x);
}
inline void updatar(int x) {
	if (tr[x].l == tr[x].r) {
		modifyf(x, R1);
		return;
	}
	pushdown(x);
	if (tr[x << 1].mx <= R1)
		updatar(x << 1 | 1);
	else {
		modifyf(x << 1 | 1, R1);
		updatar(x << 1);
	}
	updata(x);
}
int ans[100005];
inline void dfs(int x) {
	if (tr[x].l == tr[x].r) {
		ans[a[tr[x].l].id] = tr[x].mx;
		return;
	}
	pushdown(x);
	dfs(x << 1); dfs(x << 1 | 1);
}
int main () {
	R(n), R(L1), R(R1);
	char ch[105];
	for (int i = 1; i <= n; ++i) {
		scanf("%s", ch);
		R(b[i].zhi);
		switch (ch[0]) {
		case '+': b[i].kind = 1;
			break;
		case '-': b[i].kind = 2;
			break;
		case '*': b[i].kind = 3;
			break;
		case '@': b[i].kind = 4;
			break;
		}
	}
	int q;
	R(q);
	for (int i = 1; i <= q; ++i) {
		R(a[i].zhi);
		a[i].id = i;
	}
	sort(a + 1, a + q + 1, cmp);
	build(1, 1, q);
	//			printf("tr[1].mx = %d\n", tr[1].mx);

	for (int i = 1; i <= n; ++i) {
		switch (b[i].kind) {
		case 1:
			modifyj(1, b[i].zhi);
		//	printf("tr[1].mx = %d\n", tr[1].mx);
			if (tr[1].mx <= R1)continue;
			updatar(1);
			break;
		case 2:
			modifyj(1, -b[i].zhi);		//	printf("tr[1].mn = %d\n", tr[1].mn);

			if (tr[1].mn >= L1)continue;
			updatal(1);
			break;
		case 3: modifyx(1, b[i].zhi);
//			printf("tr[1].mx = %d\n", tr[1].mx);

			if (tr[1].mx <= R1)continue;
			updatar(1);
			break;
		case 4: modifyg(1, b[i].zhi);		//	printf("tr[1].mx = %d\n", tr[1].mx);

			if (tr[1].mx <= R1)continue;
			updatar(1);
			break;
		}
	}
	dfs(1);
	for (int i = 1; i <= q; i++)printf("%d\n", ans[i]);
	return 0;
}
