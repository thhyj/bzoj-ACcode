
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
struct shu {
	int id, zhi;
} a[100005];
inline bool cmp(const shu &a, const shu &b) {
	return a.zhi > b.zhi;
}
int n;
set<int>ms;
int l[100005], r[100005];
struct trie {
	int son[2], sum;
} tr[50000 * 35];
int root[50005];
int b[100005];
int tot;
#define bin(x) (1<<x)
inline void build(int pre, int now, int x) {
	int temp;
	for (int i = 30; i >= 0; --i) {
		tr[now] = tr[pre];
		tr[now].sum ++;
		temp =  (x & (bin(i))) >> i;
		if (temp) {
			tr[now].son[1] = ++tot;
			now = tr[now].son[1],
			pre = tr[pre].son[1];
		} else {
			tr[now].son[0] = ++tot;
			now = tr[now].son[0],
			pre = tr[pre].son[0];
		}
	}
	tr[now].sum = tr[pre].sum + 1;
}
inline int query(int pre, int now, int x) {
	int temp, ret = 0;
	for (int i = 30; i >= 0; --i) {
		temp =  (x & (bin(i))) >> i;
		if (tr[tr[now].son[temp ^ 1]].sum - tr[tr[pre].son[temp ^ 1]].sum > 0) {
			ret += bin(i);
			now = tr[now].son[temp ^ 1],
			pre = tr[pre].son[temp ^ 1];
		} else {
			now = tr[now].son[temp],
			pre = tr[pre].son[temp];
		}
	}
	return ret;
}
int main () {
	R(n);
	for (int i =  1; i <= n; ++i) {
		R(a[i].zhi);
		a[i].id = i;
		root[i] = ++tot;
		build(root[i - 1], root[i], a[i].zhi);
	}
	sort(a + 1, a + n + 1, cmp);
	ms.insert(0), ms.insert(n + 1);
	set<int>:: iterator iter;
	for (int i = 1; i <= n; ++i) {
		iter = ms.lower_bound(a[i].id);
		++iter;
		if (iter == ms.end()) r[a[i].id] = n;
		else r[a[i].id] = (*iter) - 1;
		--iter;
		--iter;
		if (iter == ms.begin()) l[a[i].id] = 0;
		else --iter, l[a[i].id] = (*iter);
		ms.insert(a[i].id);
	}
	int ans = 0;
//	printf("tr[20].sum = %d\n", tr[20].sum);

	for (int i = 1; i <= n; ++i) {
	//	printf("l[%d] = %d, r[%d] = %d\n", a[i].id, l[a[i].id], a[i].id, r[a[i].id]);
		ans = max(ans, query(root[l[a[i].id]], root[r[a[i].id]], a[i].zhi));
	}
	printf("%d\n", ans);
}
