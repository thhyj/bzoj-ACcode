
#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <ctime>
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
int main() {
	int T,a[12],d;
	R(T);
	char ch;
	int cnt;
	long long s;
	int ans=0;
	for(int o=1;o<=T;++o) {
		cnt=0;
		ans=0;
		do {
			ch=getchar();
		} while(!isdigit(ch));
		a[++cnt]=ch-47;
		while(ch=getchar()) {
			if(ch==' ') break;
			a[++cnt]=ch-47;
		}
		sort(a+1,a+cnt+1);
	////	for(int i=1;i<=cnt;++i)
	//		cout<<a[i]<<' ';
	//	cout<<'\n';
		R(d);
	//	cout<<"d="<<d<<'\n';
		do {
			s=0;
		//	for(int i=1;i<=cnt;++i) 	cout<<a[i]<<' ';
		//	cout<<'\n';
			for(int i=1;i<=cnt;++i)
				s=(s+(s<<2)<<1)+(a[i]-1);
		//	cout<<s<<'\n';
			if(s%d==0) ++ans;	
		} while(next_permutation(a+1,a+cnt+1));
		cout<<ans<<'\n';
	}
	return 0;
}
