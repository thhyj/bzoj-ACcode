
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
int n, m, s, t;
struct node {
	int to, v1, v2;
	node(int to, int v1, int v2): to(to), v1(v1), v2(v2) {}
	node(){
	}
};
vector<node>q[105];
int dis[105][200005];
queue<pair<int, int> >que;
#define pii pair<int, int>
#define mk make_pair
bool vis[105][200005];
int main () {
	/*R(n), R(m), R(s), R(t);
	int u, v, x, y;
	for (int i = 1; i <= m; ++i) {
		R(u), R(v), R(x), R(y);
		q[u].push_back(node(v, x, y));
		q[v].push_back(node(u, x, y));
	}
	memset(dis, 127, sizeof(dis));
	dis[s][0] = 0;
	que.push(mk(s, 0));
	vis[s][0] = 1;
	pii temp;
	while (!que.empty()) {
		temp = que.front();
		que.pop();
		vis[temp.first][temp.second] = 0;
		node *p;
		for (int i = 0; i < q[temp.first].size(); ++i) {
			p = &q[temp.first][i];
			if (temp.second + p->v1 > 100000) continue;
			if (dis[p->to][temp.second + p->v1] > dis[temp.first][temp.second] + p->v2) {
				dis[p->to][temp.second + p->v1] = dis[temp.first][temp.second] + p->v2;
				if (!vis[p->to][temp.second + p->v1]) {
					vis[p->to][temp.second + p->v1] = 1;
					que.push(mk(p->to, temp.second + p->v1));
				}
			}
		}
	}
	int mi = INT_MAX;
	int ans = 0;
	for (int i = 0; i <= 100000; ++i) {
		if (dis[t][i] == 0x7f7f7f7f) continue;
		if (dis[t][i] > mi) continue;
		mi = dis[t][i];
		++ans;
	}*/
}
