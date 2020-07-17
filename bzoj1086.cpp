
#include <bits/stdc++.h>
using namespace std;
inline void R(int &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
		ch = getchar();
		if (ch == '-')
			p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = (v + (v << 2) << 1) + (ch^'0');
		ch = getchar();
	}
	if (p) v = -v;
}
vector<int>q[10005];
vector<int>st;
inline void create(const int &x , const int &y) {
	q[x].push_back(y);
	q[y].push_back(x);
}
int bl[10005];
int shenghui[10005];
int cnt;
int n, b;
inline void dfs(const int &x, const int &fa) {
	int p;
	int sz;
	int temp;
	sz = st.size();
	for (int i = 0; i < q[x].size(); ++i) {
		p = q[x][i];
		if (p ^ fa) {
			dfs(p , x);
			if (st.size() - sz >= b) {
				shenghui[++cnt] = x;
				while (st.size()^sz) {
					temp = st.back();
					st.pop_back();
					bl[temp] = cnt;
				}
			}
		}
	}
	st.push_back(x);
}
int main () {
	R(n), R(b);
	int x, y;
	for (int i = 1; i < n; ++i) {
		R(x), R(y);
		create(x, y);
	}
	dfs(1, 1);
	int temp;
	//shenghui[++cnt] = 1;
	while (!st.empty()) {
		temp = st.back();
		st.pop_back();
		bl[temp] = cnt;
	}
	cout << cnt << '\n';
	for (int i = 1; i < n; ++i) {
		cout << bl[i] << ' ';
	}
	cout << bl[n] << '\n';
	for (int i = 1; i <= cnt; ++i) {
		cout << shenghui[i] << ' ';
	}
	return 0;
}
