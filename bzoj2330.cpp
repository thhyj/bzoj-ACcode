
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
struct node {
	int to, length;
	node(int to, int length): to(to), length(length) {}
	node() {}
};
std::vector<node>q[100005];
int n, k;
int dis[100005];
inline void create(int x, int y,int z) {
	q[x].push_back(node(y, z));
}
queue<int>que;
bool vis[100005];
int cnt[100005];
int main() {
	R(n), R(k);
	int kind, x, y;
	for (int i = 1; i <= k; ++i) {
		R(kind), R(x), R(y);
		switch (kind) {
		case 1:
			create(x, y, 0);
			create(y, x, 0);
			break;
		case 2:
			if (x == y) {
				puts("-1"); return 0;
			}
			create(x, y, 1);
			break;
		case 3:
			create(y, x, 0);
			break;
		case 4:
			if (x == y) {
				puts("-1"); return 0;
			}
			create(y, x, 1);
			break;
		case 5:
			create(x, y, 0);
			break;
		}
	}
	for (int i = 1; i <= n; ++i) {
		dis[i] = 1;
		que.push(i);
		vis[i] = 1;
		cnt[i] = 1;
	}
	node *p;
	while (!que.empty()) {
		x = que.front();
		que.pop();
		vis[x] = 0;
		for (int i = q[x].size()-1 ; i >=0; --i) {
			p = &q[x][i];
			if (dis[p->to] < dis[x] + p->length) {
				dis[p->to] = dis[x] + p->length;
				if (++cnt[p->to] > n) {
					puts("-1");
					return 0;
				}
				if (!vis[p->to]) {
					que.push(p->to);
					vis[p->to] = 1;
				}
			}
		}
	}
	long long ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans += dis[i];
	}
	printf("%lld\n", ans);
	return 0;
}
