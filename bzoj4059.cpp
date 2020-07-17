
#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <map>
using namespace std;
inline void R(int &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
	   ch = getchar();
	   if(ch == '-')
		   p = 1;
	}while(!isdigit(ch));
	while(isdigit(ch)) {
		v = (v + (v << 2) <<1) + (ch ^ '0');
		ch = getchar();
	}
	if(p)
		 v = -v;
}
int n;
int pre[2000005],nxt[2000005],a[2000005];
inline bool check (int l,int r) {
	int l1=l, r1=r;
	if(l>=r) return 1;
	for(int i=l;i<=r;++i) {
		if(i&1) {
			if(pre[l1]<l&&nxt[l1]>r) return check(l,l1-1)&&check(l1+1,r);
			++l1;
		} else {
			if(pre[r1]<l&&nxt[r1]>r) return check(l,r1-1)&&check(r1+1,r);
			--r1;
		}
	}
	return 0;
}	
map<int,int>mp;
int main() {
	int T;
	R(T);
	for(int o=1;o<=T;++o) {
		mp.clear();
		R(n);
		for(int i=1;i<=n;++i) {
			R(a[i]);
			pre[i]=mp[a[i]];
			nxt[mp[a[i]]]=i;
			mp[a[i]]=i;
		}
		for(int i=1;i<=n;++i) {
			nxt[mp[a[i]]]=n+1;
		}
		if(check(1,n)) {
			cout<<"non-boring\n";
		} else cout<<"boring\n";
	}
}
