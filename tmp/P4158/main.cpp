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




const int N = 55;
const int M = 2505;

int a[N][N];
int n, m, t;

void preInit() { } 
void init()
  {
    n = sc.n(); 
    m = sc.n(); 
    t = sc.n();
    rep (i,n) 
      { 
        rep (j,m) 
          {
            a[i][j] = sc.nextChar() - '0';
          }
      }
  }

int val[N][N];

void getVal(int r)
  {
    int sum[N];
    rep (i,m) sum[i+1] = sum[i] + a[r][i];
    auto getInter = [sum](int l, int r) 
      {
        int len = r-l+1, has = sum[r+1] - sum[l];
        return max(has, len-has); 
      };
    int dp[N]; memset(dp,0,sizeof(dp));
    repa (i,min(t,m)) 
      {
        int udp[N];
        memset(udp,0,sizeof(udp));
        repb (i,m,1)
          rep (j,i+1) 
            checkMax(udp[i], dp[j] + getInter(j,i-1));
        repa (j,m)
          checkMax(val[r][i], udp[j]);
        repa (j,m)
          dp[j] = udp[j];
      }
  }

int dp[M];

void solve() 
  {
    rep (i,n)
      getVal(i);
    rep (i,n)
      repa (j,t)
        see(i,j,val[i][j]);
    rep (i,n) 
      repb (j,t,0)
        repa (k,m)
          if (j-k >= 0)
            checkMax( dp[j], dp[j-k] + val[i][k] );
    int ans = 0;
    repa (i,t) 
      checkMax (ans, dp[i]);
    printf("%d\n", ans);
  }
