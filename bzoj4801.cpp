
#include <bits/stdc++.h>
using namespace std;
inline void R(int &v) {
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
int main() {
	int T;
	R(T);
	int a, b, c, d;
	int q, t;
	char s[3];
	int ans;
	int ans1, ans2, ans3;
	while (T--) {
		q = t = 0;
		ans = ans1 = ans2 = ans3 = 0;
		scanf("%s", s);
		if (isdigit(s[0])) a = s[0] - '0';
		else {
			switch (s[0]) {
			case 'T' : a = 10 ; break;

			case 'A' : a = 14; break;
			case 'J' : a = 11; break;
			case 'Q' : a = 12; break;
			case 'K' : a = 13; break;
			}
		}		scanf("%s", s);
		if (isdigit(s[0])) b = s[0] - '0';
		else {
			switch (s[0]) {
			case 'T' : b = 10 ; break;

			case 'A' : b = 14; break;
			case 'J' : b = 11; break;
			case 'Q' : b = 12; break;
			case 'K' : b = 13; break;
			}
		}		scanf("%s", s);
		if (s[0] == '1' && s[1] == '0') c = 10;
		else if (isdigit(s[0])) c = s[0] - '0';
		else {
			switch (s[0]) {
			case 'T' : c = 10 ; break;

			case 'A' : c = 14; break;
			case 'J' : c = 11; break;
			case 'Q' : c = 12; break;
			case 'K' : c = 13; break;
			}
		}		scanf("%s", s);
		if (isdigit(s[0])) d = s[0] - '0';
		else {
			switch (s[0]) {
			case 'T' : d = 10 ; break;
			case 'A' : d = 14; break;
			case 'J' : d = 11; break;
			case 'Q' : d = 12; break;
			case 'K' : d = 13; break;
			}
		}
		//	printf("a=%d, b=%d, c=%d, d=%d\n",a,b,c,d);

		if (c > a) {								//a->c, b->d
			if (c != 14)
				ans1 -= c;
			else ans1 -= 1;
			if (d >= b) {
				if (d != 14)
					ans1 -= d; else ans1 -= 1;
			}
			else if (b != 14)ans1 += b; else ans1 += 1;
		} else {
			if (a != 14)
				ans1 += a;
			else ans1 += 1;
			if (d > b) {
				if (d != 14)
					ans1 -= d; else ans1 -= 1;
			}
			else if (b != 14)ans1 += b; else ans1 += 1;
		}
		if (d > a) {								//a->d,b->c
			if (d != 14)
				ans2 -= d;
			else ans2 -= 1;
			if (c >= b) {
				if (c != 14)
					ans2 -= c; else ans2 -= 1;
			}
			else if (b != 14)ans2 += b; else ans2 += 1;
		} else {
			if (a != 14)
				ans2 += a;
			else ans2 += 1;
			if (c > b) {
				if (c != 14)
					ans2 -= c; else ans2 -= 1;
			}
			else if (b != 14)ans2 += b; else ans2 += 1;
		}
		ans1 = min(ans2,ans1);
		if (c > b) {							//b->c, a->d
			if (c != 14)
				ans -= c;
			else ans -= 1;
			if (d >= a) {
				if (d != 14)
					ans -= d; else ans -= 1;
			}
			else if (a != 14)ans += a; else ans += 1;
		} else {
			if (b != 14)
				ans += b;
			else ans += 1;
			if (d > a) {
				if (d != 14)
					ans -= d; else ans -= 1;
			}
			else if (a != 14)ans += a; else ans += 1;
		}
		if (d > b) {							//b->d,a->c
			if (d != 14)
				ans3 -= d;
			else ans3 -= 1;
			if (c >= a) {
				if (c != 14)
					ans3 -= c; else ans3 -= 1;
			}
			else if (a != 14)ans3 += a; else ans3 += 1;
		} else {
			if (b != 14)
				ans3 += b;
			else ans3 += 1;
			if (c > a) {
				if (c != 14)
					ans3 -= c; else ans3 -= 1;
			}
			else if (a != 14)ans3 += a; else ans3 += 1;
		}
		ans = min(ans, ans3);
		printf("%d\n", max(ans,ans1));
	}
}
