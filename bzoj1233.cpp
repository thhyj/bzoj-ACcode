
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
int n, w[100005], sum[100005], f[100005], g[100005];
deque<int>q;
int main() {
	R(n);
	for (int i = 1; i <= n; ++i) {
		R(w[i]);
		sum[i] = sum[i - 1] + w[i];
	}
	q.push_back(n + 1);
	for (int i = n; i; --i) {
		while ((q.size() > 1) && (sum[q[1] - 1] - sum[i - 1]) >= f[q[1]]) q.pop_front();
		f[i] = (sum[q.front() - 1] - sum[i - 1]);
		g[i] = g[q.front()] + 1;
		while ((q.size() > 1) && (f[q.back()] - sum[q.back() - 1]) > f[i] - sum[i - 1]) q.pop_back();
		q.push_back(i);
	}
	printf("%d\n", g[1]);
}
