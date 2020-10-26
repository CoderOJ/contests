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
    inline int n() { while ( getChar()<'0' || getChar()>'9' ) { buffPos++; if ( buffPos == buffLim ) { flushBuff(); } } int res = 0; while ( getChar()>='0' && getChar()<='9' ) { res = res*10 + (getChar()-'0'); buffPos++; if ( buffPos == buffLim ) { flushBuff(); } } return res; }
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
int n,q;

namespace Gcd {
    const int M = 1005;
    int g[M][M];

    void init() {
        rep (i,M) rep (j,i+1) g[i][j] = g[j][i] = __gcd(i,j); }
    int gcd(int a, int b) {
        if (a<M && b<M) { return g[a][b]; }
        return b==0 ? a : gcd(b,a%b); } }
using Gcd::gcd;

namespace STree {
    int a[N<<2];
    void pushUp(int u) {
        a[u] = gcd( a[u+u], a[u+u+1] ); }
    void build(int l, int r, int u) {
        if (l==r) { a[u] = sc.n(); return; }
        int mid = (l+r)/2;
        build(l,mid,u+u); build(mid+1,r,u+u+1); 
        pushUp(u); }
    void modify(int l, int r, int p, int val, int u) {
        if (l==r) { a[u] = val; return; }
        int mid = (l+r)/2;
        if (p<=mid) { modify(l,mid,p,val,u+u); }
        else { modify(mid+1,r,p,val,u+u+1); }
        pushUp(u); }
    int querySplit(int l, int r, int pl, int pr, int u) {
        if (l==r) { return l; }
        int mid = (l+r)/2;
        int vl = gcd(a[u+u], pl), vr = gcd(a[u+u+1], pr);
        if (vl <= vr) { return querySplit(l,mid, pl,vr, u+u); }
        else { return querySplit(mid+1,r, vl,pr, u+u+1); } }
    long long calcPre(int l, int r, int p, int pre, int u) {
        if (l==r) { return gcd(a[u], pre); }
        int vr=gcd(a[u+u+1], pre), vl=gcd(a[u+u],vr);
        int mid = (l+r)/2;
        if (p <= mid) { return calcPre(l,mid,p,vr,u+u); }
        else if (vl == vr) {
            return 1LL * (mid-l+1) * vr  +
                    calcPre(mid+1,r,p,pre,u+u+1); }
        else {
            return  calcPre(l,mid,p,vr,u+u)  +
                    calcPre(mid+1,r,p,pre,u+u+1); } }
    long long calcSuf(int l, int r, int p, int pre, int u) {
        if (l==r) { return gcd(a[u], pre); }
        int vl=gcd(a[u+u], pre), vr=gcd(a[u+u+1],vl);
        int mid = (l+r)/2;
        if (p >  mid) { return calcSuf(mid+1,r,p,vl,u+u+1); }
        else if (vl == vr) {
            return 1LL * (r-mid) * vl  +
                    calcSuf(l,mid,p,pre,u+u); }
        else {
            return  calcSuf(l,mid,p,pre,u+u)  +
                    calcSuf(mid+1,r,p,vl,u+u+1); } }
};



void preInit() { Gcd::init(); } 
void init() { n=sc.n(); q=sc.n(); STree::build(1,n,1); } 
void solve() {
    while (q--) {
        int pos=sc.n(), val=sc.n();
        STree::modify(1,n,pos,val,1);
        int split = STree::querySplit(1,n,0,0,1);
        printf("%lld\n", STree::calcPre(1,n,split,0,1) + STree::calcSuf(1,n,split,0,1) - STree::a[1]); }
}
