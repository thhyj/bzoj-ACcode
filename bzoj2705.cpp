
#include <bits/stdc++.h>
using namespace std;
inline void R (long long &v) {
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
long long n;
inline long long getphi(long long x) {
	long long temp = sqrt(x);
	long long t = x, ans = x;
	for (long long i = 2; i <= temp; ++i ) {
		if (t % i == 0) {
			ans = ans * (i - 1) / i;
			while (t % i == 0)	 t /= i;
		}
	}
	if (t > 1) ans = ans * (t - 1) / t;
	return ans;
}

int main() {
	R(n);
	long long temp = sqrt(n);
	long long ans = 0;
	for (long long i = 1; i <= temp; ++i) {
		if (n % i == 0) {
			ans += (n / i) * getphi(i) + (n / (n / i)) * getphi(n / i);
		}
	}
	cout << ans << '\n';
	return 0;
}
