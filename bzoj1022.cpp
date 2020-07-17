
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int main()
{
	//freopen("in.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin>>T;
	int x;
	int n;
	int ans=0;
	int cnt=0;
	for(int i=1;i<=T;++i)
	{
		cnt=0;
		ans=0;
		cin>>n;
		for(int j=1;j<=n;++j)
		{
			cin>>x;
			ans^=x;
			if(x>1)
				cnt=1;
		}
		//cout<<"ans="<<ans<<"\n";
		if(cnt==0)
		{
			if(ans)
			cout<<"Brother\n";
			else
			cout<<"John\n";
			continue;
		}
		else
		if(ans)
			cout<<"John\n";
		else
			cout<<"Brother\n";
	}
	return 0;
}
