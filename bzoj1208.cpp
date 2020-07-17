
#include <bits/stdc++.h>
using namespace std;
const unsigned int inf=4000000000;
const unsigned int mod = 1000000;
inline void R(unsigned int &v)
{
	static char ch;
	v=0;
	bool p=0;
	do
	{
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
struct tree
{
	unsigned int val,cnt,sz;
	unsigned int s[2],f;
}a[300005];
unsigned int root;
inline void point(unsigned int x,unsigned int y,bool z)
{
//	cout<<"x="<<x<<" y="<<y<<"\n";
	a[x].s[z]=y;
	a[y].f=x;
}
inline void update(unsigned int x)
{
	a[x].sz=a[a[x].s[0]].sz+a[a[x].s[1]].sz+a[x].cnt;
}
inline bool son(unsigned int x)
{
	return a[a[x].f].s[1]==x;
}
inline void rotate(unsigned int x)
{
//	cout<<"x="<<x<<" a[x].f="<<a[x].f<<"\n";
	bool d=son(x);
	unsigned int p=a[x].f;
	point(a[p].f,x,son(a[x].f));
	point(p,a[x].s[d^1],d);
	point(x,p,d^1);
	update(x),update(p);
	if(!a[x].f)
	{
		root=x;
	}
}
inline void splay(unsigned int x,unsigned int &k)
{
	while(x^k)
	{
	//	getchar();
		if(a[x].f==k)
		{
		rotate(x);
		return;}
		if(son(x)==son(a[x].f))
		{
			rotate(a[x].f);
		}
		else
		rotate(x);
		rotate(x);
	}
}
unsigned int pos,tot;
inline void ins(unsigned int &k,unsigned int x,unsigned int last )
{
	if(!k)
	{
		++tot;
		k=tot;
		a[k].val=x;
		a[k].f=last;
		splay(k,root);
		return ;
	}
	if(x<a[k].val)ins(a[k].s[0],x,k);
	else ins(a[k].s[1],x,k);
}
unsigned int qq,hj;
inline void ask_before(unsigned int k,unsigned int x)
{
	
	while(k)
	{
		if(a[k].val<=x)qq=k,k=a[k].s[1];
		else k=a[k].s[0];
	}
}
inline void ask_after(unsigned int k,unsigned int x)
{
	while(k)
	{
		if(a[k].val>=x)hj=k,k=a[k].s[0];
		else k=a[k].s[1];
	}
}
inline void askbefore(unsigned int k)
{
	splay(k,root);
	if(!a[k].s[0])return;
	k=a[k].s[0];
	while(a[k].s[1])k=a[k].s[1];
	qq=k;
}
inline void askafter(unsigned int k)
{
	splay(k,root);
	if(!a[k].s[1])return;
	k=a[k].s[1];
	while(a[k].s[0])k=a[k].s[0];
	hj=k;
}
unsigned int rs;
void del(long long x)
{
	splay(x,root);
	if(a[x].s[1]*a[x].s[0]==0)
	{root=a[x].s[1]+a[x].s[0];}
	else 
	{
		int k=a[x].s[1];
		while(a[k].s[0]){
		//cout<<"a[k].s[0]="<<a[k].s[0]<<'\n';
		k=a[k].s[0];}
		a[k].s[0]=a[x].s[0];a[a[x].s[0]].f=k;
		root=a[x].s[1];
	}
	a[root].f=0;
}
void zhongxu(int x)
{
	if(a[x].s[0])
		zhongxu(a[x].s[0]);
	cout<<"ÖÐÐò±éÀú "<<x<<' '<<a[x].val<<'\n';
	if(a[x].s[1])
		zhongxu(a[x].s[1]);
}
int main()
{
//	freopen("out.out","w",stdout);
	unsigned int n;
	R(n);
    unsigned int ans=0;
    unsigned int ki,x;
    bool kind;
    for(unsigned int i=1;i<=n;++i)
    {
    	//cout<<"root="<<root<<'\n';
   //	zhongxu(root);
    	//getchar();
    //	cout<<'\n';
        R(ki),R(x);
        if(!root)
        {
        	ins(root,x,0);
        	kind=ki;
		}
		else if(kind==ki)ins(root,x,0);
		else
		{
			qq=hj=-1;
			ask_before(root,x),ask_after(root,x);
		//	cout<<"qq="<<qq<<" hj="<<hj<<" a[qq].val="<<a[qq].val<<" a[hj].val="<<a[hj].val<<'\n';
			if(qq==-1)
			{
			//	cout<<"delete qq\n";
				ans=(ans+a[hj].val-x)%mod;del(hj);continue;
			}
			if(hj==-1)
			{
			//	cout<<"delete hj\n";
				ans=(ans+x-a[qq].val)%mod;del(qq);continue;
			}
			if(x-a[qq].val>a[hj].val-x)  {//cout<<"delete hj\n";
			ans+=a[hj].val-x;ans%=mod;del(hj);}
			else{//cout<<"delete qq\n";
			ans+=x-a[qq].val;ans%=mod;del(qq);}
		}
    }
    cout<<ans;
    return 0;
 }
