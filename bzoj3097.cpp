
#include <iostream>  
#include <cstring>  
#include <algorithm>  
#include <cstdio>  
#include <cstdlib>  
#include <string>  
using namespace std;  
char s[10000];  
int main()  
{  
    cout<<(1<<11)+65<<" "<<(1<<10)<<endl;  
    int now=1;  
    s[1]='a';  
    for (int i=1;i<=11;i++)  
    {  
        for (int j=1;j<=now;j++)  
            s[now+j]=s[j]=='a'?'b':'a';  
        now<<=1;  
    }  
    for (int i=1;i<=now;i++)  
        printf("%c",s[i]);  
    for (int i=1;i<=65;i++)  
        printf("a");  
    printf("\n");  
    return 0;  
}  
