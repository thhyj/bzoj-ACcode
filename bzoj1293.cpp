
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
int n, k, a[1000005];
std::vector<int> cz[62];
deque<int>q[62];
const int inf = INT_MAX;
int main () {
	R(n), R(k);
	int m;
	int x;
	int cnt = 0;
	for (int i = 1; i <= k; ++i) {
		R(m);
		for (int j = 1; j <= m; ++j) {
			R(x);
			q[i].push_back(x);
			a[++cnt] = x;
		}
	}
	sort(a + 1, a + cnt + 1);
	int st, ed = 0;
	int ans = inf;
	for (int i = 1; i <= cnt; ++i) {
		if (a[i] == a[i + 1]) continue;
		st = a[i];
		ed = st;
		for (int j = 1; j <= k; ++j) {
			while ((!q[j].empty()) && q[j].front() < st) q[j].pop_front();
			if (q[j].empty()) {ed = inf, st = 0; break;}
			else
				ed = max(ed, q[j].front());
		}
		ans = min(ed - st, ans);
	}
	printf("%d\n", ans);
	return 0;
}
