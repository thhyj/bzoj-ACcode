
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include <algorithm>
using namespace std;
inline char read() {
	static const int IN_LEN = 2000100;
	static char buf[IN_LEN], *s, *t;
	if (s == t) {
		t = (s = buf) + fread(buf, 1, IN_LEN, stdin);
		if (s == t) return -1;
	}
	return *s++;
}
template<class T>
inline bool R(T &x) {
	static bool iosig;
	static char c;
	for (c = read(), iosig = true; !isdigit(c); c = read()) {
		if (c == '-') iosig = true;
		if (c == -1) return false;
	}
	for (x = 0; isdigit(c); c = read())
		x = (x + (x << 2) << 1) + (c ^ 48);
}
int x,y,d,jj,m,n,xi,i,j;
bool f,ff;
int w[50001];

int main()
{
    //freopen("in.in","r",stdin);
    //freopen("hotel.out","w",stdout);
    R(n),R(m);
    for(i=1;i<=m;i++)    //枚举数据输入的每种情况 
    {
      R(x);
      if(x==1)    //如果是住房
      {
          R(y);
          f=false;
          j=1;  jj=j+y-1;  //准备订房号j~jj
          while(j<=n && jj<=n) 
          {  
              ff=false;
              for(d=jj;d>=j;d--)
                  if(w[d]==1)    //不能成功订需要的数量，则退出
                  {
                       j=d+1;
                       jj=j+y-1;
                       ff=true;
                       break;
                  } 

               if(ff) continue;            //不能订需要的房间，则继续扫描
               for(d=jj;d>=j;d--) w[d]=1;  //如果能订到需要的房间数量，则对这些房间做入住标记
               f=true;
               break;                      //退出while循环
          }
          if(f) printf("%d\n",j);    //输出
          else  printf("0\n"); ;    
      }

      if(x==2)   //如果是退房
      {
          R(xi),R(y);
          y=xi+y-1;
          for(d=xi;d<=y;d++) w[d]=0;  //做退房标记
      }
    }
    return 0;
}
