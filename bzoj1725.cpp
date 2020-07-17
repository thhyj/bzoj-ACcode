
#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <algorithm>
#define rep(i,n) for(int i=0;i< (n);++i)
using namespace std;

typedef set<int> SI;
const int inf = 1000000000;
const int move[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
inline void upmax(int &x,int t){if(t>x)x=t;}
inline void upmin(int &x,int t){if(t<x)x=t;}

const int mod = 100000000;
inline void add(int &x,int t){if((x+=t)>=mod)x-=mod;}
int A[12][12];
int f[2][1<<13];
int n,m;

int main()
{
	//freopen("cowfood.in","r",stdin);
	//freopen("cowfood.out","w",stdout);

	scanf("%d%d",&n,&m);
	rep(i,n)rep(j,m)scanf("%d",&A[i][j]);
	
	int o=0,e=1,xxx=1<<m;
	f[e][0]=1;
	rep(i,n)rep(j,m)
	{
		swap(o,e);
		memset(f[e],0,sizeof(f[e]));
		rep(s,xxx)if(f[o][s])
		{
			int a=s&(1<<m-j-1);
			add(f[e][s-a],f[o][s]);
			if(A[i][j]==1&&a==0&&(s&(1<<m-j))==0)add(f[e][s|(1<<m-j-1)],f[o][s]);
		}
	}

	int res=0;
	rep(s,xxx)add(res,f[e][s]);
	printf("%d\n",res);

	return 0;
}
