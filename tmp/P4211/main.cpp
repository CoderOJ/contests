#define ENABLE_LL
#include <iostream>
#include <cstdio>
using namespace std; 

#ifndef _LIB_SCANNER
#define _LIB_SCANNER 1 
#include <stdio.h>
#include <stdlib.h> 
class Scanner {
private:
    static const int BUFFER_SIZE = 10000; char buff[BUFFER_SIZE]; int buffPos, buffLim; 
public:
    Scanner () { buffLim = fread(buff, 1, BUFFER_SIZE, stdin); buffPos = 0; } 
private:
    inline void flushBuff() { buffLim = fread(buff, 1, BUFFER_SIZE, stdin); if (buffLim==0) { buff[buffLim++] = '\n'; } buffPos = 0; } 
    inline bool isWS(char t) { return t==' ' || t=='\n'; } 
    inline bool isDig(char t) { return t>='0' && t<='9'; } 
    void nextPos() { buffPos++; if (buffPos == buffLim) { flushBuff(); } } 
#define getChar() buff[buffPos]
public:
    inline char getchar() { char ch=getChar(); nextPos(); return ch; } 
    inline void next(char* s) { while ( isWS(getChar()) ) { nextPos(); } while ( !isWS(getChar()) ) { *s = getChar(); s++; nextPos(); } *s = '\0'; } 
    inline void nextLine(char* s) { while ( getChar()!='\n' ) { nextPos(); } if ( getChar()=='\n' ) { nextPos(); } while ( getChar() != '\n' ) { *s = getChar(); s++; buffPos++; } *s = '\0'; } 
    inline int nextInt() { while ( !isDig(getChar()) && getChar() != '-' ) { nextPos(); } int sign = (getChar() == '-') ? nextPos(),-1 : 1; int res = 0; while (isDig(getChar())) { res = res*10 + getChar()-'0'; nextPos(); } return res * sign; } 
    inline long long nextLong() { while ( !isDig(getChar()) && getChar() != '-' ) { nextPos(); } long long sign = (getChar() == '-') ? nextPos(),-1 : 1; long long res = 0; while (isDig(getChar())) { res = res*10 + getChar()-'0'; nextPos(); } return res * sign; } 
    inline int n() { while ( getChar()<'0' || getChar()>'9' ) { buffPos++; if ( buffPos == buffLim ) { flushBuff(); } } int res = 0; while ( getChar()>='0' && getChar()<='9' ) { res = res*10 + (getChar()-'0'); buffPos++; if ( buffPos == buffLim ) { flushBuff(); } } return res; }
    inline long long nl() { while ( getChar()<'0' || getChar()>'9' ) { buffPos++; if ( buffPos == buffLim ) { flushBuff(); } } long long res = 0; while ( getChar()>='0' && getChar()<='9' ) { res = res*10 + (getChar()-'0'); buffPos++; if ( buffPos == buffLim ) { flushBuff(); } } return res; }
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

#ifdef ENABLE_LL
#define int long long
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
#define ses(...) { cout << #__VA_ARGS__ << " = "; __ses(__VA_ARGS__); }
#define see(...) { ses(__VA_ARGS__); cout << endl; }
#define slog(format, ...) printf(format, __VA_ARGS__)
#else
#define see(...) 
#define ses(...)
#define slog(format, ...)
#endif


#ifndef CUSTOM_MAIN
void preInit(); void init(); void solve(); int32_t main(){ preInit(); 
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
while(1) { try {init(); } catch(bool t) {return 0;} solve(); }
#else
init(); solve(); 
#endif /* MULTIPLE_TEST_CASES_WITHOUT_T  */
#endif /* MULTIPLE_TEST_CASES_WITH_T */
    return 0; }
#endif /* CUSTOM_MAIN */

// my code begins here

const int MOD = 201314;
const int N = 50005;

struct LCT {
    struct Node {
        Node *s[2], *f;
        int val, tot, sz, tag;
        Node () { s[0]=s[1]=f=nullptr; val=tot=tag=0; sz=1; }
        bool isRoot() { 
            if (f==nullptr) { return 1; }
            return f->s[0]!=this && f->s[1]!=this; }
        int getSon() { return this == f->s[1]; }
        void pushUp() {
            tot = val; sz = 1;
            if (s[0] != nullptr) { tot += s[0]->tot; sz += s[0]->sz; }
            if (s[1] != nullptr) { tot += s[1]->tot; sz += s[1]->sz; } }
        void pushAdd(int _v) {
            val += _v; tag += _v; tot += _v * sz; }
        void pushDown() {
            if (s[0] != nullptr) { s[0]->pushAdd(tag); }
            if (s[1] != nullptr) { s[1]->pushAdd(tag); }
            tag = 0; }
        void rotate() {
            int ss=getSon(); Node *uu=this, *ff=f, *aa=ff->f;
            if (!ff->isRoot()) { aa->s[ ff->getSon() ] = uu; }
            ff->f = uu; ff->s[ss] = uu->s[!ss];
            uu->f = aa; uu->s[!ss] = ff;
            if (ff->s[ss] != nullptr) { ff->s[ss]->f = ff; } 
            ff->pushUp(); uu->pushUp(); }  
        void _splay() {
            if (isRoot()) { return; }
            if (f->isRoot()) { rotate(); return; }
            ( getSon() == f->getSon() ? f : this ) -> rotate(); rotate(); 
            _splay(); }
        void push() {
            if (!isRoot()) { f->push(); }
            pushDown(); } 
        void splay() { 
            push(); _splay(); }
        void access() {
            Node *uu=this, *ss=nullptr;
            while (uu != nullptr) {
                uu->splay(); uu->s[1] = ss; uu->pushUp();
                ss = uu; uu = uu->f; } }
    };

    Node p[N];
    void split(int u) {
        p[u].access(); p[u].splay(); }
} T;

vector <int> e[N];
int n,m;

void preInit() { } void init() { 
    n = sc.n(); m = sc.n();
    repa (i,n-1) {
        int f = sc.n();
        T.p[i].f = &T.p[f]; 
        e[f].push_back(i); }
}

struct Query { int u,z, id; };
vector <Query> qs;
int ans[N*2];

void solve() {
    rep (i,m) {
        int l=sc.n(), r=sc.n(), z=sc.n();
        qs.push_back( {l-1, z,i*2} );
        qs.push_back( {r, z,i*2+1} ); }
    sort( qs.begin(), qs.end(), [](Query a, Query b) { return a.u < b.u; } );
    int qid = 0;
    while (qs[qid].u == -1) { qid++; }
    rep (i,n) {
        T.split(i); T.p[i].pushAdd(1);
        while (qid < (int)qs.size() && qs[qid].u<=i) {
            T.split(qs[qid].z);
            ans[ qs[qid].id ] = T.p[ qs[qid].z ].tot; 
            qid++; } }
    rep (i,m) { 
        see(ans[i*2], ans[i*2+1]);
        printf("%lld\n", (ans[i*2+1]-ans[i*2]) % MOD); }
}
