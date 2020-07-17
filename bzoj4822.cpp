
#include<cstdio>
#include<algorithm>
using namespace std;
#define LL long long
int rd()
{
    LL x=0;
    int f=1;
    char c=getchar();
    while (c<'0'||c>'9')
    {
        if (c=='-') f=-1;
        c=getchar();
    }
    while (c>='0'&&c<='9')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
struct str
{
    LL x,y,k,id,v;
    bool operator < (const str &s) const
    {
        if (x!=s.x) return x<s.x;
        return !k&&s.k;
    }
}a[2000010];
LL ans[100010],s[2000010],ord[2000010],
xx[100010],yy[100010],vv[100010],x1[100010],y1[100010],x2[100010],y2[100010];
int n,q,m,tot;
int main()
{
    int u1,u2;
    LL sum;
    n=rd();
    q=rd();
    for (int i=1;i<=n;i++)
    {
        xx[i]=rd();
        yy[i]=rd();
        vv[i]=rd();
        ord[++m]=yy[i];
    }
    for (int i=1;i<=q;i++)
    {
        x1[i]=rd();
        y1[i]=rd();
        x2[i]=rd();
        y2[i]=rd();
        ord[++m]=y1[i]-1;
        ord[++m]=y2[i];
    }
    sort(ord+1,ord+m+1);
    m=unique(ord+1,ord+m+1)-ord-1;
    for (int i=1;i<=n;i++)
    {
        u1=lower_bound(ord+1,ord+m+1,yy[i])-ord;
        a[++tot]=(str){xx[i],u1,0,0,vv[i]};
    }
    for (int i=1;i<=q;i++)
    {
        u1=lower_bound(ord+1,ord+m+1,y1[i]-1)-ord;
        u2=lower_bound(ord+1,ord+m+1,y2[i])-ord;
        a[++tot]=(str){x1[i]-1,u1,1,i,0};
        a[++tot]=(str){x1[i]-1,u2,-1,i,0};
        a[++tot]=(str){x2[i],u1,-1,i,0};
        a[++tot]=(str){x2[i],u2,1,i,0};
    }
    sort(a+1,a+tot+1);
    for (int i=1;i<=tot;i++)
        if (a[i].k)
        {
            sum=0;
            for (int j=a[i].y;j;j-=j&-j) sum+=s[j];
            ans[a[i].id]+=sum*a[i].k;
        }
        else
            for (int j=a[i].y;j<=m;j+=j&-j) s[j]+=a[i].v;
    for (int i=1;i<=q;i++) printf("%lld\n",ans[i]);
}
