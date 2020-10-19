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
    inline double nextDouble() { while ( isWS(getChar()) ) { nextPos(); } int sign = (getChar() == '-') ? nextPos(),-1 : 1; double res = 0; while (isDig(getChar())) { res = res * 10 + getChar()-'0'; nextPos(); } if (getChar() == '.') { nextPos(); double ep = 1; while (isDig(getChar())) { ep *= 0.1; res += ep * (getChar()-'0'); nextPos(); } } return sign * res; } 
    inline char nextChar() { while (isWS(getChar())) nextPos(); char res = getChar(); nextPos(); return res; }
#undef getChar
}; Scanner sc;
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

const int N = 100005;
int n,m;

struct LCT {
    struct Node;
    static Node _NUL;
    static Node *NUL;
    static void init() { NUL = &_NUL; }

    struct Node {
        Node *s[2], *f;
        int rev, vt, at;

        Node () { s[0]=s[1]=f=&_NUL; rev=vt=at=0; }
        inline bool isRoot() { if (f==NUL) { return 1; } return f->s[0] != this && f->s[1] != this; }
        inline int getSon() { return this == f->s[1]; }
        inline void pushRev() { rev ^= 1; swap(s[0], s[1]); }
        inline void pushDown() { 
            if (rev) { s[0]->pushRev(); s[1] ->pushRev(); } 
            rev=0; }
        inline void pushUp() { 
            at = vt ^ s[0]->at ^ s[1]->at; }
        void push() { if (!isRoot()) { f->push(); } pushDown(); }
        void rotate() {
            int ss = getSon(); Node *uu=this, *ff=f, *aa=ff->f;
            if (!ff->isRoot()) { aa->s[ ff->getSon() ] = uu; }
            ff->f = uu; ff->s[ss] = uu->s[!ss];
            uu->f = aa; uu->s[!ss] = ff;
            if (ff->s[ss] != NUL) { ff->s[ss]->f = ff; } 
            ff->pushUp(); pushUp(); }
        void _splay() {
            if (isRoot()) { return; } if (f->isRoot()) { rotate(); return; }
            (getSon() == f->getSon() ? f : this) -> rotate(); rotate(); _splay(); }
        Node* splay() { push(); _splay(); return this; }
        void access() {
            Node *u = this, *s = NUL;
            while (u != NUL) { 
                u->splay(); 
                // u->s[1] become virtual, s is no longer virtual
                if (u->s[1] != NUL) { u->vt ^= u->s[1]->at; }
                if (s != NUL) { u->vt ^= s->at; }
                u->s[1] = s; u->pushUp(); 
                s = u; u = u->f; } }
        void makeRoot() { access(); splay(); pushRev(); }
        inline void modify(int val) { makeRoot(); vt^=val; at^=val; }
    } p[N];

    void split(int u, int v) { p[u].makeRoot(); p[v].access(); p[v].splay(); }
    void link(int u, int v) { 
        p[u].makeRoot(); p[v].makeRoot(); 
        p[u].f = &p[v]; p[v].vt ^= p[u].at; p[v].pushUp(); }
    void cut(int u, int v) { split(u,v); p[u].f = p[v].s[0] = NUL; p[v].pushUp(); }

} T;
LCT::Node LCT::_NUL, *LCT::NUL;

int rnd[N*3], uu[N*3], vv[N*3];
int totRnd;

void preInit() { srand(601200539); LCT::init(); }
void init() { sc.nextInt(); n=sc.nextInt(); m=sc.nextInt(); rep (i,n-1) { T.link(sc.nextInt(),sc.nextInt()); } } 
void solve() {
    int cnt2 = 1;
    repa (cs, m) {
        int opt = sc.nextInt();
        if (opt == 1) {
            int ux=sc.nextInt(),uy=sc.nextInt(),vx=sc.nextInt(),vy=sc.nextInt();
            T.cut(ux,uy); T.link(vx,vy); }
        else if (opt == 2) {
            int u=sc.nextInt(),v=sc.nextInt();
            int s = rand(); T.p[u].modify(s); T.p[v].modify(s); totRnd ^= s; 
            uu[cnt2] = u; vv[cnt2] = v; rnd[cnt2++] = s;  }
        else if (opt == 3) {
            int u = sc.nextInt();
            totRnd ^= rnd[u]; T.p[ uu[u] ].modify(rnd[u]); T.p[ vv[u] ].modify(rnd[u]); }
        else {
            int u=sc.nextInt(), v=sc.nextInt();
            T.split(u,v);
            if ((T.p[u].vt) == totRnd) { puts("YES"); } else { puts("NO"); } } }
}
