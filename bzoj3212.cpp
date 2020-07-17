
#include<iostream>
#include<ctime>
#include<cstring>
#include<cctype>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
inline void R(long long &v)
{
    static char ch;
    v=0;
    bool p=0;
    do{
        ch=getchar();
        if(ch=='-')
        {
            p=1;
        }
    }while(!isdigit(ch));
    while(isdigit(ch))
    {
        v=(v<<1)+(v<<3)+(ch^'0');
        ch=getchar();
    }
    if(p)v=-v;
}
long long num[200005];
struct tree
{
    long long lson,rson,sum,tag;
}tr[800005];
long long tot;
long long root;
inline void update(long long x)
{
    tr[x].sum=tr[tr[x].lson].sum+tr[tr[x].rson].sum;
}
void build(long long now,long long l,long long r)
{
    if(l==r)
    {
        tr[now].sum=num[l];return;
    }
    long long mid=l+r>>1;
    if(!tr[now].lson)tr[now].lson=++tot;
    if(!tr[now].rson)tr[now].rson=++tot;
    build(tr[now].lson,l,mid);
    build(tr[now].rson,mid+1,r);
    update(now);
}
void downtag(long long x,long long l,long long r)
{
	if(tr[x].tag)
	{
		tr[tr[x].lson].tag+=tr[x].tag;
		tr[tr[x].rson].tag+=tr[x].tag;
        long long mid=l+r>>1;
		tr[tr[x].lson].sum+=tr[x].tag*(mid-l+1);
		tr[tr[x].rson].sum+=tr[x].tag*(r-mid);
		tr[x].tag=0;
	}
}
void add(long long now,long long al,long long ar,long long l,long long r,long long x)
{
    if(al<=l&&ar>=r)
	{
		tr[now].tag+=x;
		tr[now].sum+=x*(r-l+1);
		//cout<<"cur->r="<<cur->r<<" cur->l="<<cur->l<<" cur->zhi="<<cur->zhi<<"\n";
		return;
	}
    //if(!tr[now].lson)tr[now].lson=++tot;
    //if(!tr[now].rson)tr[now].rson=++tot;
    downtag(now,l,r);
	long long mid=r+l>>1;
	if(al<=mid)
	add(tr[now].lson,al,ar,l,mid,x);
	if(ar>mid)
	add(tr[now].rson,al,ar,mid+1,r,x);
	update(now);
}
long long query(long long now,long long ql,long long qr,long long l,long long r)
{
    //cout<<"l="<<l<<" r="<<r<<" now="<<now<<'\n';
	if(l>=ql&&r<=qr)
	{
    //    cout<<"now="<<now<<'\n';
        return tr[now].sum;}
	downtag(now,l,r);
	long long mid=l+r>>1;
	long long ret=0;
	if(qr>mid)
		ret+=query(tr[now].rson,ql,qr,mid+1,r);
//	cout<<"ret="<<ret<<"\n";
	if(ql<=mid)
		ret+=query(tr[now].lson,ql,qr,l,mid);
//	cout<<"ret="<<ret<<"\n";
	return ret;
}
long long seq[200005];
int main()
{
    long long n,m;
    long long pos;
    root=0;
   // freopen("in.txt","r",stdin);
        R(n), R(m);
        for(long long i=1;i<=n;++i)
        {
            R(num[i]);
        }
        build(root,1,n);
        char p;
        long long l,r,x;
    //    for(long long i=1;i<=4*n;++i)
    //    cout<<tr[i].sum<<' ';
        for(long long i=1;i<=m;++i)
        {
            p = getchar();
            while(!isupper(p)) p = getchar();
            if(p=='C')
            {
                R(l);R(r);R(x);
                add(root,l,r,1,n,x);
            }
            else if(p=='Q'){
            	
                R(l);R(r);
                cout<<query(root,l,r,1,n)<<'\n';
            }
        }

}
