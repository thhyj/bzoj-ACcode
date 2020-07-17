
#include <bits/stdc++.h>
using namespace std;
int n;
int a[10005];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	nth_element(a + 1,a + (n + 1) / 2, a + n + 1);
	printf("%d\n", a[(n + 1)/2]);
}
