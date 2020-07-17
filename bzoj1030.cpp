
#include <bits/stdc++.h>
using namespace std;
int n, m;
char s[65][105];
struct trie {
	int son[26], fail;
	bool cnt;
} tr[6005];
int tot;
int dp[105][6005];
inline void build(char *s) {
	int len = strlen(s), temp, now = 0;
	for (int i = 0; i < len; ++i) {
		temp = s[i] - 'A';
		if (!tr[now].son[temp]) {
			tr[now].son[temp] = ++tot;
		}
		now = tr[now].son[temp];
	}
	tr[now].cnt = 1;
}
inline void getfail() {
	static queue<int> que;
	for (int i = 0; i < 26; ++i) {
		if (tr[0].son[i]) que.push(tr[0].son[i]);
	}
	int u, v;
	while (!que.empty()) {
		u = que.front();
		que.pop();
		for (int i = 0; i < 26; ++i) {
			v = tr[u].fail;
			if ((!tr[v].son[i]) && v) v = tr[v].fail;
			if (tr[u].son[i]) {
				tr[tr[u].son[i]].fail = tr[v].son[i];
				tr[tr[u].son[i]].cnt |= tr[tr[v].son[i]].cnt;
				que.push(tr[u].son[i]);
			} else {
				tr[u].son[i] = tr[v].son[i];
			}
		}
	}
}
const int mod = 10007;

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", s[i]);
		build(s[i]);
	}
	getfail();
	dp[0][0] = 1;
//	cout<<"tot="<<tot<<'\n';
	int v;
	for (int i = 1; i <= m ; ++i) {
		for (int j = 0; j <= tot; ++j) {
			if (dp[i - 1][j])
				for (int k = 0 ; k < 26; ++k) {
					v = j;
					if (v && !tr[v].son[k]) v = tr[v].fail;
					v = tr[v].son[k];
					if (tr[v].cnt == 0)
						dp[i][v] = (dp[i][v] + dp[i - 1][j]) % mod;
				}
		}
	}
	int ans = 1;
	for (int i = 1; i <= m; ++i) {
		ans = ans * 26 % mod;
	}
//	for (int j = 1; j <= m; ++j)
//		for (int i = 0; i <= tot; ++i) {
//			printf("dp[%d][%d] = %d\n", j, i , dp[j][i]);
//		}
	int to1 = 0;
	for (int i = 0; i <= tot; ++i) {
		if (!tr[i].cnt)
			to1 += dp[m][i];
		to1 %= mod;
	}
	ans = ((ans - to1) % mod + mod) % mod;
	cout << ans << '\n';
}
