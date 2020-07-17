
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 400005;

#define debug puts("here");

int p[X];

struct node{
	int x,y,next;
}edge[X*2];

int po[X],tol;
bool use[X];
int a[X],tot;
int vec[X];
int n,m;

void add(int x,int y){
	edge[++tol].x = x;
	edge[tol].y = y;
	edge[tol].next = po[x];
	po[x] = tol;
}

int find_set(int x){
	if(x!=p[x])
		p[x] = find_set(p[x]);
	return p[x];
}

void init(){
	memset(po,0,sizeof(po));
	tol = 0;
	for(int i=1;i<=n;i++){
		use[i] = true;
		p[i] = i;
	}
	int x,y;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		x ++;
		y ++;
		add(x,y);
		add(y,x);
	}
	cin >> tot;
	for(int i=1;i<=tot;i++){
		scanf("%d",&a[i]);
		a[i] ++;
		use[a[i]] = false;
	}
}

void solve(){
	int x,y,px,py;
	for(int i=1;i<=tol;i+=2){
		x = edge[i].x;
		y = edge[i].y;
		if(use[x]&&use[y]){
			px = find_set(x);
			py = find_set(y);
			p[px] = py;
		}
	}
	int ans = 0;
	for(int i=1;i<=n;i++)
		if(use[i]&&p[i]==i)
			ans ++;
	for(int i=tot;i;i--){
		vec[i] = ans;
		int x = a[i];
		use[x] = 1;
		ans ++;
		for(int j=po[x];j;j=edge[j].next){
			int y = edge[j].y;
			if(use[y]){
				py = find_set(y);
				px = find_set(x);
				if(px!=py){
					p[px] = py;
					ans --;
				}
			}
		}
	}
	vec[0] = ans;
	for(int i=0;i<=tot;i++)
		printf("%d\n",vec[i]);
}
int main(){
	cin >> n >> m;
	init();
	solve();
	return 0;
}
