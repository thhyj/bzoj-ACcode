
#include <bits/stdc++.h>
using namespace std;
inline void R(int &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
		ch = getchar();
		if (ch == '-') p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = (v  + (v << 2) << 1) + (ch^'0');
		ch = getchar();
	}
	if (p)v = -v;
}
struct trie {
	int son[2], sum;
} tr[36000000];
int cnt;
int bin[31];
int a[600005], b[600005];
int rt[600005];
inline void insert(int pre, int now, int v) {
	for (int i = 25; i >= 0 ; i --) {
		int t = (v & bin[i]) >> i;
		tr[now].sum = tr[pre].sum + 1;
		tr[now].son[1] = tr[pre].son[1];
		tr[now].son[0] = tr[pre].son[0];
		tr[now].son[t] = ++cnt;
		now = tr[now].son[t], pre = tr[pre].son[t];
	}
	tr[now].sum = tr[pre].sum + 1;
}
inline int query(int pre, int now , int v) {
	int ans = 0;
//	printf("v = %d\n", v);
	for (int i = 25; i >= 0; i --) {
		int t = (v & bin[i]) >> i;
		if (tr[tr[now].son[t ^ 1]].sum - tr[ tr[pre].son[t ^ 1]].sum) {
			ans += bin[i];
			now = tr[now].son[t ^ 1], pre = tr[pre].son[t ^ 1];
		} else {
			now = tr[now].son[t], pre = tr[pre].son[t];
		}
	}
	return ans;
}
int main () {
//	freopen("in.in","r",stdin);
	bin[0] = 1;
	for (int i = 1; i <= 30; ++i) bin[i] = bin[i - 1] << 1;
	int n;
	R(n);
	++n;
	int m;
	R(m);
	rt[1] = ++cnt;
	insert(rt[0], rt[1], b[1]);
	for (int i = 2; i <= n; ++i) {
		R(a[i]);
		b[i] = b[i - 1] ^ a[i];
//		printf("b[%d] = %d\n",i ,b[i]);
		rt[i] = ++cnt;
		insert(rt[i - 1], rt[i], b[i]);
	}
	
	int kind, l, r, x;
	char ch;
	for (int i = 1; i <= m; ++i) {
		do {
			ch = getchar();
		} while (!isupper(ch));
		switch (ch) {
		case 'A' :
			R(x);
			b[n + 1] = b[n] ^ x;
			rt[++n] = ++cnt;
			insert(rt[n - 1], rt[n], b[n]);
			break;
		case 'Q':
			R(l), R(r), R(x);
			printf("%d\n", query(rt[l - 1], rt[r], b[n]^x));
			break;
		}
	}
}
