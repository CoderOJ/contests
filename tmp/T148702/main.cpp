#define ENABLE_LL
#include <iostream>
#include <cstdio>
using namespace std; 
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <cstring>
#include <bitset>
#include <sstream>

#ifdef ENABLE_LL
#define int long long
#define I "%lld"
#define II "%lld%lld"
#define III "%lld%lld%lld"
#define IIII "%lld%lld%lld%lld"
#define IN "%lld\n"
#define IIN "%lld%lld\n"
#define IIIN "%lld%lld%lld\n"
#define IIIIN "%lld%lld%lld%lld\n"
#else
#define I "%d"
#define II "%d%d"
#define III "%d%d%d"
#define IIII "%d%d%d%d"
#define IN "%d\n"
#define IIN "%d%d\n"
#define IIIN "%d%d%d\n"
#define IIIIN "%d%d%d%d\n"
#endif
#define repe(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)

typedef pair < int , int > pr; 
typedef pair < pr  , int > prr; 
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); } 
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); } 
void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } } 
bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }
#define L first
#define R second

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#define ses(a) std::cout << #a << "=" << a << " " 
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#define ses(a)
#endif

#ifndef CUSTOM_MAIN

void preInit();
void init(); 
void solve(); 

int32_t main(){ 
preInit();

#ifdef MULTIPLE_TEST_CASES_WITH_T
int T; 

#ifdef _LIB_SCANNER
T = sc.nextInt();
#else
scanf("%d",&T); 
#endif /* _LIB_SCANNER */

while(T--) {init(); solve();} 
#else

#ifdef MULTIPLE_TEST_CASES_WITHOUT_T 
while(1) {
    try {init(); } 
    catch(bool t) {return 0;} 
    solve();
}
#else
init(); solve(); 
#endif /* MULTIPLE_TEST_CASES_WITHOUT_T  */

#endif /* MULTIPLE_TEST_CASES_WITH_T */
    return 0;
}

#endif /* CUSTOM_MAIN */

// my code begins here

const int N = 4005;
int n,m,k;
int w[N];
vector <int> e[N];
int dep[N], fa[N][20];





void preInit() {
    scanf(III,&n,&m,&k);
    repa (i,n) scanf(I,&w[i]);
    rep (i,n-1) { int u,v; scanf(II,&u,&v); e[u].push_back(v); e[v].push_back(u); }
}

void dfs(int u, int f) {
    fa[u][0] = f; rep (i,19) fa[u][i+1] = fa[ fa[u][i] ][i]; dep[u]=dep[f]+1;
    for (int v: e[u]) if (v!=f) {
        dfs(v,u); } }
void up(int &u , int dep) {
    repb (i,19,0) if (dep & (1<<i)) u = fa[u][i]; }
int lca(int u, int v) {
    if (dep[u]<dep[v]) swap(u,v);
    up(u,dep[u]-dep[v]);
    repb (i,19,0) { 
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i]; v=fa[v][i]; } }
    return u==v ? u : fa[u][0]; }
int dis[N][N];

void init() {
    dfs(1,0);
    repa (i,n) repa (j,n) dis[i][j] = dep[i] + dep[j] - 2*dep[lca(i,j)];
}

int calc (int u) {
    int ans = 0;
    repa (i,n) if (i!=u) {
        if ((w[i] ^ w[u]) <= k) {
            ans += dis[i][u]; } }
    return ans; }

void solve() {
    int ans = 0;
    repa (i,n) ans += calc(i); 
    ans /= 2;
    printf(IN,ans);
    rep (i,m) {
        int u,_w; scanf(II,&u,&_w);
        ans -= calc(u); w[u] = _w; ans += calc(u); 
        printf(IN,ans); }
}
