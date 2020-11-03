/*
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize(3)
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize("unroll-loops") */
#include <iostream>
#include <cstdio>
using namespace std; 
#ifndef _LIB_SCANNER
#define _LIB_SCANNER 1

#include <stdio.h>
#include <stdlib.h>

class Scanner {
private: static const int BUFFER_SIZE = 10000; char buff[BUFFER_SIZE]; int buffPos, buffLim; 
public: Scanner () { buffLim = fread(buff, 1, BUFFER_SIZE, stdin); buffPos = 0; } 
private: inline void flushBuff() { buffLim = fread(buff, 1, BUFFER_SIZE, stdin); if (buffLim==0) { buff[buffLim++] = '\n'; } buffPos = 0; }
    inline bool isWS(char t) { return t==' ' || t=='\n'; } inline bool isDig(char t) { return t>='0' && t<='9'; } 
    void nextPos() { buffPos++; if (buffPos == buffLim) { flushBuff(); } } 
#define getChar() buff[buffPos]
public: inline char getchar() { char ch=getChar(); nextPos(); return ch; } 
    inline void next(char* s) { while ( isWS(getChar()) ) { nextPos(); } while ( !isWS(getChar()) ) { *s = getChar(); s++; nextPos(); } *s = '\0'; } 
    inline void nextLine(char* s) { while ( getChar()!='\n' ) { nextPos(); } if ( getChar()=='\n' ) { nextPos(); } while ( getChar() != '\n' ) { *s = getChar(); s++; buffPos++; } *s = '\0'; } 
    inline int nextInt() { while ( !isDig(getChar()) && getChar() != '-' ) { nextPos(); } int sign = (getChar() == '-') ? nextPos(),-1 : 1; int res = 0; while (isDig(getChar())) { res = res*10 + getChar()-'0'; nextPos(); } return res * sign; }
    inline double nextDouble() { while ( isWS(getChar()) ) { nextPos(); } int sign = (getChar() == '-') ? nextPos(),-1 : 1; double res = 0; while (isDig(getChar())) { res = res * 10 + getChar()-'0'; nextPos(); } if (getChar() == '.') { nextPos(); double ep = 1; while (isDig(getChar())) { ep *= 0.1; res += ep * (getChar()-'0'); nextPos(); } } return sign * res; } 
    inline char nextChar() { while (isWS(getChar())) nextPos(); char res = getChar(); nextPos(); return res; } 
#undef getChar
}; Scanner sc;
#endif /* _LIB_SCANNER */
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
template <typename T> void __ses(T a) { cout << a << " "; }
template <typename T, typename ... Args> void __ses(T a, Args... b) { cout << a << " "; __ses(b...); }
#define ses(...) { cout << #__VA_ARGS__ << " = "; __ses(__VA_ARGS__); }
#define see(...) { ses(__VA_ARGS__); cout << endl; }
#define slog(format, ...) printf(format, __VA_ARGS__)
#else
#define see(...) 
#define ses(...)
#define slog(format, ...)
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

const long long MOD = 998244353;
const int N = 600005;
long long ans = 0;
int n;

struct Tree {
    int eu[N], ev[N*2], en[N*2]; int ew[N*2];
    int cnt;

    Tree () { memset(eu, -1, sizeof(eu)); memset(en, -1, sizeof(en)); cnt = 0; }
    void addEdge (int u, int v, long long w) {
        en[cnt] = eu[u]; eu[u] = cnt; ev[cnt] = v; ew[cnt] = w; cnt++;
        en[cnt] = eu[v]; eu[v] = cnt; ev[cnt] = u; ew[cnt] = w; cnt++; }
};

struct Parse { int col; long long w; };
namespace T2 {
    int eu[N], ev[N*2], en[N*2]; int ew[N*2];
    int cnt;
    void iinit() { memset(eu, -1, sizeof(eu)); memset(en, -1, sizeof(en)); cnt = 0; }
    void addEdge (int u, int v, long long w) {
        en[cnt] = eu[u]; eu[u] = cnt; ev[cnt] = v; ew[cnt] = w; cnt++;
        en[cnt] = eu[v]; eu[v] = cnt; ev[cnt] = u; ew[cnt] = w; cnt++; }

    static const int B = 21;
    int dfn[N], dfnCnt;
    int st[N], stTop; 
    struct Node {
        unsigned long long sz[2], wei[2], sum[2], sdep[2];
        void clear() { sz[0]=sz[1]=wei[0]=wei[1]=sum[0]=sum[1]=sdep[0]=sdep[1]=0; }};
    Node t[N];

// ST for LCA, ignore
    unsigned int lg[N], ll[N][B], d[N];
    void dfs(int u, int f) {
        t[u].clear();
        dfn[u] = dfnCnt; ll[dfnCnt][0] = u; dfnCnt++;
        for (int e=eu[u]; e!=-1; e=en[e]) if (ev[e] != f) {
            d[ev[e]] = d[u]+1;
            dfs(ev[e], u); ll[dfnCnt++][0] = u; } }
#define cmp [](int a, int b) { return d[a] < d[b]; }
    void init(int u) {
        dfnCnt = 0; dfs(u,0); 
        rep (i,B-1) rep (j,dfnCnt-(1<<i)) { ll[j][i+1] = min(ll[j][i], ll[j+(1<<i)][i], cmp); }
        lg[1]=0; repi (i,2,N-1) { lg[i] = lg[i/2]+1; } }
    int lca(int u, int v) {
        int l=dfn[u], r=dfn[v]; if (l>r) { swap(l,r); }
        int s = lg[r-l+1];
        return min(ll[l][s], ll[r-(1<<s)+1][s], cmp); }
#undef cmp
// End ST for LCA

#define C(a) { if(a>=MOD) a-=MOD; }
    void update(int u, int v, int wmid) {
        int w = d[v] - d[u];
        (t[v].sum[0] += w*t[v].wei[0]) %= MOD; (t[v].sum[1] += w*t[v].wei[1]) %= MOD;
        (t[v].sdep[0] += w*t[v].sz[0]) %= MOD; (t[v].sdep[1] += w*t[v].sz[1]) %= MOD;
        (ans += t[u].sum[0] * t[v].sz[1] + t[u].sum[1] * t[v].sz[0]);
        (ans += t[u].wei[0] * t[v].sdep[1] + t[u].wei[1] * t[v].sdep[0]) ;
        (ans += t[v].wei[0] * t[u].sdep[1] + t[v].wei[1] * t[u].sdep[0]) ;
        (ans += t[v].sum[0] * t[u].sz[1] + t[v].sum[1] * t[u].sz[0]) %= MOD; 
        if (wmid) { 
            (ans += t[u].sdep[0] * t[v].sz[1] + t[v].sdep[1] * t[u].sz[0]) ;
            (ans += t[u].sdep[1] * t[v].sz[0] + t[v].sdep[0] * t[u].sz[1]) %= MOD; }
        t[u].sz[0] += t[v].sz[0]; t[u].sz[1] += t[v].sz[1];
        (t[u].wei[0] += t[v].wei[0]) ;  (t[u].wei[1] += t[v].wei[1]); C(t[u].wei[0]); C(t[u].wei[1]);
        (t[u].sum[0] += t[v].sum[0]) ; (t[u].sum[1] += t[v].sum[1]) ; C(t[u].sum[0]); C(t[u].sum[1]);
        (t[u].sdep[0] += t[v].sdep[0]) ; (t[u].sdep[1] += t[v].sdep[1]) ; C(t[u].sdep[0]); C(t[u].sdep[1]); }
    bool cmp(int a, int b) { return dfn[a] < dfn[b]; }
    void VTree (int uu[], Parse us[], int usCnt, int wmid) {
        rep (i,usCnt) { auto u=us[i];
            t[uu[i]].sz[ u.col ] = 1; t[uu[i]].wei[ u.col ] = u.w; }
        sort(uu, uu+usCnt, cmp);
        stTop = 0; if (uu[0] != 1) { st[stTop++] = 1; }
        rep (i,usCnt) { 
            while (stTop > 1) {
                int f = st[stTop-1], ff = st[stTop-2]; int l = lca(f, uu[i]);
                if (l == f) { break; }
                else if (dfn[l] <= dfn[ff]) { update(ff, f, wmid); stTop--; t[f].clear(); }
                else { update(l,f, wmid); stTop--; t[f].clear(); st[stTop++] = l; break; } }
            st[stTop++] = uu[i]; }
        while (stTop > 1) {
            int f = st[stTop-1], ff = st[stTop-2];
            update(ff,f,wmid); t[f].clear(); stTop--; }
        t[1].clear(); }
}

struct Tree1 : public Tree{
    int dep[N];
    int sz[N], ec[N*2];
    int eU,eV,eI,eC,pc; int eW;

    Tree1 () { memset(ec,0,sizeof(ec)); }
    void getSize(int u, int f) {
        sz[u] = 1;
        for (int e=eu[u]; e!=-1; e=en[e]) if (ev[e] != f && !ec[e]) {
            getSize(ev[e], u); sz[u] += sz[ev[e]]; } }
    void getEdge(int u, int f) {
        for (int e=eu[u]; e!=-1; e=en[e]) if (ev[e] != f && !ec[e]) {
            int cur = max(sz[ev[e]], pc-sz[ev[e]]); 
            if (checkMin(eC, cur)) { eU=u; eV=ev[e]; eI=e; eW=ew[e]; }
            getEdge(ev[e], u); } }
    inline void getCut(int u) {
        getSize(u,u); pc=sz[u]; 
        if (pc == 1) { return; }
        eC=0x3f3f3f3f; getEdge(u,u); ec[eI] = ec[eI^1] = 1; }
    
    int pu[N]; Parse p[N]; int pCnt;
    void get(int u, int f, long long dis, int col) {
        if (u<=n) { pu[pCnt] = u; p[pCnt++] = {col,dis}; }
        for (int e=eu[u]; e!=-1; e=en[e]) if (ev[e] != f && !ec[e]) {
            get(ev[e], u, dis+ew[e], col); } }
    void dfs(int u) {
        getCut(u); if (pc == 1) { return; }
        pCnt=0; get(eU,0,0,0); get(eV,0,0,1); 
        if (pCnt > 1) { T2::VTree(pu,p,pCnt,eW); }
        int _eU=eU, _eV=eV; dfs(_eU); dfs(_eV); }
} T1;

struct Tree0 : public Tree {
    int vuCnt;
    void init() { vuCnt = n+1; }
    void dfs(int u, int f) {
        int last = u;
        int cnt = 0;
        for (int e=eu[u]; e!=-1; e=en[e]) if (ev[e] != f) {
            if (cnt == 0) { T1.addEdge(u,ev[e],ew[e]); }
            else { T1.addEdge(last, vuCnt, 0); T1.addEdge(vuCnt, ev[e], ew[e]); last=vuCnt++; }
            cnt++; }
        for (int e=eu[u]; e!=-1; e=en[e]) if (ev[e] != f) {
            dfs(ev[e], u); } }
} T0; 

void preInit() { T2::iinit();  } 
void init() {
    n = sc.nextInt();
    rep (i,n-1) { int u=sc.nextInt(), v=sc.nextInt(); T0.addEdge(u,v,1); }
    rep (i,n-1) { int u=sc.nextInt(), v=sc.nextInt(); T2::addEdge(u,v,1); }
}

void solve() {
    T0.init(); T0.dfs(1,0); 
    T2::init(1);
    T1.dfs(1);
    printf("%lld\n",ans);
}
