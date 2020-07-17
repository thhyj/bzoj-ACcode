
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int first[301],next[16001],to[16001],fr[16001],length[16001],tot,cnt,res[301];
bool pd[501];
struct dui {
    int num;
    int w;
} heap[16001];
inline void R(int &v) {
    v=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c>='0'&&c<='9') {
        v=(v<<3)+(v<<1)+(c^'0');
        c=getchar();
    }
}
inline void create(int &x,int &y,int &z) {
    ++tot;
    next[tot]=first[x];
    first[x]=tot;
    to[tot]=y;
    fr[tot]=x;
    length[tot]=z;
}
inline void up(int fi) {
    int fa=fi>>1;
    dui t=heap[fi];
    while(fa&&t.w<heap[fa].w) {
        heap[fi]=heap[fa];

        fi=fa;
        fa=fa>>1;
    }
    heap[fi]=t;
}
inline void down (int fa) {
    int fi=fa<<1;
    dui t=heap[fa];
    while(fi<=cnt) {
        if(fi^cnt&&heap[fi].w>heap[fi+1].w)++fi;
        if(t.w<heap[fi].w)
            break;
        heap[fa]=heap[fi];
        fa=fi;
        fi=fi<<1;
    }
    heap[fa]=t;
}
int main() {
    int n,m;
    R(n);
    R(m);
    int ans=0;
    int x,y,z;
    for(register int i=1; i<=m; ++i){
            R(x);
            R(y);
            R(z);
            create(x,y,z);
            create(y,x,z);
        }
    int p;
    for(register int i=1; i<=16000; ++i)
        heap[i].w=156165165;
    for(p=first[1]; p; p=next[p]) {
        ++cnt;
        heap[cnt].w=length[p];
        heap[cnt].num=p;
        up(cnt);
    }
    pd[1]=1;
    pd[0]=1;
    int j;
    for(register int i=1; i<n;) {
        j=to[heap[1].num];
        if(pd[j]&&pd[fr[heap[1].num]]) {
            heap[1]=heap[cnt];
            --cnt;
            down(1);
            continue;
        }
        ++i;
        res[i]=heap[1].w;
        ++ans;
        heap[1]=heap[cnt];
        --cnt;
        down(1);
        for(p=first[j]; p; p=next[p]) {
            if(pd[fr[p]]&&pd[to[p]])continue;
            ++cnt;
            heap[cnt].w=length[p];
            heap[cnt].num=p;
            up(cnt);
        }
        pd[j]=1;
    }
    int max1=0;
    for(register int i=1;i<=n;++i)
        max1=max(max1,res[i]);
    cout<<ans<<" "<<max1;
    return 0;
}
