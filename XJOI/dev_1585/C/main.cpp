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


const int N = 300005;

struct STree {
    struct Node {
        uint32_t val, tag;
        Node () { val = tag = 0; }
        void pushAdd(uint32_t _v) {
            val += _v; tag += _v; }
        void pushUp(Node &l, Node &r) {
            val = l.val + r.val; }
        void pushDown(Node &l, Node &r) {
            l.pushAdd(tag); r.pushAdd(tag);
            tag = 0; }
    };

    Node a[N*4];
    void modify(int l, int r, int sl, int sr, uint32_t val, int u=1) {
        if (sl <= l && r <= sr) { a[u].pushAdd(val); return; }
        a[u].pushDown(a[u+u], a[u+u+1]); 
        int mid = (l+r) / 2;
        if (sl <= mid) modify(l,mid,sl,sr, val,u+u);
        if (sr > mid) modify(mid+1,r,sl,sr, val,u+u+1);
        a[u].pushUp(a[u+u], a[u+u+1]); }
    uint32_t query(int l, int r, int sl, int sr, int u=1) {
        if (sl <= l && r <= sr) { return a[u].val; }
        a[u].pushDown(a[u+u], a[u+u+1]); 
        int mid = (l+r)/2;
        uint32_t res = 0;
        if (sl <= mid) res += query(l,mid,sl,sr, u+u); 
        if (sr > mid) res += query(mid+1,r,sl,sr, u+u+1);
        return res; }
};


struct LCT {
    struct Node {
        Node *s[2], *f;
        uint32_t sv,st,sl, av,at,al, dv,dt,dl;

        Node () { 
            s[0]=s[1]=f = nullptr; 
            sv=st=sl = av=at=al = dv=dt=dl = 0; }
        bool isRoot() { if (f == nullptr) { return 1; } return f->s[0] != this && f->s[1] != this; }
        int getSon() { return this == f->s[1]; }
        void pushAdds(int _v) { sv+=_v; sl+=_v; st+=_v; }
        void pushAdda(int _v) { av+=_v; al+=_v; at+=_v; }
        void pushAddd(int _v) { dv+=_v; dl+=_v; dt+=_v; }
        void pushDown() { 
            if (s[0] != nullptr) {
                s[0]->pushAdds(sl); s[0]->pushAdda(al); s[0]->pushAddd(dl); }
            if (s[1] != nullptr) {
                s[1]->pushAdds(sl); s[1]->pushAdda(al); s[1]->pushAddd(dl); }
            sl = al = dl = 0; }
        void pushUp() { 
            st=sv; at=av; dt=dv;
            if (s[0] != nullptr) {
                st += s[0]->st; at += s[0]->at; dt += s[0]->dt; }
            if (s[1] != nullptr) {
                st += s[1]->st; at += s[1]->at; dt += s[1]->dt; } }
        void push() { if (!isRoot()) { f->push(); } pushDown(); }
        void rotate() { 
            int ss = getSon(); Node *uu=this, *ff=f, *aa=ff->f;
            if (!ff->isRoot()) { aa->s[ ff->getSon() ] = uu; }
            ff->f = uu; ff->s[ss] = uu->s[!ss];
            uu->f = aa; uu->s[!ss] = ff;
            if (ff->s[ss] != nullptr) { ff->s[ss]->f = ff; }
            ff->pushUp(); uu->pushUp(); }
        void _splay() {
            if (isRoot()) { return; }
            if (f->isRoot()) { rotate(); return; }
            (getSon() == f->getSon() ? f : this) -> rotate(); rotate(); _splay(); }
        Node* splay() { push(); _splay(); return this; }
        void access() {
            Node *uu=this, *ss=nullptr;
            while (uu!=nullptr) {
                uu->splay(); uu->s[1]=ss; uu->pushUp();
                ss=uu; uu=uu->f; } }
        Node* findRoot() {
            access(); splay();
            Node *uu = this; uu->pushDown();
            while (uu->s[0] != nullptr) { uu=uu->s[0]; uu->pushDown(); }
            return uu; }

        void adds(int _v) { splay(); pushAdds(_v); }
        void adda(int _v) { splay(); pushAdda(_v); }
        void addd(int _v) { splay(); pushAddd(_v); }
    };

    Node p[N];
    void link(int u, int f) {
        p[u].f = &p[f]; }
    void cut(int u) {
        p[u].access(); p[u].splay(); 
        Node *ff = p[u].f; p[u].f = nullptr;
        ff->access(); ff->splay(); ff->s[1]=nullptr; }
    void split(int u) {
        p[u].access(); p[u].splay(); }
} T;

vector <int> e[N];
int n,m;
int dfnl[N], dfnr[N], fa[N], dfnCnt=0;

void dfs(int u, int f) {
    fa[u] = f;
    dfnl[u] = dfnCnt++;
    for (int v: e[u]) if (v!=f) { dfs(v,u); }
    dfnr[u] = dfnCnt-1; }


void preInit() { } void init() {
    see(&T.p[1]);
    n = sc.n(); m = sc.n();
    repi (i,2,n) { 
        int f = sc.n();
        T.link(i, f); e[f].push_back(i); }
    repa (i,n) { T.split(i); T.p[i].adds(1); }
    dfs(1,0);
}

void solve() {

}
