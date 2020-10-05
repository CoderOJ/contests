#define ENABLE_LL
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

typedef pair < int , int > pr; 
typedef pair < pr  , int > prr; 
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); } 
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); } 
void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } } 
bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }
#define L first
#define R second

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#define ses(a) std::cout << #a << "=" << a << " " 
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#define ses(a)
#endif

#ifndef CUSTOM_MAIN

void preInit();
void init(); 
void solve(); 

int32_t main(){ 
preInit();

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
while(1) {
    try {init(); } 
    catch(bool t) {return 0;} 
    solve();
}
#else
init(); solve(); 
#endif /* MULTIPLE_TEST_CASES_WITHOUT_T  */

#endif /* MULTIPLE_TEST_CASES_WITH_T */
    return 0;
}

#endif /* CUSTOM_MAIN */

// my code begins here

const int N = 2005;
const int T = 52;
struct Tea { int c,w,v; };
vector <Tea> t;
int n,m;

int dp[2][N*T];

void preInit() {

}

void init() {
    scanf(II,&n,&m); 
    rep (i,n) {
        int c,w,v; scanf(III,&c,&w,&v);
        t.push_back( {c,w,-v} ); }
    rep (i,m) {
        int c,w,v; scanf(III,&c,&w,&v);
        t.push_back( {-c,w,v} ); }
    sort( t.begin(), t.end(), [] ( Tea a, Tea b ) { return a.w == b.w ? a.c > b.c : a.w > b.w; } );
    for (Tea u: t) { ses(u.c);ses(u.w);see(u.v); }
}

void solve() {
    memset(dp, 0xcf, sizeof dp); dp[1][0] = 0; 
    rep (i,n+m) {
        rep (j,N*T) { dp[i%2][j] = dp[(i+1)%2][j]; }
        rep (j,N*T-55) {
            if (j + t[i].c >= 0 && j + t[i].c < N*T) {
                checkMax( dp[i%2][j+t[i].c] , dp[(i+1)%2][j] + t[i].v ); } } }
    int ans = -0x3f3f3f3f3f3f3f3f;
    rep (i,N*T) { checkMax(ans, dp[(n+m-1)%2][i]); }
    printf(IN,ans);
}
