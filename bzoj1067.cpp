
#include <bits/stdc++.h>
using namespace std;
map<int, int>ma;
inline void R(int &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
		ch = getchar();
		if (ch == '-') {
			p = 1;
		}
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = (v + (v << 2) << 1) + (ch^'0');
		ch = getchar();
	}
	if (p) v = -v;
}
struct lisan {
	int ord;
	int zhi;
	int rain;
} num[50005];
struct tree {
	int son[2], sum, max, min;
} tr[800005];
int tot;
inline void updata(const int &x) {
	tr[x].max = max(tr[tr[x].son[0]].max, tr[tr[x].son[1]].max);
	tr[x].min = min(tr[tr[x].son[0]].min, tr[tr[x].son[1]].min);
}
inline void add(const int &x , const int &pos, const int &v, const int &l, const int &r) {
	if (l == r) {
		//	cout<<"l="<<l<<" r="<<r<<" v="<<v<<'\n';
		tr[x].min = v;
		tr[x].max = v;
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid) {
		if (!tr[x].son[0]) {
			tr[x].son[0] = ++tot;
		}
		add(tr[x].son[0], pos , v , l , mid);
	} else {
		if (!tr[x].son[1]) {
			tr[x].son[1] = ++tot;
		}
		add(tr[x].son[1], pos, v, mid + 1, r);
	}
	updata(x);
}
inline int querymin(const int &x , const int &ql, const int & qr, const int &l, const int &r) {
	if (l >= ql && r <= qr) {
		return tr[x].min;
	}
	//cout<<"ql="<<ql<<" qr="<<qr<<'\n';
	int mid = l + r >> 1;
	int ret = 2000000000;
	if (ql <= mid) {
		if (!tr[x].son[0]) return 0;
		ret = min(ret, querymin(tr[x].son[0], ql, qr, l, mid));
	}
	if (qr > mid) {
		if (!tr[x].son[1]) return 0;
		ret = min(ret, querymin(tr[x].son[1], ql, qr, mid + 1, r));
	}
	return ret;
}
inline int querymax(const int &x , const int &ql, const int & qr, const int &l, const int &r) {
	if (l >= ql && r <= qr) {
		//cout << "l=" << l << " r=" << r << " max=" << tr[x].max << '\n';
		return tr[x].max;
	}
	//cout<<"l="<<l<<" r="<<r<<'\n';
	int mid = l + r >> 1;
	int ret = 0;
	if (ql <= mid) {
		if (tr[x].son[0])
			ret = max(ret, querymax(tr[x].son[0], ql, qr, l, mid));
	}
	if (qr > mid) {
		if (tr[x].son[1])
			ret = max(ret, querymax(tr[x].son[1], ql, qr, mid + 1, r));
	}
	return ret;
}
int a[50005], b[50005];
int main () {
	int n;
	memset(a, -1, sizeof(a));
	int x;
	R(n);
	//cout<<"n="<<n<<'\n';
	int root = 1;
	int tot = 1;
	int y;
	for (int i = 1; i <= n; ++i) {
		R(x);
		//cout<<"x="<<x<<'\n';
		R(y);
		ma[x] = y;
		//	cout<<"a[x]="<<a[x]<<'\n';
		add(root, x, y, -1000000000, 1000000000);
	}
	int m;
	R(m);
	int l;
	for (int i = 1; i <= m; ++i) {
		R(l); R(x);
		++l;
		if (ma.find(x) == ma.end()) {
			if(ma.find(l-1) == ma.end())
			cout << "maybe\n"; else {
				if( querymax(root, l, x, -1000000000, 1000000000)<ma[l-1]) 
					cout<<"maybe\n"; else 
				cout<<"false\n";
			}
			continue;
		}
		int temp = querymax(root, l, x-1, -1000000000, 1000000000);
		if(ma.find(l-1) != ma.end()) {
			if(ma[l-1]<ma[x]) {
				cout<<"false\n";continue;
			}
		}
		if (temp < ma[x]) {
			//	cout<<"min="<<querymin(root, l, x, -1000000000, 1000000000)<<'\n';
			if (ma.find(l-1) != ma.end()) {
				if(ma[l-1]< temp) {
					cout<<"false\n";
					continue;
				}
			} 
			if (querymin(root, l, x, -1000000000, 1000000000) == 0) {
				cout << "maybe\n";
			} else if (ma.find(l-1) == ma.end()) {
				cout << "maybe\n";
			} else if(ma[l-1]>= temp)
				cout << "true\n";
				else cout<<"false\n";
		} else {
			cout << "false\n";
		}
	}
	return 0;
}
