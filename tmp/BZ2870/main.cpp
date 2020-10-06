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

const int N = 100005;
int n;
int a[N];

struct Tree {
    vector <int> e[N];
    void addEdge(int u, int v) {
        e[u].push_back(v); 
        e[v].push_back(u); } };
struct Tree2 {
    struct Edge { int v,w,f; };
    vector <Edge> e[N];
    void addEdge (int u, int v, int w) {
//        printf("%d %d %d\n",u,v,w);
        e[u].push_back( {v,w,1} );
        e[v].push_back( {u,w,1} ); } };
Tree T1;
Tree2 T2;

struct Trans {
    int vnodeCnt; 
    void dfs(int u, int f) {
        int cnt = 0, las = -1;
        for (int v: T1.e[u]) if (v != f) {
            cnt++;
            if (cnt == 1) { las = v; }
            else { a[vnodeCnt] = a[u]; T2.addEdge(vnodeCnt, las, (las<=n)); T2.addEdge(vnodeCnt, v, 1); las = vnodeCnt; vnodeCnt++; } }
        if (las != -1) { T2.addEdge(u,las,(las<=n)); }
        for (int v: T1.e[u]) if (v != f) { dfs(v,u); } }
    void main() {
        vnodeCnt = n+1;
        dfs(1,0); }
};

void preInit() { } 
void init() {
    scanf(I,&n);
    repa (i,n) scanf(I,&a[i]);
    rep (i,n-1) { int u,v; scanf(II,&u,&v); T1.addEdge(u,v); }
}

struct Ep {
    int sz[N];
    void getSize(int u, int f) {
        sz[u] = 1;
        for (Tree2::Edge p : T2.e[u]) if (p.v != f && p.f) {
            getSize(p.v, u); sz[u] += sz[p.v]; } }

    int edgeU, edgeV, edgeW, edgeI, edgeC, totSize;
    void getEdgeInit(int u) { totSize = sz[u]; edgeC = 0x3f3f3f3f; }
    void _getEdge(int u, int f) {
        repe (i,T2.e[u]) { Tree2::Edge& p = T2.e[u][i]; if (p.v != f && p.f) {
            int cost = max( sz[p.v] , totSize - sz[p.v] );
            if (checkMin(edgeC, cost)) { edgeU = u; edgeI = i; edgeV = p.v; edgeW = p.w; }
            _getEdge(p.v, u); } } }
    void getEdge(int u) {
        totSize = sz[u]; edgeC = 0x3f3f3f3f;
        _getEdge(u,0); 
        T2.e[ edgeU ][ edgeI ].f = 0;
        repe (i,T2.e[edgeV]) { if (T2.e[edgeV][i].v == edgeU) { T2.e[edgeV][i].f = 0; } } }

    vector <pr> sA, sB;
    void get(vector <pr>& S, int u, int f, int dep, int val) {
        checkMin(val, a[u]); 
        S.push_back( {val, dep} );
        for (Tree2::Edge p : T2.e[u]) if (p.v != f && p.f) {
            get(S, p.v, u, dep + p.w, val); } }
    long long dfs(int u) {
        see(u);
        getSize(u,0); 
        if (sz[u] == 1) { return 0; }
        getEdge(u);

        sA.clear(); sB.clear();
        get(sA,edgeU,edgeV,0,0x3f3f3f3f); get(sB,edgeV, edgeU,0,0x3f3f3f3f);
        auto _cmp = [](pr a, pr b) { return a>b; };
        sort(sA.begin(), sA.end(), _cmp); sort(sB.begin(), sB.end(), _cmp); 
        vector <int> lab; for (pr i: sA) { lab.push_back(i.L); } for (pr i: sB) { lab.push_back(i.L); }
        sort(lab.begin(), lab.end(), [](int a, int b) { return a>b; });
        int lenA=-edgeW, lenB=-edgeW; int Aid=0, Bid=0;
        long long ans = 0;
        for (int u: lab) {
            while (Aid < (int)sA.size() && sA[Aid].L >= u) { checkMax(lenA, sA[Aid].R); Aid++; }
            while (Bid < (int)sB.size() && sB[Bid].L >= u) { checkMax(lenB, sB[Bid].R); Bid++; }
            ses(edgeU);ses(edgeV);ses(u);ses(lenA);see(lenB);
            checkMax(ans, 1LL*(lenA+lenB+edgeW+1)*u); }
        int pu = edgeU, pv = edgeV;
        checkMax(ans, dfs(pu));
        checkMax(ans, dfs(pv)); 
        return ans; }
};

void solve() {
    Trans _Trans; _Trans.main(); 
    long long preAns=0; repa (i,n) checkMax(preAns, 1LL*a[i]);
    Ep _Ep; printf("%lld\n",max(preAns,_Ep.dfs(1)));
}
