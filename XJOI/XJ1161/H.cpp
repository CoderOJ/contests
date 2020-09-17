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

const int N = 10005;
int v , n , m , r;
vector < int > e[N];
int mch[N] , vis[N];

void init(){
    scanf("%d%d%d%d",&v,&n,&m,&r);
    rep (i,r) {
        int u , v;
        scanf("%d%d",&u,&v);
        v += n;
        e[u].push_back(v);
        e[v].push_back(u);
    }
}

bool dfs(int u) {
    foreach (i,e[u]) {
        int v = e[u][i];
        if (vis[v]) continue;
        vis[v] = 1;
        if (mch[v] == -1 || dfs(mch[v])) {
            mch[v] = u;
            mch[u] = v;
            return 1;
        }
    }
    return 0;
}

int Hungarian() {
    int res = 0;
    memset(mch , -1 , sizeof(mch));
    repa (i,n + m) {
        if (mch[i] == -1) {
            memset (vis , 0 , sizeof(vis));
            res += dfs(i);
        }
    }
    return res;
}

int main(){
    init();
    printf("%d\n",min (v + 1,n + m - Hungarian()));
    return 0;
}
