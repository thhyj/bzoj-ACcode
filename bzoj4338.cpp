
#include<bits/stdc++.h>
using namespace std;
long long n,m,k,p,len,a[20];
inline long long power(long long a,long long b,long long mod){
    long long res=1;
    for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)res=1ll*res*a%mod;
    return res;
}
inline bool isprime(long long p){
    for(long long d=2;1ll*d*d<=p;d++){
        if(!(p%d)){;return false;}
    }
    return true;
}
const long long Maxn=1e6;
const long long INF=0x7fffffff;
long long isnotprime[Maxn+50],prime[Maxn+50],primecnt;
inline void seive(){
    for(long long i=2;i<=Maxn;i++){
        if(!isnotprime[i]){
            prime[++primecnt]=i;
        }
        for(long long j=1;j<=primecnt;j++){
            long long k=i*prime[j];
            if(k>Maxn)break;
            isnotprime[k]=1;
            if(!(i%prime[j]))break;
        }
    }
}
vector<pair<long long,long long> >factory;
typedef pair<long long,long long> pii;
inline long long getfac(long long k){
    for(long long i=1;prime[i]*prime[i]<=k;i++){
        if(!(k%prime[i])){
            factory.push_back(make_pair(prime[i],0));
            while(!(k%prime[i]))k/=prime[i],factory[factory.size()-1].second++;
        }
    }
    if(k!=1)factory.push_back(make_pair(k,1));
}
inline pii getans(long long val,long long p){
    if(val<p){
        long long res=1;
        for(long long i=1;i<=val;i++)res=1ll*i*res%p;
        return make_pair(res,0);
    }
    pii tmp=getans(p-1,p);
    pii tmp2=getans(val/p,p);
    long long res=1;
    for(long long i=val/p*p+1;i<=val;i++){
        res=1ll*res*i%p;
    }
    return make_pair(1ll*res*power(tmp.first,val/p,p)%p*tmp2.first%p,val/p+tmp2.second);
}
inline long long exgcd(long long &a,long long &b,long long x,long long y){
    if(!y){
        a=1,b=0;
        return x;
    }
    long long t=exgcd(a,b,y,x%y);
    long long a2=a;
    a=b;
    b=(a2-b*(x/y));
    return t;
}
inline void merge(long long &A,long long &B,long long C,long long D){
    long long a,b;
    long long t=exgcd(a,b,A,C);
    a%=C;
    long long lcm=1ll*A*C/t;
    a=(1ll*a*(D-B)%C+C)%C;
    B=1ll*A*a+B;
    B%=lcm;
    A=lcm;
}
inline long long calc(long long m,long long k){
    getfac(p);
    long long A=1,B=0;
    for(long long e=0;e<factory.size();e++){
        pii t=getans(m+k-1,factory[e].first);
        pii t1=getans(m,factory[e].first);
        pii t2=getans(k-1,factory[e].first);
        long long tmp=t.second-t1.second-t2.second;
        long long pp=power(factory[e].first,factory[e].second,INF);
        long long val=1ll*t.first*power(t1.first,pp-pp/factory[e].first-1,pp)%pp*power(t2.first,pp-pp/factory[e].first-1,pp)%pp;
        val=1ll*val*power(factory[e].first,tmp,pp)%pp;
        merge(A,B,pp,val);
    }
    return B;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    cin>>n>>m>>k>>p;
     if(isprime(p)){
        k%=p;
        long long all=1,fac=1;
        for(long long i=1;i<=m;i++){
            fac=1ll*fac*i%p;
            all=1ll*all*k%p;
            (++k)%=p;
        }
        all=1ll*all*power(fac,p-2,p)%p;
        long long ans=1;
        for(long long i=1;i<=n;i++){
            ans=1ll*all*ans%p;
            all=(all+p-1)%p;
        }
        cout<<ans<<endl;
    }
    else{ 
        seive();
        long long all=calc(m,k),ans=1;
        for(long long i=1;i<=n;i++){
            ans=1ll*all*ans%p;
            all=(all+p-1)%p;
        }
        cout<<ans<<endl;
    }
}
