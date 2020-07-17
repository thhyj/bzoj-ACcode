
#include <bits/stdc++.h>
using namespace std;
double a[100005], yi[100005], er[100005], san[100005];
int main () {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lf", &a[i]);
	}
	for (int i = 1; i <= n; ++i) {
		yi[i] = (yi[i - 1] + 1) * a[i];
		er[i] = (er[i - 1] + 2 * yi[i - 1] + 1) * a[i];
		san[i] = san[i - 1] + (er[i - 1] * 3 + yi[i - 1] * 3 + 1) *  a[i];
	}
	printf("%0.1f\n", san[n]);
	return 0;
}
