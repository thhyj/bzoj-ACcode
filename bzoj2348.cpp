
#include <bits/stdc++.h>
using namespace std;
int a[100005];
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	sort(a + 1, a + n + 1);
	int l = 1, r = 1;
	long long ans = 0;
	for(r = 1; r <= n; ++r) {
		while (l < r && (long long)a[r] * 9 > (long long)a[l] * 10) {
			++l;
		}
		ans += r - l;
}
	cout << ans;
	return 0;
}
