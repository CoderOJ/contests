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
class Intm { private: static unsigned long long MOD; static unsigned long long k; unsigned long long a; public: inline static void setMod(const unsigned long long _MOD) { MOD = _MOD; k = (__uint128_t(1) << 64) / _MOD; } inline static void getModSub(unsigned long long & a) { if (a>=MOD) a-=MOD; } inline static void getModAdd(unsigned long long & a) { if (a < 0) a+=MOD; } inline static void getMod(unsigned long long & a) { unsigned long long q = (unsigned long long)((__uint128_t(k) * a) >> 64); a -= q*MOD; getModSub(a); } inline static unsigned long long power(unsigned long long a, unsigned long long b) { unsigned long long r = 1; while (b) { if (b&1) getMod(r*=a); getMod(a*=a); b>>=1; } return r; } Intm () { a=0; } Intm (unsigned long long _a) : a(_a) {} Intm& operator += (const Intm b) { a += b.a; getModSub(a); return *this; } Intm operator + (const Intm b) const { Intm R(a); return (R += b); } Intm& operator -= (const Intm b) { a -= b.a; getModAdd(a); return *this; } Intm operator - (const Intm b) const { Intm R(a); return (R -= b); } Intm& operator *= (const Intm b) { a *= b.a; getMod(a); return *this; } Intm operator * (const Intm b) const { Intm R(a); return (R *= b); } Intm& operator /= (const Intm b) { a *= power(b.a,MOD-2); getMod(a); return *this; } Intm operator / (const Intm b) const { Intm R(a); return (R /= b); } operator long long() { return (long long)a; } }; unsigned long long Intm::MOD; unsigned long long Intm::k;

const int INF = 0x3f3f3f3f3f3f3f3f;
const int N = 55;
const int M = 2005;
const int W = 3000000;
vector <int> ei[N];
struct Edge { int v,w; } e[M];
int eCnt=0;
int n,m;

void addEdge(int u, int v, int w) {
    ei[u].push_back(eCnt); e[eCnt] = {v,w}; eCnt++;
    ei[v].push_back(eCnt); e[eCnt] = {u,0}; eCnt++; }

void init() {
    scanf(II,&n,&m);
    rep (i,m) {
        int u,v,w;
        scanf(III,&u,&v,&w);
        addEdge(u,v, w*W+1);  }
}

int dep[N], vis[N];
bool bfs() {
    memset(dep,0,sizeof(dep)); memset(vis,0,sizeof(vis));
    dep[1] = 0; vis[1] = 1;
    queue <int> que; que.push(1);
    while (!que.empty()) {
        int u=que.front(); que.pop();
        see(u);
        for (auto p: ei[u]) {
            int v=e[p].v, w=e[p].w;
            if (w == 0 || vis[v]) continue;
            dep[v] = dep[u]+1; vis[v]=1;
            que.push(v); }}
    return vis[n]; }

int ef[N];
int dfs(int u, int delta=INF) {
    ses(u);see(delta);
    if (u==n || delta==0) return delta;
    int res = delta;
    for (int &p=ef[u]; p<(int)ei[u].size(); p++) {
        if (res == 0) break;
        int i = ei[u][p];
        int v=e[i].v, w=e[i].w;
        // ses(v);see(w);
        if (w == 0 || dep[v] != dep[u]+1) continue;
        int left = dfs(v,min(res,w));
        e[i].w -= left; e[i^1].w += left;
        res -= left; }
    return delta - res; }

int Dinic() {
    int res = 0;
    while (bfs()) {
        int add =0; 
        memset(ef,0,sizeof(ef));
        while ((add = dfs(1))) {
            res += add;
            memset(ef,0,sizeof(ef)); } }
    return res; }

void solve() {
    int ans = Dinic();
    printf("%lld ",ans/W);
    printf(IN,ans%W);
}

