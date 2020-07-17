
#include <cstdio>
using namespace std;
int n,maxa,maxn;
int main () {
	scanf("%d",&n);
	int x;
	for(int i=1;i<=n;++i) {
		scanf("%d",&x);
		if((maxa^x)) {
			if(!maxn) maxn=1,maxa=x;
			else --maxn;
		} else ++maxn; 
	}
	printf("%d",maxa);
	return 0;
}
