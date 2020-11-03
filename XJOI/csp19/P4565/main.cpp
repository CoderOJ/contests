#pragma GCC optimize(2,3,"Ofast")
#pragma GCC target("avx", "avx2")
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
const int N = 733400;
long long ans = 0;
int n;

struct Tree {
    int eu[N], ev[N*2], en[N*2]; long long ew[N*2];
    int cnt;

    Tree () { memset(eu, -1, sizeof(eu)); memset(en, -1, sizeof(en)); cnt = 0; }
    void addEdge (int u, int v, long long w) {
        en[cnt] = eu[u]; eu[u] = cnt; ev[cnt] = v; ew[cnt] = w; cnt++;
        en[cnt] = eu[v]; eu[v] = cnt; ev[cnt] = u; ew[cnt] = w; cnt++; }
};

struct Parse { int u, col; long long w; };
struct Tree2 : public Tree {
    static const int B = 21;
    int dfn[N], dfnCnt;
    int st[N], stTop; 
    long long sz[2][N], wei[2][N], sum[2][N], sdep[2][N];
    void clear(int u) {
        sz[0][u] = sz[1][u] = 0; wei[0][u] = wei[1][u] = 0;
        sum[0][u] = sum[1][u] = 0; sdep[0][u] = sdep[1][u] = 0; }

// ST for LCA, ignore
    int lg[N], ll[N][B], d[N];
    void dfs(int u, int f) {
        clear(u);
        dfn[u] = dfnCnt; ll[dfnCnt][0] = u; dfnCnt++;
        for (int e=eu[u]; e!=-1; e=en[e]) if (ev[e] != f) {
            d[ev[e]] = d[u]+1;
            dfs(ev[e], u); ll[dfnCnt++][0] = u; } }
#define cmp [this](int a, int b) { return d[a] < d[b]; }
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

    void update(int u, int v, int wmid) {
        int w = d[v] - d[u];
        int vsum[2], vsdep[2];
        vsum[0] = (sum[0][v] + w*wei[0][v]) % MOD; vsum[1] = (sum[1][v] + w*wei[1][v]) % MOD; 
        vsdep[0] = (sdep[0][v] + w*sz[0][v]) % MOD; vsdep[1] = (sdep[1][v] + w*sz[1][v]) % MOD;
        (ans += sum[0][u] * sz[1][v]) %= MOD; (ans += sum[1][u] * sz[0][v]) %= MOD;
        (ans += wei[0][u] * vsdep[1]) %= MOD; (ans += wei[1][u] * vsdep[0]) %= MOD;
        (ans += wei[0][v] * sdep[1][u]) %= MOD; (ans += wei[1][v] * sdep[0][u]) %= MOD;
        (ans += vsum[0] * sz[1][u]) %= MOD; (ans += vsum[1] * sz[0][u]) %= MOD; 
        if (wmid) { 
            (ans += sdep[0][u] * sz[1][v] + vsdep[1] * sz[0][u]) %= MOD;
            (ans += sdep[1][u] * sz[0][v] + vsdep[0] * sz[1][u]) %= MOD; }
        sz[0][u] += sz[0][v]; sz[1][u] += sz[1][v];
        (wei[0][u] += wei[0][v]) %= MOD; (wei[1][u] += wei[1][v]) %= MOD; 
        (sum[0][u] += vsum[0]) %= MOD; (sum[1][u] += vsum[1]) %= MOD;
        (sdep[0][u] += vsdep[0]) %= MOD; (sdep[1][u] += vsdep[1]) %= MOD; }
    void VTree (Parse us[], int usCnt, int wmid) {
        rep (i,usCnt) { auto &u=us[i];  
            sz[ u.col ][u.u] = 1; wei[ u.col ][u.u] = u.w; }
        sort(us, us+usCnt, [this](Parse u, Parse v) { return dfn[u.u] < dfn[v.u]; });
        stTop = 0; if (us[0].u != 1) { st[stTop++] = 1; }
        rep (i,usCnt) { auto &u = us[i];
            while (stTop > 1) {
                int f = st[stTop-1], ff = st[stTop-2]; int l = lca(f, u.u);
                if (l == f) { break; }
                else if (dfn[l] <= dfn[ff]) { update(ff, f, wmid); stTop--; clear(f); }
                else { update(l,f, wmid); stTop--; clear(f); st[stTop++] = l; break; } }
            st[stTop++] = u.u; }
        while (stTop > 1) {
            int f = st[stTop-1], ff = st[stTop-2];
            update(ff,f,wmid); clear(f); stTop--; }
        clear(1); }
} T2;

struct Tree1 : public Tree{
    long long dep[N];
    int sz[N], ec[N*2];
    int eU,eV,eI,eC,pc; long long eW;

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
    
    Parse p[N]; int pCnt;
    void get(int u, int f, long long dis, int col) {
        if (u<=n) { p[pCnt++] = {u,col,dis}; }
        for (int e=eu[u]; e!=-1; e=en[e]) if (ev[e] != f && !ec[e]) {
            get(ev[e], u, dis+ew[e], col); } }
    void dfs(int u) {
        getCut(u); if (pc == 1) { return; }
        pCnt=0; get(eU,0,0,0); get(eV,0,0,1); 
        T2.VTree(p,pCnt,eW);
        int _eU=eU, _eV=eV; dfs(_eU); dfs(_eV); }
} T1;

struct Tree0 : public Tree {
    int vuCnt;
    void init() { vuCnt = n+1; }
    void dfs(int u, int f) {
        int last = u;
        for (int e=eu[u]; e!=-1; e=en[e]) if (ev[e] != f) {
            T1.addEdge(last, vuCnt, 0); T1.addEdge(vuCnt, ev[e], ew[e]); last=vuCnt++; }
        for (int e=eu[u]; e!=-1; e=en[e]) if (ev[e] != f) {
            dfs(ev[e], u); } }
} T0; 

void preInit() { } 
void init() {
    n = sc.nextInt();
    rep (i,n-1) { int u=sc.nextInt(), v=sc.nextInt(); T0.addEdge(u,v,1); }
    rep (i,n-1) { int u=sc.nextInt(), v=sc.nextInt(); T2.addEdge(u,v,1); }
}

void solve() {
    T0.init(); T0.dfs(1,0); 
    T2.init(1);
    T1.dfs(1);
    printf("%lld\n",ans);
}
