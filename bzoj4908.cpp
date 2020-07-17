
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cassert>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll mod=1000000007;
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
// head


const int N=201000,M=1000;
int lim,a[N],n,x,y,Q;
ll ret;
struct node {
	PII pos;
	int ty,sum;
}q[N*2];
bool operator < (node a,node c) { return a.pos<c.pos; }
struct block {
	node q[M];
	ll sa[M],sb[M],r;
	int offset,sz,pres,fg;
	block* nxt;
	void build();
	void gaopres(int x);
	void del(int x);
	void add(int x);
}nd[M*2],*cur=nd,*bl[N];
void block::build() {
	int s=pres,ms=s,ns=s;
	ret-=r; fg=0;
	rep(i,0,sz) {
		s+=q[i].ty;
		q[i].sum=s;
		ms=min(ms,q[i].sum);
		ns=max(ns,q[i].sum);
		bl[q[i].pos.se]=this;
	}
	offset=ms;
	rep(i,0,sz+1) sa[i]=sb[i]=0;
	r=0;
	rep(i,0,sz) {
		if (q[i].ty==-1) {
			sa[q[i].sum-offset]+=q[i].pos.fi;
			if (q[i].sum>=0) r+=q[i].pos.fi;
			else r-=q[i].pos.fi;
		}
		else {
			sb[q[i].sum-offset]+=q[i].pos.fi;
			if (q[i].sum<=0) r+=q[i].pos.fi;
			else r-=q[i].pos.fi;
		}
	}
	ret+=r;
}
void block::gaopres(int x) {
	ret-=r;
	if (x==1) {
		if (-offset-1>=0&&-offset-1<=sz) r+=2*sa[-offset-1];
		if (-offset>=0&&-offset<=sz) r-=2*sb[-offset];
	} else {
		if (-offset>=0&&-offset<=sz) r-=2*sa[-offset];
		if (-offset+1>=0&&-offset+1<=sz) r+=2*sb[-offset+1];
//		printf("oo %d %lld\n",offset,r);
	}
	ret+=r;
	offset+=x; pres+=x; fg+=x;
}
void block::del(int x) {
	rep(i,0,sz) if (q[i].pos.se==x) {
		rep(j,i,sz) q[j]=q[j+1];
		--sz;
		break;
	}
	build();
	block *p=nxt;
	while (p) p->gaopres(1),p=p->nxt;
	if (nxt&&sz+nxt->sz<lim) {
		rep(j,0,nxt->sz) q[j+sz]=nxt->q[j];
		sz+=nxt->sz; ret-=nxt->r;
		nxt=nxt->nxt;
		build();
	}
}
void block::add(int x) {
	int ff=sz;
	rep(i,0,sz) if (q[i].pos>mp(a[x],x)) {
		ff=i; break;
	}
	per(j,ff,sz) q[j+1]=q[j]; q[ff].pos=mp(a[x],x); q[ff].ty=-1; ++sz;
	build();
	block *p=nxt;
	while (p) p->gaopres(-1),p=p->nxt;
	if (sz>2*lim) {
		block *r=cur++;
		r->sz=sz-lim; r->pres=q[lim-1].sum+fg;
		rep(i,lim,sz) r->q[i-lim]=q[i];
		sz=lim;
		build(); r->build();
		r->nxt=nxt; nxt=r;
	}
}
int main() {
//	freopen("driver.in","r",stdin);
//	freopen("driver.out","w",stdout);
	scanf("%d",&n);
	rep(i,0,n) {
		scanf("%d",&x); a[i]=x;
		q[i].pos.fi=x; q[i].pos.se=i;
		q[i].ty=-1;
	}
	rep(i,0,n) {
		scanf("%d",&x);
		q[i+n].pos.fi=x; q[i+n].pos.se=i+n;
		q[i+n].ty=1;
	}
	sort(q,q+2*n);
	lim=sqrt(2*n);
	int s=0;
	rep(i,0,(2*n-1)/lim+1) {
		int l=i*lim,r=min((i+1)*lim,2*n);
		nd[i].pres=s;
		rep(j,l,r) nd[i].q[j-l]=q[j],s+=q[j].ty;
		nd[i].sz=r-l;
		nd[i].build();
		if (i>0) nd[i-1].nxt=nd+i;
		cur=nd+i+1;
	}
	printf("%lld\n",ret);
	scanf("%d",&Q);
	rep(i,0,Q) {
		scanf("%d%d",&x,&y); --x;
		a[x]=y;
		bl[x]->del(x);
		block *h=nd;
		while (h) { if (h->nxt&&h->nxt->sz==0) h->nxt=h->nxt->nxt; else h=h->nxt; }
		h=nd;
		while (h) {
			if (!h->nxt||h->nxt->q[0].pos>mp(a[x],x)) { h->add(x); break; }
			h=h->nxt;
		}
		printf("%lld\n",ret);
	}
}
