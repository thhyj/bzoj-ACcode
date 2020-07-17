
#include<iostream>  
#include<cstdio>  
#include<algorithm>  
#include<cstring>  
#include<cmath>  
#define N 103  
#define eps 1e-16  
#define inf 1000000000  
using namespace std;  
struct vector {  
    double x,y;  
    vector (double X=0,double Y=0){  
        x=X,y=Y;  
    }  
}a1[N],p[N],tmp[N];  
typedef vector point;  
vector operator -(vector a,vector b){  
    return vector (a.x-b.x,a.y-b.y);  
}  
vector operator +(vector a,vector b){  
    return vector (a.x+b.x,a.y+b.y);  
}  
vector operator *(vector a,double t)  
{  
    return vector (a.x*t,a.y*t);  
}  
vector operator !=(vector a,vector b){  
    return a.x!=b.x||a.y!=b.y;  
}  
struct data{  
    point a,b;  
}line[N];  
double a[N],b[N],c[N];  
int n,m;  
void init()  
{  
    m=0;  
    p[m++]=point(inf,inf);  
    p[m++]=point(eps,inf);  
    p[m++]=point(eps,eps);  
    p[m++]=point(inf,eps);  
}  
int dcmp(double x)  
{  
    if (fabs(x)<eps) return 0;  
    return x<0?-1:1;  
}  
double cross(vector a,vector b)  
{  
    return a.x*b.y-a.y*b.x;  
}  
point glt(point a,point a0,point b,point b0)  
{  
    double a1,b1,c1,a2,b2,c2;    
    a1 = a.y - a0.y;    
    b1 = a0.x - a.x;    
    c1 = cross(a,a0);    
    a2 = b.y - b0.y;    
    b2 = b0.x - b.x;    
    c2 = cross(b,b0);    
    double d = a1 * b2 - a2 * b1;    
    return point((b1 * c2 - b2 * c1) / d,(c1 * a2 - c2 * a1) / d);     
}  
void cut(point a,point b)  
{  
    int cnt=0;  
    memset(tmp,0,sizeof(tmp));  
    for (int i=0;i<m;i++){  
        double c=cross(b-a,p[i]-a);  
        double d=cross(b-a,p[(i+1)%m]-a);  
        if (dcmp(c)>=0)   
          tmp[cnt++]=p[i];  
        if (dcmp(c)*dcmp(d)<0)   
         tmp[cnt++]=glt(a,b,p[i],p[(i+1)%m]);  
    }  
    m=0;  
    for (int i=0;i<cnt;i++)   
     if (m==0 || (tmp[i].x!=p[m-1].x||tmp[i].y!=p[m-1].y))   
       p[m++]=tmp[i];  
}  
int main()  
{  
    scanf("%d",&n);  
    for (int i=1;i<=n;i++) scanf("%lf%lf%lf",&a[i],&b[i],&c[i]);  
    for (int i=1;i<=n;i++){  
        int k=0;  
        bool mark=true;  
        for (int j=1;j<=n;j++){  
            if (i==j) continue;  
            double nowa=1.0/a[j]-1.0/a[i];  
            double nowb=1.0/b[j]-1.0/b[i];  
            double nowc=1.0/c[j]-1.0/c[i];  
            if (dcmp(nowa)==0&&dcmp(nowb)==0) {  
                if (dcmp(nowc)>0) continue;  
                else {  
                    mark=false;  
                    break;  
                }  
            }  
            k++;  
            if (dcmp(nowb)==0) {  
                double t=-nowc/nowa;  
                line[k].a.x=t; line[k].b.x=t;  
                line[k].a.y=1; line[k].b.y=2;  
                if (dcmp(nowa)>0) swap(line[k].a,line[k].b);  
                continue;  
            }  
            line[k].a.x=1;  
            line[k].a.y=-(nowa+nowc)/nowb;  
            line[k].b.x=2;  
            line[k].b.y=-(nowa*2.0+nowc)/nowb;  
            if (dcmp(nowb)<0) swap(line[k].a,line[k].b);  
        }  
        if (!mark){  
            printf("No\n");  
            continue;  
        }  
        init();  
        for (int  j=1;j<=k;j++)  
         cut(line[j].a,line[j].b);  
        double area=0; p[m]=p[0];  
        for (int j=1;j<m;j++) area+=cross(p[j]-p[0],p[j+1]-p[0]);  
        area=fabs(area);  
        if (m>2&&dcmp(area)>0) printf("Yes\n");  
        else printf("No\n");  
    }  
} 
