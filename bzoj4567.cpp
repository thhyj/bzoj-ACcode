
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <vector>
using namespace std;
struct trie {
	int cnt,son[26];
}tr[510005];
int tot;
inline void build(char *s,const int &bianhao){
	int len=strlen(s),pos=1;
	for(int i=len-1;i>=0;--i) {
		if(!tr[pos].son[s[i]-'a']) {
			tr[pos].son[s[i]-'a']=++tot;
		}
		pos=tr[pos].son[s[i]-'a'];
	}
	tr[pos].cnt=1;
}

vector<int>q[500100];
int cnt1;
int tms[500010];
void getedge(int x) {
//	cout<<" 123x="<<x<<'\n';
	if(tr[x].cnt){
			q[tms[x]].push_back(++cnt1);
			tms[x]=cnt1;
	}
	for(int i=0;i<26;++i) {
		if(tr[x].son[i]){
			tms[tr[x].son[i]]=tms[x];
			getedge(tr[x].son[i]);
		}
	}
}
int siz[510001];
inline bool cmp1(int a,int b){
	return siz[a]<siz[b];
}
void getsiz(int x) {
	siz[x]=1;
	//cout<<"x="<<x<<'\n';
	for(int i=0;i<q[x].size();++i){
		getsiz(q[x][i]);
		siz[x]+=siz[q[x][i]];
	}

}
int xuhao[510001];
long long ans;
int cnt;
void dfs1(int x) {
	xuhao[x]=++cnt;
	sort(q[x].begin(),q[x].end(),cmp1);
	for(int i=0;i<q[x].size();++i) {
		ans+=cnt+1-xuhao[x];
		dfs1(q[x][i]);
	}
}
int main() {
	//freopen("in.in","r",stdin);
	int n;
	cin>>n;
	//cout<<"n="<<n<<'\n';
	char s[510000];
	tot=1;
	for(int i=1;i<=n;++i) {
		cin>>s;
		build(s,i);
	}
	cnt1=1;
	tms[1]=1;
	getedge(1);
	//for(int i=1;i<=n;++i){
	//	for(int j=0;j<q[i].size();++j){
			//cout<<"i="<<i<<" j="<<j<<" "<<q[i][j]<<' ';
	//	}
	//	cout<<'\n';
//	}
	getsiz(1);
	tot=0;
	//for(int i=1;i<=n;++i){
	//	cout<<siz[i]<<'\n';
	//}
	dfs1(1);
	cout<<ans;
	return 0;
}
