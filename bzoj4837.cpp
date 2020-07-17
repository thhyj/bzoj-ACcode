
#include<iostream>  
#include<string>  
#include<algorithm>  
#include<cstdio>  
#include<cstring>  
#include<cstdlib>  
#include<cmath>
#include<vector>
using namespace std; 
typedef unsigned long long ull;
 
const int ONE = 1e5+5;
const int INF = 2147483640;
 
int T;
int n,m;
int x,A,B,p;
int PD[10000001],pos[10000001];
int q[10000001];
int Ans;
 
inline int get()
{
        int res=1,Q=1;  char c;
        while( (c=getchar())<48 || c>57)
        if(c=='-')Q=-1;
        if(Q) res=c-48; 
        while((c=getchar())>=48 && c<=57) 
        res=res*10+c-48;
        return res*Q; 
}
 
void Solve()
{
        n=get();    m=get();
        x=get();    A=get();    B=get();    p=get(); 
        ull Ans = 0, val = 0;
        int tou=1, wei=0, num=0;
         
        for(int i=1;i<=max(n,m);i++) PD[i] = 0;
        for(int i=0;i<=p;i++) pos[i] = 0;
        for(int i=1;i<=m;i++)
        {
            if(!pos[x])
            {
                if(num == n)
                {
                    while(!PD[tou]) tou++;
                    pos[q[tou]] = 0;    PD[tou] = 0;
                    val -= q[tou];  num--;
                }
                q[++wei] = x; 
                pos[x] = wei; PD[wei] = 1;
                val+=x; num++;
            }
             
            else
            {
                q[++wei] = x;
                PD[pos[x]] = 0; pos[x] = wei; PD[pos[x]] = 1;
            }
             
            x = ((long long)A*x%p + B) % p;
            Ans += i*val; 
        }
         
        cout<<Ans<<endl;
}
 
int main()
{
        T=get();
        while(T--)
            Solve();
}
