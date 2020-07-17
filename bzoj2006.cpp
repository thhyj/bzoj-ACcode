
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
		v = (v + (v << 2) << 1) + (ch^'0');
		ch = getchar();
	}
	if (p) v = -v;
}
int n, k, l1, r1;
struct SUM {
	int zhi, ori;
} sum[500005];
int ls[500005], zhi[500005];
inline bool cmp(const SUM &a , const SUM &b) {
	return a.zhi < b.zhi;
}
struct tree {
	int ls, rs, sum;
} tr[10000005];
int tot;
int root[500005], kth[500005], qianzhui[500005];
inline void updata(int x) {
	tr[x].sum = tr[tr[x].ls].sum + tr[tr[x].rs].sum;
}
priority_queue< pair<int, int> >q;
inline void build(int prev, int &now, int l, int r, int v) {
	if (!now) now = ++tot;
	if (l == r) {
		tr[now].sum = tr[prev].sum + 1;
		return;
	}
	int mid = l + r >> 1;
	if (v <= mid) {
		tr[now].rs = tr[prev].rs;
		build(tr[prev].ls, tr[now].ls, l, mid, v);
	} else {
		tr[now].ls = tr[prev].ls;
		build(tr[prev].rs, tr[now].rs, mid + 1, r, v);
	}
	updata(now);
}
inline int query(int prev, int now, int l, int r, int k) {
//	if (tr[now].sum - tr[prev].sum < k) return 0;
	if (l == r) {
//		printf("l=%d\n", l);
		return zhi[l];
	}
	int mid = l + r >> 1, temp = tr[tr[now].ls].sum - tr[tr[prev].ls].sum;
	if (temp >= k) return query(tr[prev].ls, tr[now].ls, l, mid, k);
	else return query(tr[prev].rs, tr[now].rs, mid + 1, r, k - temp);
}
int main() {
//	freopen("in.in", "r", stdin);
	R(n), R(k), R(l1), R(r1);
	int x;
	for (int i = 1; i <= n; ++i) {
		R(x);
		sum[i].zhi = sum[i - 1].zhi + x;
		sum[i].ori = i;
		qianzhui[i] = sum[i].zhi;
		//	printf("sun[%d] = %d\n", i, sum[i].zhi);
	}
	sort(sum + 1, sum + n + 1, cmp);
	for (int i = 1; i <= n; ++i) {
		ls[sum[i].ori] = i;
		zhi[i] = sum[i].zhi;
	}
	for (int i = 1; i <= n; ++i) {
//		printf("ls[%d] = %d\n", i, ls[i]);
		build(root[i - 1], root[i], 1, n, ls[i]);
	}
	//for (int i = l1; i <= r1; ++i) {
	//	++kth[i];
	//	q.push(make_pair (qianzhui[i], i));
	//}
//	kth[4] = 1;
	for (int i = l1; i <= r1; ++i) {
		q.push(make_pair(qianzhui[i], i));
	}
	for (int i = l1 + 1; i <= n; ++i) {
		++kth[i];
//			printf("i = %d, l = %d, r = %d, kth = %d,  zuida = %d\n", i, max(0, i - r1), i - l1, kth[i], qianzhui[i] - query(root[max(0, i - r1 - 1)], root[i - l1], 1, n, kth[i]));
		q.push(make_pair (qianzhui[i] -  query(root[max(0, i - r1 - 1)], root[i - l1], 1, n, kth[i]), i));
	}
	pair<int, int> temp;
	long long ans = 0;
	for (int i = 1; i <= k; ++i) {
		temp = q.top();
		//	printf("temp.first = %d, temp.seocnd = %d\n", temp.first, temp.second);
		ans += temp.first;
		q.pop();
		++kth[temp.second];
		if ((temp.second - l1) - (max(0, temp.second - r1 - 1))>= kth[temp.second]) {
			//		printf("(temp.second - l1) - (max(0, temp.second - r1)) + 1 = %d\n", (temp.second - l1) - (max(0, temp.second - r1)) + 1);
//			printf("l = %d, r = %d, temp.second = %d, kth[%d] = %d, zuida = %d\n", max(0, temp.second - r1 - 1), temp.second - l1, temp.second, temp.second, kth[temp.second], qianzhui[temp.second] - query(root[max(0, temp.second - r1)], root[temp.second - l1], 1, n, kth[temp.second]));
			q.push(make_pair(qianzhui[temp.second] - query(root[max(0, temp.second - r1 - 1)], root[temp.second - l1], 1, n, kth[temp.second]), temp.second));
		}
	}
	printf("%lld\n", ans);
}
