
#include <bits/stdc++.h>
using namespace std;
inline char read() {
    static const int IN_LEN = 1000000;
    static char buf[IN_LEN], *s, *t;
    s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin) : 0;
    return s == t ? -1 : *s++;
}

template <typename T>
inline void R(T &x) {
    static char c;
    static bool iosig;
    for (c = read(), iosig = false; !isdigit(c); c = read()) {
        if (c == -1) return;
        c == '-' ? iosig = true : 0;
    }
    for (x = 0; isdigit(c); c = read()) x = (x + (x << 2) << 1) + (c ^ '0');
    iosig ? x = -x : 0;
}

inline int read(char *buf) {
    register int s = 0;
    register char c;
    while (c = read(), isspace(c) && c != -1)
        ;
    if (c == -1) {
        *buf = '\0';
        return -1;
    }
    do
        buf[s++] = c;
    while (c = read(), !isspace(c) && c != -1);
    buf[s] = '\0';
    return s;
}

inline void read(double &x) {
    static char buf[30];
    read(buf), x = atof(buf);
}
struct node {
	int to, length;
	node (int to, int length): to(to), length(length) {}
	node() {}
};
std::vector<node> q[200010];
inline void create(int x, int y , int z) {
	q[x].push_back(node(y, z));
	q[y].push_back(node(x, z));
}
int dis[200005], d[200005], bian[200005], siz[200005];
bool vis[200005];
int rt, sum;
int ans[200005];
const int inf = INT_MAX;
inline void findrt(int x, int f) {
	node *p;
	siz[x] = 1;
	d[x] = 0;
	for (int i = 0; i < q[x].size(); ++i) {
		p = &q[x][i];
		if ((!vis[p->to]) && (p->to ^ f)) {
			findrt(p->to, x);
			siz[x] += siz[p->to];
			d[x] = max(d[x], siz[p->to]);
		}
	}
	d[x] = max(d[x], sum - siz[x]);
	if (d[x] < d[rt]) rt = x;
}
	int n, k;
typedef pair<int ,int> pii;
vector<pii>st;
inline bool cmp1(const pii &a, const pii &b) {
	return a.first < b.first;
}
inline void getdis(int x, int f) {
	node *p;
	st.push_back((pii) {dis[x], bian[x]});
	for (int i = 0; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (p->to != f && (!vis[p->to])) {
			dis[p->to] = dis[x] + p->length;
			bian[p->to] = bian[x] + 1;
			getdis(p->to, x);
		}
	}
}
inline void calc(int x, int nowd, int nowb, int f) {
	dis[x] = nowd, bian[x] = nowb;
	st.clear();
	getdis(x, x);
	sort(st.begin(), st.end(), cmp1);
	for (int i = 0, j = st.size() - 1; i <= j; i++)
	{
		while (j > i && st[i].first + st[j].first > k) j--;
		for (int t = j; st[i].first + st[t].first == k; t--) ans[st[i].second + st[t].second] += f;
	}
}
inline void solve(int x) {
	vis[x] = 1;
	calc(x, 0, 0, 1);
	node *p;
	for (int i = 0; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (!vis[p->to]) {
			calc(p->to, p->length, 1, -1);
			rt = 0;
			sum = siz[p->to];
			findrt(p->to, p->to);
			solve(rt);
		}
	}
}
int main () {
	//freopen("in.in","r",stdin);
	R(n), R(k);
	int x, y , z;
	for (int i = 1; i < n; ++i) {
		R(x), R(y), R(z);
		create(x, y, z);
	}
	rt = 0, sum = n;
	findrt(0, 0);
	solve(0);
	for (int i = 1; i < n; i++) if (ans[i]) {printf("%d\n", i); return 0;}
	printf("-1\n");
}
