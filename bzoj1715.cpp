
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<string>
#include<cstring>
#include<ctime>
using namespace std;
int first[100001],f[100001];             
int next[2000001],v[2000001],c[2000001],ti[2000001];  
int p[2000000];          
int n,k,t,size;
bool exist[100001],pd;      
void inser(int x,int y,int w) 
{
  size++;               
  next[size]=first[x];    
  first[x]=size;          
  v[size]=y;             
  c[size]=w;              
}
void init()      
{
  int i,x,y,w;
  memset(v,0,sizeof(v));
  memset(c,0,sizeof(c));
  memset(next,0,sizeof(next));
  memset(ti,0,sizeof(ti));
  memset(first,0,sizeof(first));
  scanf("%d%d%d",&n,&k,&t);
  size=0;
  for (i=1;i<=k;i++)
    {
      scanf("%d%d%d",&x,&y,&w);   
      inser(x,y,w);               
      inser(y,x,w);           
    }
  for(i=1;i<=t;i++)
  {
  	scanf("%d%d%d",&x,&y,&w);   
    inser(x,y,-w);       
  }
}
int main()      
{int q;
  cin>>q;
  for(int l=1;l<=q;l++)
  {pd=0;
  init();           
  int i,j,head,tail,u;
  memset(exist,false,sizeof(exist));
  fill(f+1,f+n+1,1000000000);  
  f[1]=0;                          
  p[1]=1;                         
  exist[1]=true;                  
  head=0;                           
  tail=1;                         
  while (head<tail)
  {
     head++;                             
     exist[p[head]]=false;               
     u=first[p[head]];                   
     while (u!=0)                        
       { 
         if (f[p[head]]+c[u]<f[v[u]])   
           {
             f[v[u]]=f[p[head]]+c[u];   
             if (exist[v[u]]==false)     
             {  ti[v[u]]++;
           if(ti[v[u]]>n-1)
           {cout<<"YES"<<endl;
		   pd=1;
		   break;}   
               tail++;                   
               p[tail]=v[u];           
               exist[v[u]]=true;         
             }
           }
         u=next[u]; 
      }
      if(pd==1)
      break;
   }
   if(pd==0)
   cout<<"NO"<<endl;
}
  return 0;
}
