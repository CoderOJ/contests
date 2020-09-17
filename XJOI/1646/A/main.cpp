#define ENABLE_LL
#include <iostream>
#include <cstdio>
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
using namespace std; 
#ifndef CUSTOM_MAIN
void init(); void solve(); int main(){ try { 
#ifdef MULTIPLE_TEST_CASES_WITH_T
int T; scanf("%d",&T); while(T--) {init(); solve();} 
#else
#ifdef MULTIPLE_TEST_CASES_WITHOUT_T 
while(1) {try{init(); } catch(bool t){return 0;} solve(); } 
#else
init(); solve(); 
#endif
#endif
} catch (...) { return 0; } return 0; }
#endif
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
#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#define ses(a) std::cout << #a << "=" << a << " " 
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#define ses(a)
#endif
#define repe(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)
#define L first
#define R second
typedef pair < int , int > pr; typedef pair < pr  , int > prr; template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); } template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); } void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } } bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }
class Scanner { private: static const int BUFFER_SIZE = 10000; char buff[BUFFER_SIZE]; int buffPos, buffLim; public: Scanner () { buffPos = BUFFER_SIZE; buffLim = BUFFER_SIZE; } private: inline void flushBuff() { buffLim = fread(buff, 1, BUFFER_SIZE, stdin); if (buffLim == 0) { exit(-1); } buffPos = 0; } inline char getChar() { if (buffPos == buffLim) { flushBuff(); } return buff[ buffPos ]; } inline bool isWS(char t) { return t==' ' || t=='\n'; } inline bool isLF(char t) { return t=='\n'; } public: inline void next(char* s) { while ( isWS(getChar()) ) { buffPos++; } char cur; while ( !isWS((cur=getChar())) ) { *s = cur; s++; buffPos++; } *s = '\0'; } inline void nextLine(char* s) { while ( getChar()!='\n' ) { buffPos++; } if (  getChar()=='\n' ) { buffPos++; } char cur; while ( (cur=getChar()) != '\n' ) { *s = cur; s++; buffPos++; } *s = '\0'; } inline int nextInt() { while ( isWS(getChar()) ) { buffPos++; } int sign = (getChar() == '-') ? ++buffPos,-1 : 1; int res = 0; while (!isWS(getChar())) { res = res*10 + getChar()-'0'; buffPos++; } return res * sign; } inline double nextDouble() { while ( isWS(getChar()) ) { buffPos++; } int sign = (getChar() == '-') ? ++buffPos,-1 : 1; double res = 0; while (!isWS(getChar()) && getChar() != '.') { res = res * 10 + getChar()-'0'; buffPos++; } if (getChar() == '.') { buffPos++; double ep = 1; while (!isWS(getChar())) { ep *= 0.1; res += ep * (getChar()-'0'); buffPos++; } } return sign * res; } inline char nextChar() { char res = getChar(); buffPos++; return res; } };
class Intm { private: static unsigned long long MOD; static unsigned long long k; unsigned long long a; public: inline static void setMod(const unsigned long long _MOD) { MOD = _MOD; k = (__uint128_t(1) << 64) / _MOD; } inline static void getModSub(unsigned long long & a) { if (a>=MOD) a-=MOD; } inline static void getModAdd(unsigned long long & a) { if (a < 0) a+=MOD; } inline static void getMod(unsigned long long & a) { unsigned long long q = (unsigned long long)((__uint128_t(k) * a) >> 64); a -= q*MOD; getModSub(a); } inline static unsigned long long power(unsigned long long a, unsigned long long b) { unsigned long long r = 1; while (b) { if (b&1) getMod(r*=a); getMod(a*=a); b>>=1; } return r; } Intm () { a=0; } Intm (unsigned long long _a) : a(_a) {} Intm& operator += (const Intm b) { a += b.a; getModSub(a); return *this; } Intm operator + (const Intm b) const { Intm R(a); return (R += b); } Intm& operator -= (const Intm b) { a -= b.a; getModAdd(a); return *this; } Intm operator - (const Intm b) const { Intm R(a); return (R -= b); } Intm& operator *= (const Intm b) { a *= b.a; getMod(a); return *this; } Intm operator * (const Intm b) const { Intm R(a); return (R *= b); } Intm& operator /= (const Intm b) { a *= power(b.a,MOD-2); getMod(a); return *this; } Intm operator / (const Intm b) const { Intm R(a); return (R /= b); } operator int()  { return (int)a; }  }; unsigned long long Intm::MOD; unsigned long long Intm::k;


const int N = 200005;
const int B = 20;
vector <int> e[N];
int n,m;

void init() {
    scanf(II,&n,&m);
    rep (i,n-1) { int u,v; scanf(II,&u,&v); e[u].push_back(v); e[v].push_back(u); }
}

int fa[N][B], dep[N];
void dfs(int u, int f) {
    dep[u] = dep[f] + 1; fa[u][0] = f;
    rep (b,B-1) fa[u][b+1] = fa[ fa[u][b] ][b];
    for (int v: e[u]) if (v!=f) {
        dfs(v,u); } }
int up(int u, int d) {
    repb (b,B-1,0) if (d & (1<<b)) u=fa[u][b];
    return u; }
int lca(int u, int v) {
    if (dep[u]<dep[v]) swap(u,v);
    u = up(u, dep[u] - dep[v]);
    repb (b,B-1,0) if (fa[u][b] != fa[v][b]) { u=fa[u][b]; v=fa[v][b]; }
    return u==v? u : fa[u][0]; }

int covers[N];

void dfs2(int u, int f) {
    for (int v:e[u]) if (v!=f) {
        dfs(v,u); covers[u] += covers[v]; } }

void solve() {
    dfs(1,0);
    rep (i,m) {
        int u,v; scanf(II,&u,&v);
        covers[u]++; covers[v]++; covers[lca(u,v)]-=2; }
    dfs2(1,0);
    long long ans = 0;
    repi (i,2,n) {
        if (covers[i] == 0) { ans += m; }
        else if (covers[i] == 1) { ans ++; } }
    printf("%lld\n",ans);
}

