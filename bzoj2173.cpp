
#include<iostream>
long long g[1000010],n;int main(){std::cin>>n;g[1]=1;for(int i=2;i<=n;i++)g[i]=(2*g[i-1]+g[i-2])%(int)(1e9+7);std::cout<<g[n];}
