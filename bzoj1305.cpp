
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cmath>
#include<vector>
using namespace std;
const int inf=2100000000;
inline void R(int &v) {
	static char ch;
	v=0;
	bool p=0;
	do{
		ch=getchar();
		if(ch=='-'){
			p=1;
		}
	}while(!isdigit(ch));
	while(isdigit(ch)){
		v=(v+(v<<2)<<1)+(ch^'0');
		ch=getchar();
	}
	if(p)
		v=-v;
}
int n,k;
bool ma[55][55];
struct node{
	int length,pa,to;
	node(int to,int length,int pa):to(to),length(length),pa(pa){
	}
	node(){
	}
};
vector<node>q[300];
int dis[300],gap[300],temp[300];
inline void create(const int &x,const int &y,const int &z){
	 q[x].push_back(node(y,z,q[y].size()));
	 q[y].push_back(node(x,0,q[x].size()-1));
}
inline int sap(int x,int flow,const int &s,const int &t){
	if(x==t)
		return flow;
	int ret=0;
	
	int f;
	//cout<<"x="<<x<<'\n';
	for(int i=temp[x];i<q[x].size();++i){
		node *p=&q[x][i];
		if(dis[x]==dis[p->to]+1&&p->length){
			f=sap(p->to,min(flow-ret,p->length),s,t);
			p->length-=f;
			q[p->to][p->pa].length+=f;
			temp[x]=i;
			if((ret+=f)==flow)return flow;	
		}
	}
	temp[x]=0;
	if(!(--gap[dis[x]])) dis[s]=4*n+2;
	gap[++dis[x]]++;
	return ret;
}
int main() {
//	scanf("%d%d",&n,&k);
	R(n);
	R(k);
	int s=0,t=n*4+1;
	//cout<<"t="<<t<<'\n';
	char ch[101];
	for(int i=1;i<=n;++i){
		scanf("%s",ch);
		for(int j=0;j<n;++j){
			if(ch[j]=='Y'){
				ma[i][j+1]=1;
			}
		}
	}
	for(int a=1;a<=n;++a)
	{
		int ans=0;
		memset(dis,0,sizeof(dis));
		memset(q,0,sizeof(q));
		memset(gap,0,sizeof(gap));
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(ma[i][j])
					{
						create(i,j+n,1);
					//	cout<<"i="<<i<<" j="<<j<<'\n'; 
					}
				else
					create(i+n*2,j+n*3,1);
			}
		}
		for(int i=1;i<=n;++i){
			create(i,i+n*2,k);
			create(i+n*3,i+n,k);
		}
		for(int i=1;i<=n;++i){
			create(s,i,a);
			create(i+n,t,a);
		}
		gap[0]=4*n+2;
	//	cout<<"a="<<a<<'\n';
		while(dis[s]<4*n+2)	ans+=sap(s,inf,s,t);
	//	cout<<"ans="<<ans<<'\n';
		if(ans<a*n){
			cout<<a-1;
			return 0;
		}
	}
	cout<<n;
	return 0;
}
