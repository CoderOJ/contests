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
#define I "%lld"
#define II "%lld%lld"
#define III "%lld%lld%lld"
#define IIII "%lld%lld%lld%lld"
#define IN "%lld\n"
#define IIN "%lld%lld\n"
#define IIIN "%lld%lld%lld\n"
#define IIIIN "%lld%lld%lld%lld\n"
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
class Scanner { private: static const int BUFFER_SIZE = 10000; char buff[BUFFER_SIZE]; int buffPos, buffLim; public: Scanner () { buffLim = fread(buff, 1, BUFFER_SIZE, stdin); buffPos = 0; } private: inline void flushBuff() { buffLim = fread(buff, 1, BUFFER_SIZE, stdin); if (buffLim==0) { buff[buffLim++] = '\n'; } buffPos = 0; } inline bool isWS(char t) { return t==' ' || t=='\n'; } inline bool isDig(char t) { return t>='0' && t<='9'; } void nextPos() { buffPos++; if (buffPos == buffLim) { flushBuff(); } } 
#define getChar() buff[buffPos]
public: inline char getchar() { char ch=getChar(); nextPos(); return ch; } inline void next(char* s) { while ( isWS(getChar()) ) { nextPos(); } while ( !isWS(getChar()) ) { *s = getChar(); s++; nextPos(); } *s = '\0'; } inline void nextLine(char* s) { while ( getChar()!='\n' ) { nextPos(); } if ( getChar()=='\n' ) { nextPos(); } while ( getChar() != '\n' ) { *s = getChar(); s++; buffPos++; } *s = '\0'; } inline int nextInt() { while ( !isDig(getChar()) ) { nextPos(); } int sign = (getChar() == '-') ? nextPos(),-1 : 1; int res = 0; while (isDig(getChar())) { res = res*10 + getChar()-'0'; nextPos(); } return res * sign; } inline double nextDouble() { while ( isWS(getChar()) ) { nextPos(); } int sign = (getChar() == '-') ? nextPos(),-1 : 1; double res = 0; while (isDig(getChar())) { res = res * 10 + getChar()-'0'; nextPos(); } if (getChar() == '.') { nextPos(); double ep = 1; while (isDig(getChar())) { ep *= 0.1; res += ep * (getChar()-'0'); nextPos(); } } return sign * res; } inline char nextChar() { while (isWS(getChar())) nextPos(); char res = getChar(); nextPos(); return res; } 
#undef getChar
}; 

#define int long long

const int N = 7505;
int fac[N];
int C[N][N];
int isP[N];
int bel[N];
int n,m,M;

int power (int a, int b, int MOD ) { int r=1; while (b) { if (b&1) { (r *=a) %=MOD; } (a*=a)%=MOD; b>>=1; } return r; } 
void init() {
    scanf(II,&n,&m); M = m-1;

    fac[0] = 1; repa (i,n) fac[i] = fac[i-1]*i%M;
    C[0][0] = 1; 
    repa (i,n) { C[i][0] = C[i-1][0]; repa (j,i) { C[i][j] = (C[i-1][j-1] + C[i-1][j])%M; } }
    rep (i,N) isP[i] = 1; isP[1] = 0;
    repi (i,2,n) { if (!isP[i]) { continue; } for (int j=i+i;j<=n;j+=i) { isP[j] = 0; } }
    repi (i,2,n) if (isP[i]) { for (int p=i;p<=n;p*=i) { bel[p] = i; } }
}

int dp[N];
int calc (int s) {
    int MOD = m-1;
    static int dp[N];
    dp[0] = MOD-1;
    int upp = n/s;
    repa (i,upp) {
        dp[i]=0;
        repa (j,i) if (dp[i-j]) {
            (dp[i] -= dp[i-j] * C[i*s-1][j*s-1]%MOD * fac[j*s-1]%MOD -MOD -MOD) %= MOD; } }
    int res = 0;
    repa (i,upp) { (res += dp[i] * C[n][i*s]%MOD * fac[n-i*s]%MOD) %= MOD; }
    return res; }

void solve() {
    int ans = 1;
    repi (i,2,n) if (bel[i]) {
        (ans *= power(bel[i], calc(i), m)) %= m; }
    printf(IN,ans);
}

