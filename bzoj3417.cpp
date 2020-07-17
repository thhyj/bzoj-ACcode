
#include <bits/stdc++.h>
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
	if (p)v = -v;
}
using namespace std;
std::vector<int> q[5005];
#define create(x, y) q[x].push_back(y), q[y].push_back(x);
int n, m, k;
struct que {
	int s, t, d, id;
} qu[1000005];
inline bool cmp(const que &a, const que &b) {
	return a.s < b.s;
}
bool ans[1000005];
int dis[5005][2];
struct zhuangtai {
	int x;
	bool step;
	zhuangtai(int x, bool step): x(x), step(step) {}
	zhuangtai() {}
};
inline void bfs(int s) {
	static deque<zhuangtai> p;
	p.clear();
	p.push_back(zhuangtai(s, 0));
	zhuangtai temp;
	int x, v;
	bool flag;
	while (!p.empty()) {
		temp = p.front();
		p.pop_front();
		x = temp.x;
		flag = temp.step;
		for (int i = 0; i < q[x].size(); ++i) {
			v = q[x][i];
			if (dis[v][!flag] == 0x3f3f3f3f) {
				dis[v][!flag] = dis[x][flag] + 1;
				p.push_back(zhuangtai(v, !flag));
			}
		}
	}
}
int main () {
//	freopen("in.in","r",stdin);
	R(n), R(m), R(k);
	int x, y, z;
	for (int i = 1; i <= m; ++i) {
		R(x), R(y);
		create(x, y);
	}
	for (int i = 1; i <= k; ++i) {
		R(qu[i].s), R(qu[i].t), R(qu[i].d), qu[i].id = i;
	}
	sort(qu + 1, qu + 1 + k, cmp);
	int now = 0;
//	puts("done");
	for (int i = 1; i <= k; ++i) {
		if (qu[i].s == qu[i].t && q[qu[i].s].size() == 0) {
			ans[qu[i].id] = !qu[i].d;
			continue;
		}
		if (qu[i].s != now) {
			now = qu[i].s;
			memset(dis, 0x3f, sizeof(dis));
			dis[now][0] = 0;
			bfs(now);
		}
		ans[qu[i].id] = (dis[qu[i].t][(qu[i].d & 1)] <= qu[i].d);
	}
	for (int i = 1; i <= k; ++i) {
		if (ans[i]) puts("TAK"); else puts("NIE");
	}
	return 0;
}
