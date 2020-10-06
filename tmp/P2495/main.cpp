#define MULTIPLE_TEST_CASES_WITH_T
#include <iostream>
#include <cstdio>
using namespace std; 
#ifndef _LIB_ARRAY
#define _LIB_ARRAY 1

template <int N, class T> class Array {
protected:
    T a[N]; int upt[N];
    int t;

public:
    Array () {
        t=0; for (int i=0;i<N;i++) upt[i]=0; }
    T& operator [] (const int i) {
        if (upt[i] < t) {
            a[i] = T(); upt[i] = t; }
        return a[i]; }
    void clear() {
        t++; }
};

#endif /* _LIB_ARRAY */
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

template <int N> struct Tree {
    Array <N, vector<pr>> e;
    
    void addEdge(int u, int v, int w) {
        ses(u);ses(v);see(w);
        e[u].push_back( {v,w} );
        e[v].push_back( {u,w} ); }
    void clear() {
        e.clear(); }
};

template <int N> class TreeV : public Tree<N> {
    protected:
        static const int B = 22;
        int dfn[N], fa[N][B], d[N];
        int mc[N][B];
        int dfnCnt;
        pr st[N];

    public: 
        TreeV () { memset(mc,0x3f3f3f3f,sizeof(mc)); }
        void dfs(int u, int f) { 
            dfn[u] = dfnCnt++; 
            fa[u][0] = f; rep (i,B-1) { fa[u][i+1] = fa[ fa[u][i] ][i]; }
            rep (i,B-1) { mc[u][i+1] = min( mc[u][i], mc[ fa[u][i] ][i] ); }
            for (pr v: this->e[u]) if (v.L != f) {
                mc[v.L][0] = v.R;
                d[v.L] = d[u] + 1; dfs(v.L, u); } }
        void init(int u) {
            dfnCnt = 1; dfs(u,0); }
        void up(int& u, int d) {
            repb (i,B-1,0) if ((d>>i)&1) { u = fa[u][i]; } }
        int getMc(int u, int d) {
            int res = 0x3f3f3f3f;
            repb (i,B-1,0) if ((d>>i)&1) { checkMin(res, mc[u][i]); u = fa[u][i]; } 
            return res; }
        int lca(int u, int v) {
            if (d[u] < d[v]) { swap(u,v); } up(u,d[u]-d[v]);
            repb (i,B-1,0) { if (fa[u][i] != fa[v][i]) { u=fa[u][i]; v=fa[v][i]; } }
            return u==v ? u : fa[u][0]; }
        template <class TT> void getVTree(vector <int> &us, TT& T) {
            sort(us.begin(), us.end(), [&](int a, int b) { return dfn[a] < dfn[b]; }); 
            int vnodeCnt=1; int stTop = 0; 
            if (*us.begin() != 1) { st[stTop++] = {1,vnodeCnt++}; }
            for (int u: us) {
                while (stTop > 1) {
                    pr f = st[stTop-1], ff = st[stTop-2];
                    int l = lca(u,f.L);
                    if (l == f.L) { 
                        break; }
                    else if ( d[l] <= d[ff.L] ) { 
                        T.addEdge( ff.R, f.R, getMc(f.L, d[f.L]-d[ff.L]) ); stTop--; }
                    else { 
                        T.addEdge( vnodeCnt, f.R, getMc(f.L, d[f.L]-d[l])); stTop--; 
                        st[stTop++] = {l,vnodeCnt}; vnodeCnt++; break; } }
                T.setColor(vnodeCnt); st[stTop++] = {u,vnodeCnt++}; } 
            while (stTop > 1) {
                pr f = st[stTop-1], ff = st[stTop-2];
                T.addEdge(ff.R, f.R, getMc(f.L, d[f.L] - d[ff.L]));
                stTop--; } }
};


// my code begins here

template <int N> class TreeDp : public Tree<N> {
    protected:
        static const long long  INF = static_cast<long long>(1e12);
        Array <N,int> col;

    public:
        void clear() {
            this->Tree<N>::clear();
            col.clear(); }
        void setColor(int u) { col[u] = 1; }
        long long dp(int u, int f) {
            if (f != 0 && this->e[u].size() == 1) {
                return INF; }
            long long ans = 0;
            for (pr p: this->e[u]) if (p.L != f) {
                if (col[p.L]==0) { ans += min( 1LL*p.R, dp(p.L,u) ); }
                else { ans += p.R; } }
            return ans; }
};

const int N = 250005;
TreeV <N> T1;
TreeDp <N> T2;
int n;

void preInit() {
    scanf(I,&n);
    rep (i,n-1) { int u,v,w; scanf(III,&u,&v,&w); T1.addEdge(u,v,w); }
    T1.init(1);
}

void init() {
    int m; scanf(I,&m);
    vector <int> us;
    rep (i,m) { int u; scanf(I,&u); us.push_back(u); }
    T2.clear();
    T1.getVTree(us, T2);
}

void solve() {
    printf("%lld\n", T2.dp(1,0));
}
