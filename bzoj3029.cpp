
#include<iostream>  
#include<string>  
#include<algorithm>  
#include<cstdio>  
#include<cstring>  
#include<cstdlib>  
#include<cmath>
using namespace std; 
    
const int ONE = 205;
    
int n,Limit,K;
int a[ONE];
float p[ONE],Ans;
float f[ONE][ONE][ONE*2]; //i times j win k bag
   
int get() 
{
        int res=1,Q=1;  char c;
        while( (c=getchar())<48 || c>57)
        if(c=='-')Q=-1;
        if(Q) res=c-48; 
        while((c=getchar())>=48 && c<=57) 
        res=res*10+c-48; 
        return res*Q; 
}
   
int id(int x) {return min(x,n) + 200;}
   
int main()
{
        n=get();    Limit=get();    K=get();
        for(int i=1;i<=n;i++)    scanf("%f",&p[i]), p[i]/=100.0;
        for(int i=1;i<=n;i++)    a[i]=get();
       
        f[0][0][id(K)] = 1;
        for(int i=0; i<=n-1; i++)
        for(int j=0; j<=i; j++)
        for(int k=-i; k<=n; k++)
        {
            f[i+1][j][id(k)] += f[i][j][id(k)] * (1.0-p[i+1]); // fail
            f[i+1][j+1][id(k+a[i+1])] += f[i][j][id(k)] * p[i+1]; // win
        }
           
        for(int j=Limit; j<=n; j++)
        for(int k=id(0); k<=id(n); k++)
            Ans += f[n][j][k];
           
        printf("%.6f", Ans);
}
