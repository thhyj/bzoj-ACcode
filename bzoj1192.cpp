
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
int main () {
	long long a;
	cin>>a;
	cout<<(floor)(log2(a)+1);
}
