#include<bits/stdc++.h>
using namespace std;
int main() {
	char duru[100005];
	freopen("in.in","r",stdin);
	char lujing[200];
	while(fgets(duru, 100000, stdin)){
		if(duru[0] == 'P' && duru[1] == 'r' && duru[2] == 'o' && duru[3] == 'b' && duru[4] == 'l' && duru[5] == 'e' && duru[6] == 'm') {
			fclose(stdout);
			sprintf(lujing, "bzoj%c%c%c%c.cpp", duru[7], duru[8], duru[9], duru[10]);
			freopen(lujing, "w",  stdout);
			continue;
		}
		printf("%s", duru);
	}
} 
