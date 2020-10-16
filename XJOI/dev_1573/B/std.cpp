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
int opt,n,q,w;

struct STree {
    struct Node {
        Node *l, *r; int v; 
        Node () { l=r=NULL; v=0; } };

    static Node pool[N*40];
    static int cnt;
    static Node* newNode() { return &pool[cnt++]; }

    Node* r[N];
    void init(int l, int r, Node* &u) {
        u = newNode();
        if (l == r) { return; }
        int mid = (l+r)/2;
        init(l,mid, u->l); init(mid+1,r, u->r); } 
    void modify(int l, int r, int p, Node* f, Node* &u) {
        u = newNode(); *u = *f; u->v++;
        if (l == r) { return; }
        u->l = f->l; u->r = f->r;
        int mid = (l+r)/2;
        if (p <= mid) { modify(l,mid,p,   f->l, u->l); }
        else          { modify(mid+1,r,p, f->r, u->r); } }
    int query(int l, int r, int sl, int sr, Node* u) {
        if (sl <= l && r <= sr) { return u->v; }
        int mid = (l+r)/2, ans = 0;
        if (sl <= mid) ans += query(l,mid,sl,sr,u->l); 
        if (sr > mid) ans += query(mid+1,r,sl,sr,u->r); 
        return ans; }
}; STree::Node STree::pool[N*40]; int STree::cnt = 0;

STree T;

void preInit() { } 
void init() {
    T.init(1,N,T.r[0]);
    n=sc.nextInt(); q=sc.nextInt(); opt=sc.nextInt(); w=sc.nextInt();
    rep (i,n) { int u = sc.nextInt(); checkMin(u, N-2); T.modify(1,N,u, T.r[i], T.r[i+1]); } }

void solve() {
    cerr << "init pass" << endl;
    int lans = 0;
    T.query(1,N,9,9,T.r[10]);
    while (q--) {
        int ul = sc.nextInt(), ur = sc.nextInt(), uw = sc.nextInt();
        if (opt == 1) { ul=(ul^lans)%n; ur=(ur^lans)%n; uw=(uw^lans)%w+1; }
        else { ul--; ur--; }
        if (ul > ur) { swap(ul,ur); }
        int l=1,r; lans=0;
        while (l<=uw) {
            r = uw/(uw/l);
            lans += (uw/l) * (T.query(1,N,l,r,T.r[ur+1]) - T.query(1,N,l,r,T.r[ul]));
            l = r+1; }
        printf(IN,lans); }
}
