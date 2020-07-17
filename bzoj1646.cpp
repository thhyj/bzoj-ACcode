
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
const int MAXN=500001;
bool visit[MAXN];
vector <int> Q;
struct xx
{
	int s,cnt;
}a[MAXN];
int main(int argc, char *argv[])
{
	int n,k,head,tail,d=0,zt,i;
	scanf("%d%d",&n,&k);
	a[1].s=n;
	head=1,tail=1;
	while(head<=tail)
	{
		zt=tail;
		for(i=head;i<=tail;i++)
		{
			if(a[i].s==k) {
				printf("%d\n",a[i].cnt);
				return 0;
			}
			if(a[i].s+1<MAXN)
			if(visit[a[i].s+1]==false) 
			{
				zt++;
				a[zt].s=a[i].s+1;
				a[zt].cnt=a[i].cnt+1;
				visit[a[zt].s]=true;
			}
			if(a[i].s-1>=0)
			if(visit[a[i].s-1]==false) 
			{
				zt++;
				a[zt].s=a[i].s-1;
				a[zt].cnt=a[i].cnt+1;
				visit[a[zt].s]=true;
			}
			if(a[i].s*2<MAXN)
			if(visit[a[i].s*2]==false) 
			{
				zt++;
				a[zt].s=a[i].s*2;
				a[zt].cnt=a[i].cnt+1;
				visit[a[zt].s]=true;
			}
			head=tail+1;
			tail=zt;
		}
	}
	return 0;
}
