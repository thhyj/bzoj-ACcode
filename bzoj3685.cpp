
#include <bits/stdc++.h>
using namespace std;
inline char read() {
    static const int IN_LEN = 1000000;
    static char buf[IN_LEN], *s, *t;
    s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin) : 0;
    return s == t ? -1 : *s++;
}

template<class T>
inline void read(T &x) {
    static char c;
    static bool iosig;
    for (c = read(), iosig = false; !isdigit(c); c = read()) {
        if (c == -1) return;
        c == '-' ? iosig = true : 0;
    }
    for (x = 0; isdigit(c); c = read())
        x = (x + (x << 2) << 1) + (c ^ '0');
    iosig ? x = -x : 0;
}
set<int>q;
int main () {
	//freopen("in.in","r",stdin);
	int n, m;
	read(n), read(m);
	int k, x;
	set<int>::iterator iter, rater;
	for (int i = 1; i <= m; ++i) {
		read(k);
		switch (k) {
		case 1:
			read(x);
			q.insert(x);
			break;
		case 2:
			read(x);
			q.erase(x);
			break;
		case 3:
			(!q.size()) ?
			puts("-1") :
			printf("%d\n", *q.begin());
			break;
		case 4:
			(!q.size()) ?
			puts("-1") :
			printf("%d\n", *(--q.end()));
			break;
		case 5:
			read(x);
			iter = q.lower_bound(x);
			if(iter == q.begin())
				puts("-1");
			else {
				printf("%d\n",*(--iter));
			}
			break;
		case 6:
			read(x);
			iter = q.upper_bound(x);
			if(iter == q.end())
				puts("-1");
			else {
				printf("%d\n",*(iter));
			}
			break;
		case 7:
			read(x);
			q.count(x) == 1 ? puts("1") :puts("-1");
			break;
		}
	}
	return 0;
}
