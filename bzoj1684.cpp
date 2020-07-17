
#include<cstdio>
#include<cmath>
int a,b,i,aa,bb;
double save=10;
inline double abs(double x)
{if (x<0)x=-x;return x;}
void jud(int x,int y)
{
	if (x*b==y*a) return;
	double work=abs((double)x/y-(double)a/b);
	if (work<save)
	{
		save=work;
		aa=x;
		bb=y;
	}
}
int main()
{
	scanf("%d%d",&a,&b);
	for (int j=1;j<=32767;j++)
	  {
	  	i=(int)floor((double)a/b*j);
	  	jud(i,j);
	  	jud(i+1,j);
	  }
	printf("%d %d\n",aa,bb);
}
