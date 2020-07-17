
#include <bits/stdc++.h>
#define eps 1e-20
#define inf 1e15
using namespace std;
inline void R(int &v) {
	static char ch;
	bool p = 0;
	v = 0;
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
using namespace std;
inline void R(long long &v) {
	static char ch;
	bool p = 0;
	v = 0;
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
inline void R(long double &v) {
	static char ch;
	bool p = 0;
	v = 0;
	do {
		ch = getchar();
		if (ch == '-') p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = v * 10 + (ch^'0');
		ch = getchar();
	}
	if (p) v = -v;
}
long long A, B, C, l, r, t[100010], b[100010];
int n, m;

long long check(long long x) {
	long long cost = 0;
	if (A < B) {
		long long left = 0, nd = 0;
		for (int i = 1; i <= m; i++)  if (b[i] < x)  left += x - b[i];
		for (int i = 1; i <= m; i++)  if (b[i] > x)  nd += b[i] - x;
		if (left >= nd)  cost += nd * A;
		else cost += left * A + (nd - left) * B;
	}
	else  for (int i = 1; i <= m; i++)  if (b[i] > x)  cost += (b[i] - x) * B;
	for (int i = 1; i <= n; i++)  if (t[i] < x)  cost += (x - t[i]) * C;
	return cost;
}

int main() {
//	freopen("exam.in", "r", stdin);
	R(A), R(B), R(C);
	R(n), R(m);
	for (int i = 1; i <= n; i++)  R(t[i]);
	for (int i = 1; i <= m; i++)  R(b[i]);
	if (C == 1e16) {
		long long mi = 1e18;
		for (int i = 1; i <= n; i++)  mi = min(mi, t[i]);
		cout << check(mi);
		return 0;
	}
	l = 1, r = 100005;
	while (l + 2 < r) {
		long long mid1 = (2 * l + r) / 3, mid2 = (2 * r + l) / 3;
		long long v1 = check(mid1), v2 = check(mid2);
		if (v1 == v2)  l = mid1,  r = mid2;
		else if (v1 < v2)  r = mid2;
		else  l = mid1;
	}
	long long v1 = check(l), v2 = check(r), v3 = check((2 * l + r) / 3), v4 = check((2 * r + l) / 3);
	cout << min(min(v1, v2), min(v3, v4));
	return 0;
}
