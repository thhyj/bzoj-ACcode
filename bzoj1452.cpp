
#include <bits/stdc++.h>
using namespace std;
int ma[305][305];
int sum[305][305][101];
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
int n, m;
#define lowbit(a) (a&(-a))
inline void modify(int x, int y, int c, int v) {
	for (int i = x; i <= n; i += lowbit(i)) {
		for (int j = y; j <= m; j += lowbit(j)) {
			sum[i][j][c] += v;
		}
	}
}
inline int query(int x, int y, int c) {
	int ret = 0;
	for (int i = x; i; i -= lowbit(i)) {
		for (int j = y; j; j -= lowbit(j)) {
			ret += sum[i][j][c];
		}
	}
	return ret;
}
#define x1 gjai
#define y1 asyg
#define x2 adsg
#define y2 asgga
int main () {
//	freopen("in.in","r",stdin);
	R(n), R(m);
	int ans;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			R(ma[i][j]);
			modify(i, j, ma[i][j], 1);
		}
	}
	int q;
	R(q);
	int kind;
	int x, y, c, x1, y1, x2 , y2;
	for (int i = 1; i <= q; ++i) {
		R(kind) ;
		switch (kind) {
		case 1: R(x), R(y), R(c);
			modify(x, y, ma[x][y], -1);
			modify(x, y, c,  1);
			ma[x][y] = c;
			break;
		case 2:
			R(x1), R(x2), R(y1), R(y2), R(c);
		//	cout<<"query(x2, y2, c) = "<<query(x2, y2, c) <<'\n';
		//	cout<<"query(x1 - 1, y1 - 1, c) = "<<query(x1 - 1, y1 - 1, c) <<'\n';
		//	cout<<"query(x2, y1 - 1, c) = "<<query(x2, y1 - 1, c) <<'\n';
		//	cout<<"query(x1 - 1, y2, c) = "<<query(x1 - 1, y2, c) <<'\n';
			ans = query(x2, y2, c) + query(x1 - 1, y1 - 1, c) - query(x2, y1 - 1, c) - query(x1 - 1, y2, c);
			printf("%d\n", ans);
			break;
		}
	}
	return 0;
}
