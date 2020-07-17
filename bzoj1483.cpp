
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
	if (p)v = -v;
}
set<int> q[1000005];
int v[100005];
bool vis[1000005];
int tot;
int n, m;
int ans;
int daibiao[1000005];
inline void hebing(int &x, int &y) {
	if (q[x].size() > q[y].size()) swap(x, y);
	if (q[x].empty()) return;
	set<int>::iterator temp;
	for (set<int>::iterator iter = q[x].begin(); iter != q[x].end(); ++iter) {
		/*temp = q[y].upper_bound(*iter);
		if (temp != q[y].end()) {
			if (*temp == *iter + 1) --ans;
		}
		if (temp != q[y].begin()) {
			--temp;
			if (*temp == *iter - 1) --ans;
		}*/
		if (q[y].find((*iter) + 1) != q[y].end()) --ans;
		if (q[y].find((*iter) - 1) != q[y].end()) --ans;

	}
	q[y].insert(q[x].begin(), q[x].end());
	q[x].clear();
}
int main () {
	R(n), R(m);
	int x;

	for (int i = 1; i <= n; ++i) {
		R(x);
		q[x].insert(i);
		if (!vis[x]) {
			v[++tot] = x;
			vis[x] = 1;
		}
	}
	for (int i = 1; i <= 1000005; ++i) daibiao[i] = i;
	ans = n;
	int pre;
	for (int i = 1; i <= tot; ++i) {
		pre = *q[v[i]].begin();
		for (set<int>::iterator iter = ++q[v[i]].begin(); iter != q[v[i]].end(); ++iter) {
			if (pre == *(iter) - 1) ans--;
			pre = *iter;
		}
	}
	int kind, l, r, v;
	for (int i = 1; i <= m; ++i) {
		R(kind);
		switch (kind) {
		case 1:
			R(l), R(r);
			if(l==r)continue;
			hebing(daibiao[l], daibiao[r]);
			break;
		case 2:
			printf("%d\n", ans);
			break;
		}
	}
}
