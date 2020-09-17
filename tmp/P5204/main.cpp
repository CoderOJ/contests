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
#endif
#ifdef ENABLE_LL
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

const int N     = 100005;
const int M     = 1000000000;
const int MOD   = 1000000007;
int a[N];
int n,k;

int power(int a, int b) {
    int r= 1;
    while (b) {
        if (b&1) (r*=a) %= MOD;
        (a*=a) %= MOD; b>>=1; }
    return r; }

int f[N];

int getF(int u, int n) {
    ses(u);see(n);
    f[0] = f[1] = 1;
    int cs = M-u, cp = power(cs,k);
    repi (i,2,n) {
        f[i] = (f[i-1] * (cs+1)) % MOD; 
        if (i-k-1 >= 0) (f[i] += MOD - f[i-k-1]*cp%MOD) %= MOD; } 
    rep (i,n+1) ses(f[i]);see("");
    return f[n]; }
 
void init() {
    scanf(II,&n,&k);
    rep (i,n-k+1) scanf(I,&a[i]);
}

void solve() {
    int ans =1;
    for (int i=0,j; i<n-k+1; i=j) {
        j=i+1; while (a[j] == a[i]) j++;
        ses(i);see(j);
        int len = j-i+k;
        if (i!=0    && a[i] < a[i-1]) len -= k;
        if (j!=n-k+1&& a[j-1] < a[j]) len -= k;
        if (len > 0) (ans *= getF(a[i], len)) %= MOD; }
    printf(IN,ans);
}

