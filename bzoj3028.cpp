
#include<bits/stdc++.h>
#define LL long long
using namespace std;
 
const int MOD = 10007;
const int REV = 1668;
 
int main() {
    int n=0; char pat[600]; cin>>pat+1;
    for (int i=1;i<=strlen(pat+1);i++)
        n = (n * 10 + pat[i] - '0') % MOD;
    cout<<n*(n+1ll)*(n+2)*REV%MOD;
    return 0;
}
