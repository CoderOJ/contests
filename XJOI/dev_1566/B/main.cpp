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

const int N = 300005;
int n;

void getXYT(int& x, int& y, int& t, int la) {
    scanf(III,&x,&y,&t);
    x = (x-1+la)%n+1; 
    y = (y-1+la)%n+1;
    t = (t-1+la)%n+1; }

class BF {
    protected:
        static const int B = 20;
        vector <int> e[N]; int w[N], v[N];
        int q,ty,lans;
        int dep[N], fa[N][B];

    public:
        void init() { 
            scanf(III,&n,&q,&ty); 
            rep (i,n-1) { int u,v; scanf(II,&u,&v); e[u].push_back(v); e[v].push_back(u); } 
            repa (i,n) scanf(I,&w[i]);
            repa (i,n) scanf(I,&v[i]); }
        void dfs(int u, int f) {
            fa[u][0] = f; rep (i,B-1) { fa[u][i+1] = fa[ fa[u][i] ][i]; }
            dep[u] = dep[f] + 1;
            for (int v: e[u]) if (v!=f) {
                dfs(v,u); } }
        void up(int &u, int d) {
            repb (i,B-1,0) { if ((d>>i)&1) { u = fa[u][i]; }} }
        int lca(int u, int v) {
            if (dep[u] < dep[v]) { swap(u,v); } up(u,dep[u] - dep[v]);
            repb (i,B-1,0) { if (fa[u][i] != fa[v][i]) { u = fa[u][i]; v = fa[v][i]; } }
            return u==v ? u : fa[u][0]; }
        inline int calc(int u, int t) { 
            return max(0LL, w[u]+t*v[u]); }
        int getAns(int u, int v, int t) {
            int l = lca(u,v); int t1 = t, t2 = t + dep[u]+dep[v]-dep[l]*2;
            int ans = 0;
            int uu = u; while (uu != l) { ans += calc(uu,t1); uu=fa[uu][0]; t1++; } 
            ans += calc(l,t1); 
            int vv = v; while (vv != l) { ans += calc(vv,t2); vv=fa[vv][0]; t2--; }
            return ans; }
        void main() {
            init(); dfs(1,0);
            lans = 0;
            rep (i,q) {
                int u,v,t; getXYT(u,v,t,lans * ty);
                printf(IN, getAns(u,v,t)); } }
};

class V0 {
    protected:
        static const int B = 20;
        vector <int> e[N]; int w[N], v[N];
        int q,ty,lans;
        int dep[N], fa[N][B];

    public:
        void init() { 
            scanf(III,&n,&q,&ty); 
            rep (i,n-1) { int u,v; scanf(II,&u,&v); e[u].push_back(v); e[v].push_back(u); } 
            repa (i,n) { scanf(I,&w[i]); checkMax(w[i],0LL); }
            repa (i,n) scanf(I,&v[i]); }
        void dfs(int u, int f) {
            w[u] += w[f];
            fa[u][0] = f; rep (i,B-1) { fa[u][i+1] = fa[ fa[u][i] ][i]; }
            dep[u] = dep[f] + 1;
            for (int v: e[u]) if (v!=f) {
                dfs(v,u); } }
        void up(int &u, int d) {
            repb (i,B-1,0) { if ((d>>i)&1) { u = fa[u][i]; }} }
        int lca(int u, int v) {
            if (dep[u] < dep[v]) { swap(u,v); } up(u,dep[u] - dep[v]);
            repb (i,B-1,0) { if (fa[u][i] != fa[v][i]) { u = fa[u][i]; v = fa[v][i]; } }
            return u==v ? u : fa[u][0]; }
        void main() {
            init(); dfs(1,0);
            lans = 0;
            rep (i,q) {
                int u,v,t; getXYT(u,v,t,lans * ty); 
                int l = lca(u,v);
                printf(IN, w[u] + w[v] - w[l] - w[fa[l][0]]); } }
};

void solve() {
    int T; scanf(I,&T);
    if (T <= 4) {
        BF Func; Func.main(); }
    else if (T == 5) {
        V0 Func; Func.main(); }
    else {
        BF Func; Func.main(); }
}




void preInit() { } void init() { }
