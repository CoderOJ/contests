#pragma GCC optimize(2,3,"Ofast")
#pragma GCC target("avx", "avx2")
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
typedef std::pair < int , int > pr; 
typedef std::pair < pr  , int > prr; 
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); } 
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); } 
void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } } 
bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }
#define L first
#define R second

#ifdef __LOCALE__
template <typename T> void __ses(T a) { cout << a << " "; }
template <typename T, typename ... Args> void __ses(T a, Args... b) { cout << a << " "; __ses(b...); }
#define ses(...) cout << #__VA_ARGS__ << " = "; __ses(__VA_ARGS__)
#define see(...) ses(__VA_ARGS__); cout << endl
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


const int MOD = 998244353;
const int N = 1000005;
int n,m;

struct Tree {
    int32_t ef[N], en[N*2], ev[N*2], ec;
    int ew[N*2];
    Tree () { memset(ef,-1,sizeof(ef)); memset(en,-1,sizeof(en)); ec=0; }
    void addEdge(int u, int v, int w) {
        en[ec] = ef[u]; ef[u] = ec; ev[ec] = v; ew[ec] = w; ec++;
        en[ec] = ef[v]; ef[v] = ec; ev[ec] = u; ew[ec] = w; ec++; }
};

int power(int a, int b) {
    int r=1; 
    for (;b;b>>=1) {
        if (b&1) (r*=a) %= MOD;
        (a*=a) %= MOD; }
    return r; }

inline void check2(int &a, int &b, int c) {
    if (c >= a) { b=a; a=c; }
    else if (c >= b) { b=c; } }

struct Tree0 : public Tree {
    int way[N], mdep[N][2]; int ans, sum;
    int32_t vis[N];     
    Tree0 () { sum = ans = 0; }
    void dfs(int32_t u, int32_t f) {
        mdep[u][0] = mdep[u][1] = 0; way[u] = 1; vis[u] = 1; ans++;
        for (int32_t e=ef[u]; e!=-1; e=en[e]) if (ev[e] != f) {
            dfs(ev[e], u); 
            {   int nd1 = mdep[ev[e]][0] + ew[e];
                check2( mdep[u][0], mdep[u][1], nd1 ); }
            (ans += way[u] * way[ev[e]]) %= MOD; (way[u] += way[ev[e]]*2) %= MOD; } }
    void dfs1(int32_t u, int32_t f, int up, int upDep) {
        (sum += max(upDep + mdep[u][0], mdep[u][0] + mdep[u][1])%MOD) %= MOD;
        (sum += mdep[u][0]%MOD * up) %= MOD;
        (up = up*2+1) %= MOD;
        for (int32_t e=ef[u]; e!=-1; e=en[e]) if (ev[e] != f) {
            int ne = (up+way[u]-way[ev[e]]*2-1+MOD*3) % MOD;
            (sum += ew[e] * ne % MOD * way[ev[e]]) %= MOD;
            {   int vupDep = max(upDep, (mdep[u][0]==mdep[ev[e]][0]+ew[e]) ? mdep[u][1] : mdep[u][0]);
                (sum += vupDep%MOD * way[ev[e]]) %= MOD;
                dfs1(ev[e], u, ne, (vupDep+ew[e])); } } }
    void get() {
        repa (i,n) if (!vis[i]) { dfs(i,i); dfs1(i,i,0,0); }
        printf(IN, sum * power(ans,MOD-2) % MOD); }
} T;

void preInit() { } 
void init() {
    n=sc.nextInt(); m=sc.nextInt();
    rep (i,m) { int u=sc.nextInt(), v=sc.nextInt(), w=sc.nextInt(); T.addEdge(u,v,w); }
}

void solve() {
    T.get();
}
