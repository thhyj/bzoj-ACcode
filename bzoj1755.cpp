
#include <bits/stdc++.h>
using namespace std;
double r, m, y;
int main () {
	scanf("%lf%lf%lf", &r, &m, &y);
	r /= 100;
	for (int i = 1; i <= y; ++i) {
		m = m * (1 + r);
	}
	printf("%d\n", (int)m);
}
