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

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
typedef pair < int , int > pr;
typedef pair < pr  , int > prr;
#define L first
#define R second

const int N = 505;
vector < pr > e[N];
int n,d;
int dep[N] , prt[N];

void init(){
    scanf("%d%d",&n,&d);
    rep (i,n - 1) {
        int u,v,w; scanf("%d%d%d",&u,&v,&w);
        e[u].push_back( pr(v,w) );
        e[v].push_back( pr(u,w) );
    }
}

void dfs(int u , int f) {
    vector < int > vt;
    vt.push_back(0);
    foreach (i,e[u]) {
        int v = e[u][i].L;
        if (v == f) continue;
        dfs(v,u);
        prt[u] += prt[v];
        vt.push_back( dep[v] + e[u][i].R );
    }
    sort(vt.begin() , vt.end());
    for (int i=vt.size() - 1;i>0;i--) {
        if (vt[i] + vt[i - 1] > d) {
            prt[u]++;
        }else {
            dep[u] = vt[i];
            break;
        }
    }
}

int main(){
    init();
    dfs(1,0);
    printf("%d\n",prt[1] + 1);
    return 0;
}
