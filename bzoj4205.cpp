
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
	int to, length, pa;
	node (int to, int length, int pa): to(to), length(length), pa(pa) {}
	node() {}
};
int n1, n2;
int dis[100005], gap[100005], temp[100005], vis[100005];
std::vector<node> q[100005];
int s, t;
const int inf = INT_MAX;
struct kapai {
	int x1, x2, x3;
} p1[100005], p2[100005];
inline void bfs() {
	static queue<int> que;
	++gap[0];
	vis[t] = 1;
	que.push(t);
	node *p;
	int x;
	while (!que.empty()) {
		x = que.front();
		que.pop();
		for (int i = 0 ; i < q[x].size(); ++i) {
			p = &q[x][i];
			if (!vis[p->to]) {
				dis[p->to] = dis[x] + 1;
				gap[dis[p->to]]++;
				que.push(p->to);
				vis[p->to] = 1;
			}
		}
	}
}
inline int sap(int x, int flow, int n) {
	if (x == t) return flow;
	int ret = 0;
	node *p;
	int f;
	for (int i = temp[x]; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (dis[p->to] + 1 == dis[x] && p->length) {
			f = sap(p->to, min(p->length, flow - ret), n);
			p->length -= f;
			q[p->to][p->pa].length += f;
			temp[x] = i;
			if ((ret += f) == flow || dis[x] >= n) {
				temp[x] = 0;
				return ret;
			}
		}
	}
	if (!(--gap[dis[x]])) dis[s] = n;
	gap[++dis[x]]++;
	temp[x] = 0;
	return ret;
}
inline int sap(int n) {
	int ret = 0;
	bfs();
	while (dis[s] < n) ret += sap(s, inf, n);
	return ret;
}
int zhishu[205], heshu[205], cnt;
inline void init() {
	for (int i = 2; i <= 200; ++i) {
		if (!heshu[i]) zhishu[++cnt] = i;
		for (int j = 1; j <= cnt && zhishu[j] * i <= 200; ++j) {
			heshu[zhishu[j] * i] = 1;
			if (i % zhishu[j] == 0) break;
		}
	}
}
inline void create(int x, int y, int z) {
	q[x].push_back(node(y, z, q[y].size()));
	q[y].push_back(node(x, 0, q[x].size() - 1));
}
int tot;
map<int, int> ma[205];
std::vector<int> q1, q2;
int main () {
	init();
	R(n1), R(n2);
	s = 0; t = 100000;
	for (int i = 1; i <= n1; ++i) {
		R(p1[i].x1), R(p1[i].x2), R(p1[i].x3);
	}

	for (int i = 1; i <= n2; ++i) {
		R(p2[i].x1), R(p2[i].x2), R(p2[i].x3);
	}
	for (int i = 1; i <= n1; ++i) {
		create(s, i, 1);
	}
	for (int i = 1; i <= n2; ++i) {
		create(i + n1, t, 1);
	}
	tot = n1 + n2 + 1;
	//AB
	for (int i = 1; i <= cnt; ++i) {
		for (int j = 1; j <= cnt; ++j) {
			ma[zhishu[i]][zhishu[j]] = tot++;
		}
	}
	int t, temp;
	for (int i = 1; i <= n1; ++i) {
		q1.clear();
		q2.clear();
		t = p1[i].x1;
		temp = sqrt(p1[i].x1);
		for (int j = 1; j <= cnt && zhishu[j] <= temp; ++j) {
			if (zhishu[j] > t) break;
			if (t % zhishu[j] == 0 ) {
				q1.push_back(zhishu[j]);
				while (t % zhishu[j] == 0) {
					t /= zhishu[j];
				}
			}
		}
		if (t > 1) q1.push_back(t);
		t = p1[i].x2;
		temp = sqrt(p1[i].x2);
		for (int j = 1; j <= cnt && zhishu[j] <= temp; ++j) {
			if (zhishu[j] > t) break;
			if (t % zhishu[j] == 0 ) {
				q2.push_back(zhishu[j]);
				while (t % zhishu[j] == 0) {
					t /= zhishu[j];
				}
			}
		}
		if (t > 1) q2.push_back(t);
		for (int j = 0; j < q1.size(); ++j) {
			for (int k = 0; k < q2.size(); ++k) {
				create(i, ma[q1[j]][q2[k]], 1);
			}
		}
	}
	for (int i = 1; i <= n2; ++i) {
		q1.clear();
		q2.clear();
		t = p2[i].x1;
		temp = sqrt(p2[i].x1);
		for (int j = 1; j <= cnt && zhishu[j] <= temp; ++j) {
			if (zhishu[j] > t) break;
			if (t % zhishu[j] == 0 ) {
				q1.push_back(zhishu[j]);
				while (t % zhishu[j] == 0) {
					t /= zhishu[j];
				}
			}
		}
		if (t > 1) q1.push_back(t);
		t = p2[i].x2;
		temp = sqrt(p2[i].x2);
		for (int j = 1; j <= cnt && zhishu[j] <= temp; ++j) {
			if (zhishu[j] > t) break;
			if (t % zhishu[j] == 0 ) {
				q2.push_back(zhishu[j]);
				while (t % zhishu[j] == 0) {
					t /= zhishu[j];
				}
			}
		}
		if (t > 1) q2.push_back(t);
		for (int j = 0; j < q1.size(); ++j) {
			for (int k = 0; k < q2.size(); ++k) {
				create(ma[q1[j]][q2[k]], i + n1, 1);
			}
		}
	}
	//AC
	for (int i = 1; i <= cnt; ++i) {
		for (int j = 1; j <= cnt; ++j) {
			ma[zhishu[i]][zhishu[j]] = tot++;
		}
	}
	for (int i = 1; i <= n1; ++i) {
		q1.clear();
		q2.clear();
		t = p1[i].x1;
		temp = sqrt(p1[i].x1);
		for (int j = 1; j <= cnt && zhishu[j] <= temp; ++j) {
			if (zhishu[j] > t) break;
			if (t % zhishu[j] == 0 ) {
				q1.push_back(zhishu[j]);
				while (t % zhishu[j] == 0) {
					t /= zhishu[j];
				}
			}
		}
		if (t > 1) q1.push_back(t);
		t = p1[i].x3;
		temp = sqrt(p1[i].x3);
		for (int j = 1; j <= cnt && zhishu[j] <= temp; ++j) {
			if (zhishu[j] > t) break;
			if (t % zhishu[j] == 0 ) {
				q2.push_back(zhishu[j]);
				while (t % zhishu[j] == 0) {
					t /= zhishu[j];
				}
			}
		}
		if (t > 1) q2.push_back(t);
		for (int j = 0; j < q1.size(); ++j) {
			for (int k = 0; k < q2.size(); ++k) {
				create(i, ma[q1[j]][q2[k]], 1);
			}
		}
	}
	for (int i = 1; i <= n2; ++i) {
		q1.clear();
		q2.clear();
		t = p2[i].x1;
		temp = sqrt(p2[i].x1);
		for (int j = 1; j <= cnt && zhishu[j] <= temp; ++j) {
			if (zhishu[j] > t) break;
			if (t % zhishu[j] == 0 ) {
				q1.push_back(zhishu[j]);
				while (t % zhishu[j] == 0) {
					t /= zhishu[j];
				}
			}
		}
		if (t > 1) q1.push_back(t);
		t = p2[i].x3;
		temp = sqrt(p2[i].x3);
		for (int j = 1; j <= cnt && zhishu[j] <= temp; ++j) {
			if (zhishu[j] > t) break;
			if (t % zhishu[j] == 0 ) {
				q2.push_back(zhishu[j]);
				while (t % zhishu[j] == 0) {
					t /= zhishu[j];
				}
			}
		}
		if (t > 1) q2.push_back(t);
		for (int j = 0; j < q1.size(); ++j) {
			for (int k = 0; k < q2.size(); ++k) {
				create(ma[q1[j]][q2[k]], i + n1, 1);
			}
		}
	}
	//BC
	for (int i = 1; i <= cnt; ++i) {
		for (int j = 1; j <= cnt; ++j) {
			ma[zhishu[i]][zhishu[j]] = tot++;
		}
	}
	for (int i = 1; i <= n1; ++i) {
		q1.clear();
		q2.clear();
		t = p1[i].x2;
		temp = sqrt(p1[i].x2);
		for (int j = 1; j <= cnt && zhishu[j] <= temp; ++j) {
			if (zhishu[j] > t) break;
			if (t % zhishu[j] == 0 ) {
				q1.push_back(zhishu[j]);
				while (t % zhishu[j] == 0) {
					t /= zhishu[j];
				}
			}
		}
		if (t > 1) q1.push_back(t);
		t = p1[i].x3;
		temp = sqrt(p1[i].x3);
		for (int j = 1; j <= cnt && zhishu[j] <= temp; ++j) {
			if (zhishu[j] > t) break;
			if (t % zhishu[j] == 0 ) {
				q2.push_back(zhishu[j]);
				while (t % zhishu[j] == 0) {
					t /= zhishu[j];
				}
			}
		}
		if (t > 1) q2.push_back(t);
		for (int j = 0; j < q1.size(); ++j) {
			for (int k = 0; k < q2.size(); ++k) {
				create(i, ma[q1[j]][q2[k]], 1);
			}
		}
	}
	for (int i = 1; i <= n2; ++i) {
		q1.clear();
		q2.clear();
		t = p2[i].x2;
		temp = sqrt(p2[i].x2);
		for (int j = 1; j <= cnt && zhishu[j] <= temp; ++j) {
			if (zhishu[j] > t) break;
			if (t % zhishu[j] == 0 ) {
				q1.push_back(zhishu[j]);
				while (t % zhishu[j] == 0) {
					t /= zhishu[j];
				}
			}
		}
		if (t > 1) q1.push_back(t);
		t = p2[i].x3;
		temp = sqrt(p2[i].x3);
		for (int j = 1; j <= cnt && zhishu[j] <= temp; ++j) {
			if (zhishu[j] > t) break;
			if (t % zhishu[j] == 0 ) {
				q2.push_back(zhishu[j]);
				while (t % zhishu[j] == 0) {
					t /= zhishu[j];
				}
			}
		}
		if (t > 1) q2.push_back(t);
		for (int j = 0; j < q1.size(); ++j) {
			for (int k = 0; k < q2.size(); ++k) {
				create(ma[q1[j]][q2[k]], i + n1, 1);
			}
		}
	}
	printf("%d\n", sap(tot));
}
