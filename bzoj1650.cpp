
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
inline void R(int &v) {
	v=0;
	char c=0;
	bool p=true;
	while(c>'9'||c<'0') {
		if(c=='-') {
			p=false;
		}
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		v=(v<<3)+(v<<1)+c-'0';
		c=getchar();
	}
	if(p==false) {
		v=-v;
	}
}
int l,n,m,d[50005];
bool pd(int mid) {
	int num=0,last=0;
	for(int i=1; i<=n; i++) {
		if(d[i]-last<mid) {
			num++;
		} else
			last=d[i];
		if(num>m)
			return 0;
	}
	if(l-last<mid) {
		num++;
	}
	if(num>m) {
		return 0;
	} else {
		return 1;
	}
}
int main() {
	cin>>l>>n>>m;
	for(int i=1; i<=n; i++) {
		cin>>d[i];
	}
	sort(d+1,d+n+1); 
	int ri,le;
	ri=1000000001;
	le=0;
//while(le<=ri)
	int ans=0;
	for(int i=1; i<=100; i++) {
		int mid=(ri+le)>>1;
		if(pd(mid)) {
			ans=mid;
			le=mid;
		} else {
			ri=mid;
		}
	}
	cout<<ans;
	return 0;
}
