
#include <bits/stdc++.h>
using namespace std;
struct node {
	int son[26], fail, len, cnt;
} tr[300005];
int tot;
int last;
char s[300005];
inline int getfail(int x, int l) {
	while (s[l - tr[x].len - 1] != s[l]) {
//		printf("tr[%d].fail = %d\n", x, tr[x].fail);
		x = tr[x].fail;
	}
	return x;
}
int main() {
	//freopen("in.in", "r", stdin);
	scanf("%s", s + 1);
	int len = strlen(s + 1);
	s[0] = -1;
	tr[tot].fail = 1;
	tr[tot++].len = 0;
	tr[tot].len = -1;
	int cur;
	int now;
	for (int i = 1 ; i <= len ; ++i) {
		now = s[i] - 'a';
		cur = getfail(last, i);
	//	printf("cur = %d\n", cur);
		if (!tr[cur].son[now]) {
			++tot;
		//	printf("fail = %d\n", getfail(tr[cur].fail, now) );
	//		printf("son = %d\n", tr[getfail(tr[cur].fail, i)].son[now]);
			tr[tot].fail = tr[getfail(tr[cur].fail, i)].son[now];
		//	printf("tr[%d].fail = %d\n", tot, tr[tot].fail);
			tr[tot].len = tr[cur].len + 2;
			tr[cur].son[now] = tot;
		}
		tr[last = tr[cur].son[now]].cnt++;
	//	printf("last = %d\n", last);
	}
	long long ans = 0;
	for (int i = tot; i >= 0; --i) {
		tr[tr[i].fail].cnt += tr[i].cnt;
		ans = max(ans, (long long)tr[i].cnt * tr[i].len);
	}
	cout << ans << '\n';
}
