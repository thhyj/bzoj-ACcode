
#include<iostream>
#include<cstdio>
#include<algorithm>
#define LL long long
using namespace std;
inline void R (LL &v) {
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
const int MAXN = 2000;

LL l, r, arr[MAXN], tmp[MAXN], vout, cnt, tot;

void DFS(LL w) {
    if (w > r) return;
    tmp[++cnt] = w;
    DFS(w * 10 + 2);
    DFS(w * 10 + 9);
}

inline void prework() {
    DFS(2); DFS(9);
    sort(tmp + 1, tmp + cnt);
    for (LL i = 1, tag = 0; i <= cnt; i++, tag = 0) {
        for (LL j = i - 1; j; j--) if (tmp[i] % tmp[j] == 0) {tag = 1; break;}
        if (!tag) arr[++tot] = tmp[i];
    }
    reverse(arr + 1, arr + 1 + tot);
}


void solve(LL step, LL sz, LL w) {
    if (step == tot + 1) {
        if (sz & 1) vout += r / w - (l - 1) / w;
        else if (sz) vout -= r / w - (l - 1) / w;
    } else {
        solve(step + 1, sz, w);
        LL buf = (LL)w / __gcd(w, arr[step]) * arr[step];
        if (buf <= r) solve(step + 1, sz + 1, buf);
    }
}

int main() {
    R(l), R(r);
    prework();
   // cout<<"tot = <<tot<<'\n";
  //  for(int i = 1; i <= tot; ++i) {
  //  	cout<<arr[i]<<'\n';
//	}
    solve(1, 0, 1);
    cout<<vout<<'\n';
    return 0;
}
