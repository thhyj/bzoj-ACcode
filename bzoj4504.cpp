
#include <bits/stdc++.h>
using namespace std;
inline char read() {
	static const int IN_LEN = 1000000;
	static char buf[IN_LEN], *s, *t;
	if (s == t) {
		t = (s = buf) + fread(buf, 1, IN_LEN, stdin);
		if (s == t) return -1;
	}
	return *s++;
}

template<class T>
inline void R(T &x) {
	static char c;
	static bool iosig;
	for (iosig = false, c = read(); !isdigit(c); c = read()) {
		if (c == -1) return;
		if (c == '-') iosig = true;
	}
	for (x = 0; isdigit(c); c = read())
		x = (x + (x << 2) << 1) + (c ^ '0');
	if (iosig) x = -x;
}
struct data {
	int num;
	long long ma;
	data(long long ma, int num): ma(ma), num(num) {}
	data() {}
};
inline bool operator < (const data &a, const data&b) {
	return a.ma < b.ma;
}
priority_queue<data> dui;
struct tree {
	int ls, rs;
	long long all, max;
} tr[10000005];
inline void updata(int x) {
	if (!tr[x].ls) {
		tr[x].max = tr[tr[x].rs].max;
	} else {
		if (!tr[x].rs) tr[x].max = tr[tr[x].ls].max;
		else {
			tr[x].max = max(tr[tr[x].ls].max, tr[tr[x].rs].max);
		}
	}
	tr[x].max += tr[x].all;
}
int n, k;
int a[100005];
map<int, int>last;
int tot, root[100005];
inline void build(int pre, int &now, int l, int r, int pos) {
	now = ++tot;
	tr[now] = tr[pre];
	if (l == r) {
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid) {
		build(tr[pre].ls, tr[now].ls, l, mid, pos);
	} else build(tr[pre].rs, tr[now].rs, mid + 1, r, pos);
	updata(now);
}
inline void add(int pre, int &now, int l, int r, int al, int ar, int v) {
	now = ++tot;
	tr[now] = tr[pre];
	if (l == al && r == ar) {
		tr[now].all += v;
		updata(now);
		return;
	}
	int mid = l + r >> 1;
	if (ar <= mid) {
		add(tr[pre].ls, tr[now].ls, l, mid, al, ar, v);
	} else {
		if (al > mid) {
			add(tr[pre].rs, tr[now].rs, mid + 1, r, al, ar, v);
		} else {
			add(tr[pre].ls, tr[now].ls, l, mid, al, mid, v);
			add(tr[pre].rs, tr[now].rs, mid + 1, r, mid + 1, ar, v);
		}
	}
	updata(now);
}
inline void del(int pre, int &now , int l, int r) {
	now = ++tot;
	tr[now] = tr[pre];
	if (l == r) {
		tr[now].all = -1000000000000000000;
		updata(now);
		return;
	}
	int mid = l + r >> 1;
	if (!tr[pre].ls) {
		del(tr[pre].rs, tr[now].rs, mid + 1, r);
	} else {
		if (!tr[pre].rs) {
			del(tr[pre].ls, tr[now].ls, l, mid);
		} else {
			if (tr[tr[pre].ls].max > tr[tr[pre].rs].max) {
				del(tr[pre].ls, tr[now].ls, l, mid);
			} else 		del(tr[pre].rs, tr[now].rs, mid + 1, r);
		}
	}
	updata(now);
}
int main() {
	R(n), R(k);
	for (int i = 1; i <= n; ++i) {
		R(a[i]);
		//add(root[i - 1], root[i], 1, n, i, i, 0);
		build(root[i - 1], root[i], 1, n, i);
		add(root[i], root[i], 1, n, last[a[i]] + 1, i, a[i]);
		dui.push(data(tr[root[i]].max, i));
		last[a[i]] = i;
	}
	int temp;
	int prev;
	for (int i = 1; i < k; ++i) {
		temp = dui.top().num;
		dui.pop();
		del(root[temp], root[temp], 1, n);
		dui.push(data(tr[root[temp]].max, temp));
	}
	cout << dui.top().ma << '\n';
}
