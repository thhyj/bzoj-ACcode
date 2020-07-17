
#include <bits/stdc++.h>
using namespace std;
struct trie {
	int son[10], sum;
} tr[300005];
int tot;
int n;
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
char q[65];
int kind, a, b, c;
int id;
inline int build(char *s) {
	int len = strlen(s);
	int now = 0;
	for (int i = 0 ; i < len; ++i) {
		if (!tr[now].son[s[i] - 'a']) {
			tr[now].son[s[i] - 'a'] = ++tot;
		}
		now = tr[now].son[s[i] - 'a'];
	}
	return now;
}
std::vector<int> ti[300005];
int caozuo;

inline void modify(char *s) {
	int len = strlen(s);
	int now = 0;
	for (int i = 0; i < len; ++i) {
		if (!tr[now].son[s[i] - 'a']) {
			tr[now].son[s[i] - 'a'] = ++tot;
		}
		now = tr[now].son[s[i] - 'a'];
		tr[now].sum++;
		if (ti[now].size() < tr[now].sum) {
			ti[now].push_back(caozuo);
		}
	}
}
inline void erase(char *s) {
	int len = strlen(s);
	int now = 0;
	for (int i = 0; i < len; ++i) {
		if (!tr[now].son[s[i] - 'a']) {
			tr[now].son[s[i] - 'a'] = ++tot;
		}
		now = tr[now].son[s[i] - 'a'];
		tr[now].sum--;
	}
}
int main() {
	R(n);
	char s[105];
	int cnt = 0;
	int ans = 0;
	int temp;
	for (int i = 1; i <= n; ++i) {
		++caozuo;
		R(kind);
		switch (kind) {
		case 1:
			scanf("%s", q);
			modify(q);
			break;
		case 2:
			scanf("%s", q);
			erase(q);
			break;
		case 3:
			scanf("%s", q);
			R(a), R(b), R(c);
			temp = ((long long)a * abs(ans) + b) % c;
			//		cout<<"temp = "<<temp<<'\n';
			id = build(q);
			if (ti[id].size() <= temp) {
				puts("-1");
				ans = -1;
				continue;
			} else {
				//		for(int j = 0; j < ti[id[i]].size(); ++j) {
				//			printf("ti[%d][%d].first = %d, ti[%d][%d].second = %d\n",i, j, ti[id[i]][j].first,i, j,ti[id[i]][j].second);
				//		}
				ans = ti[id][temp];
				printf("%d\n", ans);
			}
		}
	}
	return 0;
}
