#include <iostream>
#include <cstdio>
using namespace std; 
#ifndef _LIB_SCANNER
#define _LIB_SCANNER 1

#include <stdio.h>
#include <stdlib.h>

class Scanner {
private:
    static const int BUFFER_SIZE = 10000;
    char buff[BUFFER_SIZE];
    int buffPos, buffLim;

public:
    Scanner () { 
        buffLim = fread(buff, 1, BUFFER_SIZE, stdin);
        buffPos = 0;
    }

private:
    inline void flushBuff() {
        buffLim = fread(buff, 1, BUFFER_SIZE, stdin);
        if (buffLim==0) {
            buff[buffLim++] = '\n';
        }
        buffPos = 0; 
    }

    inline bool isWS(char t) {
        return t==' ' || t=='\n';
    }

    inline bool isDig(char t) {
        return t>='0' && t<='9'; 
    }

    void nextPos() {
        buffPos++;
        if (buffPos == buffLim) {
            flushBuff();
        }
    }

#define getChar() buff[buffPos]

public:
    inline char getchar() {
        char ch=getChar();
        nextPos();
        return ch; 
    }

    inline void next(char* s) {
        while ( isWS(getChar()) ) {
            nextPos(); 
        }
        while ( !isWS(getChar()) ) {
            *s = getChar(); s++;
            nextPos();
        }
        *s = '\0';
    }

    inline void nextLine(char* s) {
        while ( getChar()!='\n' ) {
            nextPos();
        }
        if ( getChar()=='\n' ) {
            nextPos();
        }
        while ( getChar() != '\n' ) {
            *s = getChar(); s++;
            buffPos++;
        }
        *s = '\0';
    }

    inline int nextInt() {
        while ( !isDig(getChar()) && getChar() != '-' ) {
            nextPos();
        }
        int sign = (getChar() == '-') ? nextPos(),-1 : 1;
        int res = 0;
        while (isDig(getChar())) {
            res = res*10 + getChar()-'0';
            nextPos();
        }
        return res * sign; 
    }

    inline double nextDouble() {
        while ( isWS(getChar()) ) {
            nextPos();
        }
        int sign = (getChar() == '-') ? nextPos(),-1 : 1;
        double res = 0;
        while (isDig(getChar())) {
            res = res * 10 + getChar()-'0';
            nextPos();
        }
        if (getChar() == '.') {
            nextPos();
            double ep = 1;
            while (isDig(getChar())) {
                ep *= 0.1;
                res += ep * (getChar()-'0');
                nextPos();
            }
        }
        return sign * res;
    }

    inline char nextChar() {
        while (isWS(getChar())) nextPos();
        char res = getChar(); nextPos();
        return res;
    }

#undef getChar
};
Scanner sc;
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

const int N = 733400;
const long long INF = 0x3f3f3f3f3f3f3f3f;
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
    int dfn[N], dfnCnt; long long dep[N];
    int st[N], stTop; long long m[2][N];
    int lg[N], ll[N][B], d[N];
    
    void dfs(int u, int f) {
        dfn[u] = dfnCnt; ll[dfnCnt][0] = u; dfnCnt++;
        for (int e=eu[u]; e!=-1; e=en[e]) if (ev[e] != f) {
            dep[ev[e]] = dep[u] + ew[e]; d[ev[e]] = d[u]+1;
            dfs(ev[e], u); ll[dfnCnt++][0] = u; } }
#define cmp [this](int a, int b) { return d[a] < d[b]; }
    void init(int u) {
        rep (i,2) rep (j,N) { m[i][j] = -INF; }
        dfnCnt = 0; dfs(u,0); 
        rep (i,B-1) rep (j,dfnCnt-(1<<i)) { ll[j][i+1] = min(ll[j][i], ll[j+(1<<i)][i], cmp); }
        lg[1]=0; repi (i,2,N-1) { lg[i] = lg[i/2]+1; } }
    int lca(int u, int v) {
        int l=dfn[u], r=dfn[v]; if (l>r) { swap(l,r); }
        int s = lg[r-l+1];
        return min(ll[l][s], ll[r-(1<<s)+1][s], cmp); }
    long long update(int u, int v) {
        long long res = max(m[0][u] + m[1][v], m[1][u] + m[0][v]);
        checkMax(m[0][u], m[0][v]); checkMax(m[1][u], m[1][v]);
        return res - 2*dep[u]; }
    long long VTree (Parse us[], int usCnt) {
        rep (i,usCnt) { auto &u=us[i];  m[0][u.u] = m[1][u.u] = -INF; m[u.col][u.u] = u.w; }
        sort(us, us+usCnt, [this](Parse u, Parse v) { return dfn[u.u] < dfn[v.u]; });
        stTop = 0; if (us[0].u != 1) { st[stTop++] = 1; }
        long long res = -INF;
        rep (i,usCnt) { auto &u = us[i];
            while (stTop > 1) {
                int f = st[stTop-1], ff = st[stTop-2]; int l = lca(f, u.u);
                if (l == f) { break; }
                else if (dfn[l] <= dfn[ff]) { checkMax(res, update(ff, f)); stTop--; m[0][f]=m[1][f]=-INF; }
                else { checkMax(res, update(l,f)); stTop--; m[0][f]=m[1][f]=-INF; st[stTop++] = l; break; } }
            st[stTop++] = u.u; }
        while (stTop > 1) {
            int f = st[stTop-1], ff = st[stTop-2];
            checkMax(res, update(ff,f)); m[0][f]=m[1][f]=-INF; stTop--; }
        m[0][1]=m[1][1]=-INF; 
        return res; }
} T2;

struct Tree1 : public Tree{
    long long dep[N];
    int sz[N], ec[N*2];
    int eU,eV,eI,eC,pc; long long eW;

    void init(int u, int f) {
        for (int e=eu[u]; e!=-1; e=en[e]) if (ev[e] != f) {
            dep[ev[e]] = dep[u]+ew[e]; init(ev[e], u); } }
    
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
        getSize(u,u); pc=sz[u]; eC=0x3f3f3f3f;
        getEdge(u,u); ec[eI] = ec[eI^1] = 1; }
    
    Parse p[N]; int pCnt;
    void get(int u, int f, long long dis, int col) {
        if (u<=n) { p[pCnt++] = {u,col,dis+dep[u]}; }
        for (int e=eu[u]; e!=-1; e=en[e]) if (ev[e] != f && !ec[e]) {
            get(ev[e], u, dis+ew[e], col); } }
    long long dfs(int u) {
        getCut(u); if (pc == 1) { return -INF; }
        pCnt=0; get(eU,0,0,0); get(eV,0,0,1); 
        long long ans = T2.VTree(p,pCnt) + eW;
        int _eU=eU, _eV=eV; checkMax(ans, dfs(_eU)); checkMax(ans, dfs(_eV)); 
        return ans; }
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
    rep (i,n-1) { int u=sc.nextInt(), v=sc.nextInt(); long long w=sc.nextInt(); T0.addEdge(u,v,w); }
    rep (i,n-1) { int u=sc.nextInt(), v=sc.nextInt(); long long w=sc.nextInt(); T2.addEdge(u,v,w); }
}

long long spj() {
    long long res = -INF;
    repa (i,n) checkMax(res, T1.dep[i]-T2.dep[i]);
    return res; }

void solve() {
    T0.init(); T0.dfs(1,0); 
    T1.init(1,0); T2.init(1);
    long long ans = spj(); checkMax(ans, T1.dfs(1)/2);
    printf("%lld\n",ans);
}
