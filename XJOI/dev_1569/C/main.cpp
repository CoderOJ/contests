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

const int MOD = 998244353;
const int N = 30005;
int n,m;
pr e[N];




void preInit() { } 
void init() {
    scanf(II,&n,&m);
    rep (i,n-1) scanf(II, &e[i].L, &e[i].R); 
}

auto power = [](int a, int b) -> int {
    int r = 1;
    while (b) {
        if (b&1) { (r *= a) %= MOD; }
        (a *= a) %= MOD; b>>=1; }
    return r; };

void solve() {
    if (n == 1)  { puts("0"); }
    else if (e[n-2].L == 1)
    {
        int ans = 0;
        (ans += 1*(n-1)) %= MOD;
        (ans += power((n*2-3), m) * (n-1)) %= MOD;
        (ans += power((n*2-2), m) * ((n-1)*(n-2)%MOD) % MOD) %= MOD;
        printf(IN,ans);
    }
    else 
    {
        int dp[N];
        auto fun = [&dp](int l) -> int {
            if (l == 0) { return 0LL; }
            if (l == 1) { return 1LL; }
            dp[0] = 0;
            dp[1] = (l*2-1) % MOD;
            repi (i,2,l) { dp[i] = (2*dp[i-1] - dp[i-2] - 2 + 4*MOD) % MOD; }
            int ans = 0;
            rep (i,l+1) { (ans += power(dp[i],m)) %= MOD; }
            return ans;
        };
        int ans = 0;
        rep (i,n) { (ans += fun(i)) %= MOD; }
        printf(IN,ans*2%MOD);
    }
};
