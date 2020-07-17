
#include <bits/stdc++.h>
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
int T, p;
int phi[10000005];
bool heshu[10000005];
int sushu[10000005];
int tot;
inline void xianshai() {
	phi[1] = 1;
	for (int i = 2 ; i <= 10000000; ++i) {
		if (!heshu[i]) sushu[++tot] = i, phi[i] = i - 1;
		for (int j = 1; j <= tot && sushu[j] * i <= 10000000; ++j) {
			if (i % sushu[j] == 0) {
				phi[i * sushu[j]] = sushu[j] * phi[i];
				heshu[i * sushu[j]] = 1;
				break;
			} else {
				phi[i * sushu[j]] = (sushu[j] - 1) * phi[i];
				heshu[i * sushu[j]] = 1;
			}
		}
	}
}
inline long long pow1(long long a,int n,int p) {
	long long ans=1;
    while(n) {
    if(n&1) ans=ans*a%p;
    a=a*a%p; n>>=1;
    }
    return ans;
}
inline int calc(int x) {
	if(x == 1) return 0;
	int t = x, k = 0;
	while(!(t & 1)) {
		++k;
		t /= 2;
	}
	return pow1(2, ((calc(phi[t]) % phi[t] - k % phi[t] + phi[t]) % phi[t] + phi[t]), t) << k;
}
int main () {
	xianshai();
	R(T);
	int x;
	while (T--) {
		R(p);
		printf("%d\n",calc(p));
	}
}
