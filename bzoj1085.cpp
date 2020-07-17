
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
int dx[8] = { -1, 1, -2, 2, -2, 2, -1, 1}, dy[8] = { -2, -2, -1, -1, 1, 1, 2, 2};
int goal[5][5] = {
	{1, 1, 1, 1, 1},
	{0, 1, 1, 1, 1},
	{0, 0, 2, 1, 1},
	{0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0}
};
char zhen[5][5];
int ma[5][5];
int T;
int ans;
int maxd;
bool pd;
inline void dfs(int cishu, pair<int, int>pos, int lef) {
	//printf("cishu = %d, lef = %d\n", cishu, lef);
	if (!lef) {
		ans = min(ans, cishu - 1);
		return;
	}
	if (cishu > min(maxd, ans)) {
		return;
	}
	if (cishu + lef > min(maxd, ans) + 2) return;
	int tx, ty, cnt = 0;
	for (int i = 0 ; i < 8 ; ++i) {
		tx = pos.first + dx[i], ty = pos.second + dy[i];
		cnt = 0;
		if (tx >= 0 && tx < 5 && ty >= 0 && ty < 5) {
			if (goal[tx][ty] == ma[tx][ty]) ++cnt;
			if (goal[pos.first][pos.second] == ma[pos.first][pos.second]) ++cnt;
			swap(ma[tx][ty], ma[pos.first][pos.second]);
			if (goal[tx][ty] == ma[tx][ty]) --cnt;
			if (goal[pos.first][pos.second] == ma[pos.first][pos.second]) --cnt;
			dfs(cishu + 1, make_pair(tx, ty), lef + cnt);
			swap(ma[tx][ty], ma[pos.first][pos.second]);
		}
	}
}
int main() {
	//freopen("in.in", "r", stdin);
	R(T);
	ans = INT_MAX;
	while (T--) {
		ans = INT_MAX;
		pd = 0;
		for (int i = 0; i < 5; ++i) {
			scanf("%s", zhen[i]);
		}
		pair<int, int> pos;
		int cnt = 0;
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (zhen[i][j] != '*')
					ma[i][j] = zhen[i][j] ^'0';
				else {ma[i][j] = 2; pos = make_pair(i, j);}
				if (ma[i][j] != goal[i][j]) ++cnt;
			}
		}
		maxd = 15;
		dfs(1, pos, cnt);
		if (ans == INT_MAX) puts("-1"); else printf("%d\n", ans);
	}
}
