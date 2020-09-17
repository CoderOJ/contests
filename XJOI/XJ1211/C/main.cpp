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
#define ses(a) std::cout << #a << "=" << a << " "
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#define ses(a)
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
const int M = 100005;
const int INF = 0;
 
struct Dsu {
    int p[N];
 
    void init() {
        rep (i,N) p[i] = i;
    }  
 
    int get(int u) {
        if (p[u] == u) return u;
        else return p[u] = get( p[u] );
    }
 
    void merge(int u , int v) {
        p[ get(u) ] = get(v);
    }
 
    bool query(int u , int v) {
       return get(u) == get(v);
    }
};
 
int peu[M] , pev[M] , pew[M] , pid[M];
vector < int > ei[N];
int ev[M] , ew[M];
int n , m , mass;
int cnt;
 
void addEdge(int u , int v , int w) {
    ev[cnt] = v ; ew[cnt] = w;
    ei[u].push_back(cnt++);
    ev[cnt] = u ; ew[cnt] = w;
    ei[v].push_back(cnt++);
}
 
const int B = 28;
int fa[N][B] , we[N][B];
int dep[N];
 
void dfs(int u , int f, int _w) {
    dep[u] = dep[f] + 1;
    fa[u][0] = f;
    we[u][0] = _w;
    foreach (_i,ei[u]) {
        int i = ei[u][_i];
        int v = ev[i] ;
        if (v == f) continue;
        dfs (v,u, ew[i]);
    }
}
 
Dsu st;
 
void init(){
    memset(we,0x3f,sizeof(we));
    scanf("%d%d",&n,&m);
    rep (i,m) scanf("%d%d%d",&peu[i],&pev[i],&pew[i]);
    rep (i,m) pid[i] = i;
    sort (pid , pid + m , [](int a , int b) {return pew[a] < pew[b];} );
    st.init();
    rep (_i,m) {
        int i = pid[_i];
        if (!st.query( peu[i] , pev[i])) {
            st.merge( peu[i] , pev[i] );
            addEdge( peu[i] , pev[i] , pew[i] );
        }
    }
    dfs(1,0,INF);
    repa (i,n) ses(we[i][0]);
    see("");
    rep (b,B - 1) repa (u,n) if (fa[u][b]) fa[u][b + 1] = fa[ fa[u][b] ][b];
    rep (b,B - 1) repa (u,n) if (fa[u][b]) we[u][b + 1] = max(we[u][b] , we[ fa[u][b] ][b]);
}
 
int upMove ( int u , int d , int& ans) {
    int b = B - 1 , sp = 1 << b;
    while (d) {
        if (sp <= d) {
            ans = max(ans , we[u][b]);
            ses(u);ses(b);see(we[u][b]);
            u = fa[u][b];
            d -= sp;
        }
        b--; sp >>= 1;
    }
    return u;
}
 
void solve() {
    int q;
    scanf("%d",&q);
    while (q--) {
        int u , v;
        scanf("%d%d",&u,&v);
        if (dep[u] < dep[v]) swap(u,v);
        int ans = INF;
        u = upMove (u,dep[u] - dep[v] , ans);
        ses(u);see(v);
        for (int b = B-1 ; b >= 0 ; b--) {
           if (fa[u][b] != fa[v][b]) {
                ans = max(ans , max(we[u][b] , we[v][b]));
                u = fa[u][b] ; v = fa[v][b];
           }
        }
        if (u != v) ans = max(ans , max(we[u][0] , we[v][0]) );
        printf("%d\n",ans);
    }
}
 
int main(){
    init();
    dfs(1,0,INF);
    solve();
    return 0;
}
