
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
const int maxl=10010,P=10000;
using namespace std;
int n,m;

struct bign{
	int v[maxl],len;
	void del0(){while (len>1&&!v[len-1]) len--;}
	void clear(){memset(v,0,sizeof(v)),len=1;}
	bign operator *(const bign &b){
		bign c;c.clear();
		c.len=len+b.len;
		for (int i=0;i<len;i++)
			for (int j=0;j<b.len;j++){
				c.v[i+j]+=v[i]*b.v[j];
				if (c.v[i+j]>P) c.v[i+j+1]+=c.v[i+j]/P,c.v[i+j]%=P;
			}
		c.del0();return c;
	}
	bign operator +(const bign &b){
		bign c;c.clear();
		c.len=max(len,b.len)+1;
		for (int i=0;i<c.len;i++){
			c.v[i]+=v[i]+b.v[i];
			if (c.v[i]>P) c.v[i+1]++,c.v[i]-=P;
		}
		c.del0();return c;
	}
	void write(){
		printf("%d",v[len-1]);
		for (int i=len-2;i>=0;i--) printf("%04d",v[i]);
		puts("");
	}
};

bign fact(int a,int b){
	bign res;res.clear();
	if (a>b) return res;
	res.v[0]=1;
	for (int i=a;i<=b;i++){
		bign pp;pp.clear(),pp.v[0]=i;
		res=res*pp;
	}
	return res;
}
bign A(int n,int m){
	if (!m){
		bign res;res.clear(),res.v[0]=1;
		return res;
	}
	if (m>n){bign res;res.clear();return res;}
	return fact(n-m+1,n);
}
//A(n,n)*(A(n+1,2)*A(n+3,m)+A(m,1)*A(2,2)*A(n+1,1)*A(n+2,m-1))

int main(){
	scanf("%d%d",&n,&m);
	bign ans=A(n,n)*(A(n+1,2)*A(n+3,m)+A(m,1)*A(2,2)*A(n+1,1)*A(n+2,m-1));
	ans.write();
	return 0;
}
