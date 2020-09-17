#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

#define long long long
#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 

const int N = 105;
int pt[N];
int dis[N];
int rp[N];
int e[N][N];
int n,m;

void init() {
    fill(dis,dis + N , -0x3f3f3f3f);
    memset(rp,-1,sizeof(rp));
    memset(e,0,sizeof(e));
    memset(pt,0,sizeof(pt));
    scanf("%d",&n);
    repa (i,n) scanf("%d",&pt[i]);
    scanf("%d",&m);
    rep (i,m) {
        int u,v;
        scanf("%d%d",&u,&v);
        e[u][v] = 1;
    }   
}

void solve(){
    dis[1] = 0;
    repi (i,2,n + 1) repa(j,i- 1) if (e[j][i]) {
        if (dis[j] + pt[i] > dis[i]) {
            dis[i] = dis[j] + pt[i];
            rp[i] = j;
        }
    }
}

void print(int p) {
    if (rp[p] == -1) printf("1");
    else {
        print(rp[p]);
        printf("->%d",(p == n + 1 ? 1 : p));
    }
}

int main(){
    int T;
    scanf("%d",&T);
    repa (kase,T) {
        init();
        solve();
        if (kase != 1) puts("");
        printf("CASE %d#\n",kase);
        printf("points : %d\n",dis[n + 1]);
        printf("circuit : ");
        print(n + 1);
        puts("");
    }
    return 0;
}
