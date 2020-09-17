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

const int N = 100005;
vector <int> e[N];
int us[N], vs[N];
int n,m;

void init() {
    scanf(II,&n,&m);
    rep (i,n-1) { int u,v; scanf(II,&u,&v); e[u].push_back(v); e[v].push_back(u); }
}

const int B = 20;
int dep[N]; int fa[N][B];
void dfs(int u, int f) {
    dep[u] = dep[f] + 1;
    fa[u][0] = f; rep (i,B-1) fa[u][i+1] = fa[ fa[u][i] ][i];
    for (int v: e[u]) if (v!=f) dfs(v,u); }

inline int up(int u, int d) {
    repb (i,B-1,0) { if (d & (1<<i)) { u = fa[u][i]; } }
    return u; } 

int mark[N];

void dfs2(int u, int f) {
    for (int v: e[u]) if (v!=f) {
        mark[v] += mark[u]; 
        dfs2(v,u); } }

namespace NoSolution {
    int deg[N], indeg[N];
    vector <int> e2[N];
    void main() {
        repa (i,n) deg[i] = e[i].size();
        rep (i,m) { e2[us[i]].push_back(vs[i]); indeg[vs[i]]++; }
        queue <int> que;
        repa (i,n) if (deg[i]==1 && indeg[i] == 0) que.push(i);
        int took = 0;
        while (!que.empty()) {
            int u = que.front(); que.pop(); took++;
            see(u);
            for (int v: e[u]) { deg[v]--; if (deg[v]==1 && indeg[v]==0) que.push(v); }
            for (int v:e2[u]) { indeg[v]--; if (deg[v]==1 && indeg[v]==0) que.push(v); } }
        if (took < n-1) {
            rep (i,n) puts("0");
            throw int(0); }
    }
}

void solve() {
    dfs(1,0);
    rep (i,m) {
        int u,v; scanf(II,&u,&v); us[i]=u; vs[i]=v;
        int du = dep[u], dv = dep[v];
        if (du < dv && up(v, dv-du) == u) { mark[1]++; mark[ up(v,dv-du-1) ]--; }
        else { mark[u]++; } }
    NoSolution::main();
    dfs2(1,0);
    repa (i,n) printf(IN,!mark[i]);
}

