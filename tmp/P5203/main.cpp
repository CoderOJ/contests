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
#include <bitset>
#include <sstream>
using namespace std; 
#ifndef CUSTOM_MAIN
void init(); void solve(); int main(){ try { 
#ifdef MULTIPLE_TEST_CASES_WITH_T
int T; scanf("%d",&T); while(T--) {init(); solve();} 
#else
#ifdef MULTIPLE_TEST_CASES_WITHOUT_T 
while(1) {try{init(); } catch(bool t){return 0;} solve(); } 
#else
init(); solve(); 
#endif
#endif
} catch (...) { return 0; } return 0; }
#endif
#ifdef ENABLE_LL
#define int long long
#endif
#ifdef ENABLE_LL
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
#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#define ses(a) std::cout << #a << "=" << a << " " 
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#define ses(a)
#endif
#define repe(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)
#define L first
#define R second
typedef pair < int , int > pr; typedef pair < pr  , int > prr; template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); } template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); } class Scanner{ private: istream& ist;public: Scanner(istream& in):ist(in){} string next(){ string r; ist >> r; return r; } string nextLine(){ string r; getline(ist,r); return r; } int nextInt(){ int r; ist >> r; return r; } double nextDouble(){ double r; ist >> r; return r; } char nextChar(){ char r; ist>>r; return r;} }; Scanner sc(cin); void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } } bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }

const int N = 200005;
const int B = 20;
vector <int> e[N];
int u[N],v[N], n,m;

void init() {
    scanf(II,&n,&m);
    rep (i,n-1) { int u,v; scanf(II,&u,&v); e[u].push_back(v); e[v].push_back(u); }
}

int dep[N], fa[N][B], c[N];
void dfs(int u, int f) {
    dep[u] = dep[f]+1; fa[u][0] = f;
    rep (i,B-1) fa[u][i+1] = fa[ fa[u][i] ][i];
    for (int v: e[u]) if (v!=f) { dfs(v,u); } }
int up(int u, int k) {
    repb (i,B-1,0) if (k &(1<<i)) u=fa[u][i];
    return u; }
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u,v);
    u = up(u, dep[u]-dep[v]);
    repb (i,B-1,0) if (fa[u][i] != fa[v][i]) { u=fa[u][i]; v=fa[v][i]; }
    return u==v ? u : fa[u][0]; }

vector <int> cr[N];
struct Diff { 
    int l,u,v;
    bool operator < (const Diff& b) const {
        if (l == b.l) return u==b.u ? v<b.v : u<b.u;
        return l<b.l; } };
map < Diff, int > muls;
long long ans=0;

long long cs[N];
void dfs2(int u,int f) {
    for (int v: e[u]) if (v!=f) {
        cs[v] += cs[u];
        dfs2(v,u); } }

void solve() {
    dfs(1,0);
    rep (i,m-n+1) {
        int u,v; scanf(II,&u,&v); if (u==v) continue;
        if (dep[u] < dep[v]) swap(u,v);
        int l = lca(u,v);
        cr[l].push_back(u);
        cs[ up(u,dep[u]-dep[l]-1) ]++;
        if (l != v) {
            cr[l].push_back(v);
            cs[ up(v,dep[v]-dep[l]-1) ]++;
            int su = up(u,dep[u]-dep[l]-1), sv = up(v,dep[v]-dep[l]-1); if (su>sv) swap(su,sv);
            Diff d = {l,su,sv};
            ans -= muls[d]; muls[d]++; } }
    repa (i,n) { int s=cs[i]; ans -= 1LL*s*(s-1)/2; } 
    dfs2(1,0);
    repa (u,n) for (int v: cr[u]) { ans += cs[v] - cs[u] - 1; }
    printf("%lld\n",ans);
}

