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
        while ( !isDig(getChar()) ) {
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
#ifndef _LIB_ARRAY
#define _LIB_ARRAY 1
namespace Array {

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

}
#endif /* _LIB_ARRAY */
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <stack>
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
    Array::Array <N, vector<pr>> e;
    
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
        int dfn[N], dep[N], fa[N][B], d[N];
        int dfnCnt;
        pr st[N];

    public: 
        void dfs(int u, int f) { 
            dfn[u] = dfnCnt++; 
            fa[u][0] = f; rep (i,B-1) { fa[u][i+1] = fa[ fa[u][i] ][i]; }
            for (pr v: this->e[u]) if (v.L != f) {
                dep[v.L] = dep[u] + v.R; d[v.L] = d[u] + 1;
                dfs(v.L, u); } }
        void init(int u) {
            dfnCnt = 1; dfs(u,0); }
        void up(int& u, int d) {
            repb (i,B-1,0) if ((d>>i)&1) { u = fa[u][i]; } }
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
                        T.addEdge( ff.R, f.R, dep[f.L]-dep[ff.L] ); stTop--; }
                    else { 
                        T.addEdge( vnodeCnt, f.R, dep[f.L]-dep[l]); stTop--; 
                        st[stTop++] = {l,vnodeCnt}; vnodeCnt++; break; } }
                T.setColor(vnodeCnt, 1); 
                st[stTop++] = {u,vnodeCnt++}; } 
            while (stTop > 1) {
                pr f = st[stTop-1], ff = st[stTop-2];
                T.addEdge(ff.R, f.R, dep[f.L] - dep[ff.L]); 
                stTop--; } 
            T.setN( static_cast<int>(us.size()) ); }
};


// my code begins here

template <int N> class TreeDp : public Tree<N> {
    protected:
        static const int INF = 0x3f3f3f3f;
        Array::Array<N,int> col;
        int n;

        int sz[N], far[N], clo[N];

    public:
        long long ansAll, ansFar, ansClo;

        void setColor(int u, int c) { col[u] = c; }
        void setN(int _n) { n = _n; }
        void clear() { this->Tree<N>::clear(); ansAll=0; ansFar=0; ansClo=0x3f3f3f3f; col.clear(); }
        void dfs(int u=1, int f=0) { 
            sz[u] = col[u];
            far[u] = col[u] ? 0 : -INF;
            clo[u] = col[u] ? 0 :  INF;
            for (pr v: this->e[u]) if (v.L != f) {
                dfs(v.L, u); sz[u] += sz[v.L];
                ansAll += v.R * 1LL*sz[v.L]*(n-sz[v.L]);
                checkMin(ansClo, 0LL+clo[u]+clo[v.L]+v.R); checkMin(clo[u], clo[v.L] + v.R);
                checkMax(ansFar, 0LL+far[u]+far[v.L]+v.R); checkMax(far[u], far[v.L] + v.R); } } 
};

const int N = 1000005;
TreeV<N> T;
TreeDp<N> VT;
int n;

void preInit() {
    n = sc.nextInt();
    rep (i,n-1) { int u=sc.nextInt(), v=sc.nextInt(); T.addEdge(u,v,1); }
    T.init(1);
}

void init() { } 
void solve() {
    int q = sc.nextInt();
    while (q--) {
        vector <int> us; int n=sc.nextInt(); rep (i,n) { us.push_back(sc.nextInt()); }
        VT.clear();
        T.getVTree(us, VT);
        VT.dfs();
        printf("%lld %lld %lld\n", VT.ansAll, VT.ansClo, VT.ansFar); }
}
