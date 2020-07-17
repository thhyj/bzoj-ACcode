
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
int m;
int n[105];
std::vector<int> q[105][105];
int cd[105][105];
int dep[105][105];
inline void create(int x, int y, int i) {
	q[i][x].push_back(y);
	q[i][y].push_back(x);
}
std::vector<int> tong[2][105];
map<vector<long long>, bool >ma;
vector<long long>linshi;
int siz[105];
int mi, rt[2], ma1[105];
inline void getzhongxin(int x, int f, int i) {
	siz[x] = 1;
	ma1[x] = 0;
	int v;
	for (int j = 0; j < q[i][x].size(); ++j) {
		v = q[i][x][j];
		if (v != f) {
			getzhongxin(v, x, i);
			siz[x] += siz[v];
			ma1[x] = max(ma1[x], siz[v]);
		}
	}
	ma1[x] = max(ma1[x], n[i] - siz[x]);
	if (ma1[x] <= ma1[rt[1]]) {
		if (ma1[x] == ma1[rt[1]]) {
			rt[2] = x;
		} else {
			rt[1] = x;
			rt[2] = -1;
		}
	}
}
pair<string, string> ha[105];
inline string dfs(int x, int f, int i) {
	string s;
	s += '(';
	std::vector<string> zu;
	int v;
	for (int j = 0; j < q[i][x].size(); ++j) {
		v = q[i][x][j];
		if (v != f) {
			zu.push_back(dfs(v, x, i));
		}
	}
	sort(zu.begin(), zu.end());
	for (int j = 0; j < zu.size(); ++j) {
		s += zu[j];
	}
	s += ')';
	return s;
}
inline void getha(int x) {
	memset(siz, 0, sizeof(siz));
	rt[1] = 0, rt[2] = -1;
	getzhongxin(1, 1, x);
	ha[x].first = "0", ha[x].second = "0";
	for (int i = 1; i <= n[x]; ++i) {
		if (i == rt[1]) ha[x].first = dfs(i, i, x);
		if (i == rt[2]) ha[x].second = dfs(i, i , x);
	}
}
int main () {
//	freopen("family.in", "r", stdin);
	//freopen("family.out", "w", stdout);
	R(m);
	ma1[0] = INT_MAX;
	int x, y;
	for (int i = 1; i <= m; ++i) {
		R(n[i]);
		for (int j = 1; j <= n[i]; ++j) {
			R(x);
			if (x == 0) {
				;
			} else {
				create(x, j, i);
			}
		}
		//dfs(rt, rt, i);
	}
	int ans = INT_MAX;
	for (int i = 1; i <= m; ++i) {
		getha(i);
	}
	for (int i = 1; i <= m; ++i) {
		ans = i;
		for (int j = 1; j < i; ++j) {
			if ((ha[i].first == ha[j].first || ha[i].first == ha[j].second) && (ha[i].second == ha[j].first || ha[i].second == ha[j].second)) {ans = min(ans, j); break;}
		}
		printf("%d\n", ans);
	}
	return 0;
}
