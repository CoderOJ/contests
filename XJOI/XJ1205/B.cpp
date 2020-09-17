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
const int INF = 0x3f3f3f3f;
int e[N][N];
int match[N]; // match form right to left
int dl[N] , dr[N];
int vl[N] , vr[N];
int slack[N];
int n,m,k;

void init(){
    scanf("%d%d%d",&n,&m,&k) ;
    memset(e,0,sizeof(e));
    rep (i,k) {
        int u,v,w; scanf("%d%d%d",&u,&v,&w);
        e[u][v] = w;
    }
    for (int i=n + 1;i<=m;i++) {
        memset(e[i],0,sizeof(e[i]));
    }
}

bool dfs(int u) {
    see(u);
    vl[u] = 1;
    repa (i,m) {
        if (e[u][i] == -1) continue;
        if (vr[i]) continue;
        int mo = dl[u] + dr[i] - e[u][i];
        if (mo == 0) {
            vr[i] = 1;
            if (match[i] == -1 || dfs(match[i])) {
                match[i] = u;
                return 1;   
            }
        }
        slack[i] = min(slack[i] , mo);
    }
    return 0;
}

int KM() {
    memset(match , -1 , sizeof(match));
    repa (i,m) {
        dl[i] = 0;
        repa (j,m) if (e[i][j] != -1) dl[i] = max(dl[i] , e[i][j]);
    }
    repa (u,m) {
        memset(slack,INF,sizeof(slack));
        while (1) {
            memset(vl,0,sizeof(vl));
            memset(vr,0,sizeof(vr));
            if (dfs(u)) break;
            int de = INF;
            repa (i,m) if (!vr[i]) de = min(de , slack[i]);
            repa (i,m) if (vl[i]) dl[i] -= de;
            repa (i,m) if (vr[i]) dr[i] += de;
                       else       slack[i] -= de;
        }
    }
    int res = 0;
    repa (i,m) res += dl[i] + dr[i];
   return res;
}

int main(){
    init();
    printf("%d\n",KM());
    return 0;
}
