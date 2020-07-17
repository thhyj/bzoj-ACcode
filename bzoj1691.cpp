
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
struct fuc {
	int nen, pri;
} cao[100005], niu[100005];
int n, m;
inline bool cmp(const fuc &a, const fuc &b) {
	return a.nen > b.nen;
}
multiset<int>q;
int main() {
	R(n), R(m);
	for (int i = 1; i <= n; ++i) {
		R(niu[i].pri), R(niu[i].nen);
	}
	for (int i = 1; i <= m; ++i) {
		R(cao[i].pri), R(cao[i].nen);
	}
	sort(niu + 1, niu + n + 1, cmp);
	sort(cao + 1, cao + m + 1, cmp);
	int now = 1;
//	for (int i = 1; i <= n; ++i) {
///		printf("pri = %d, nen = %d\n", niu[i].pri, niu[i].nen);
//	}
//	for (int i = 1; i <= m; ++i) {
//		printf("pri = %d, nen = %d\n", cao[i].pri, cao[i].nen);
//	}
	long long ans = 0;
	for (int i = 1; i <= n; ++i) {
	//	printf("i = %d\n", i);
		while (now <= m && cao[now].nen >= niu[i].nen) {
	//		printf("cao.pri = %d\n", cao[now].pri);
			q.insert(cao[now++].pri);
		}
		if (q.empty()) {
			puts("-1");
			return 0;
		} else {
			set<int>::iterator iter = q.lower_bound(niu[i].pri);
			if (iter == q.end() || *iter < niu[i].pri) {
				puts("-1");
				return 0;
			}
	//		cout << "*iter = " << *iter << '\n';
			ans += *iter;
			q.erase(iter);
		}
	}
	cout << ans;
	return 0;
}
