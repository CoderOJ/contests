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
using namespace std;

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
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)
typedef pair < int , int > pr;
typedef pair < pr  , int > prr;
#define L first
#define R second
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); }

const int MOD = 1000000009;

int gcd (int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int lcm (int a, int b) {
    return a * b / gcd(a, b);
}

int power (int bas, int exp) {
    int res = 1;
    while (exp) {
        if (exp & 1) (res *= bas) %= MOD;
        (bas *= bas) %= MOD;
        exp >>= 1;
    }
    return res;
}

int inv (int u) {
    return power(u, MOD-2);
}

int nCr(int bas, int exp) {
    if (exp > bas) return 0;
    int res = 1;
    rep  (i,exp) (res *= (bas-i)) %= MOD;
    repa (i,exp) (res *= inv(i) ) %= MOD;
    //ses(bas);ses(exp);see(re);
    return res; 
}

int n, k;
const int C[5] = {1,4,6,4,1};
vector < int > ty;
int dp[25450];
int sum[25450];

int calc() {
    int res = 0; 
    int l = ty.size() - 1; 
    int mul = 1; rep (i,l) ( mul *= C[ ty[i]-ty[i+1] ] ) %= MOD;
    int lc = 1; rep (i,l) lc = lcm(lc, ty[i]);
    memset(dp,0,sizeof(dp)); dp[0] = 1;
    // rep (i,l) repb (j,lc * l,0) repa (k,lc / ty[i] - 1) if (j - ty[i] * k >= 0) (dp[j] += dp[j - k * ty[i]]) %= MOD;
    rep (c,l) {
        rep (i,lc * l + 1) sum[i] = ( dp[i] + ( (i-ty[c] >= 0) ? sum[i-ty[c]] : 0 ) ) % MOD;
        rep (i,lc * l + 1) dp[i] = ( sum[i] - ((i-lc >= 0) ? sum[i - lc] : 0) + MOD ) % MOD;
    }
    int su = 0; rep (i,l) su += ty[i];
    for (int i=(n - 1) % lc + 1; i <= min(n, lc * l); i += lc) if (i >= su) { 
        (res += dp[i - su] * nCr( (n - i) / lc + l - 1 , l - 1) % MOD) %= MOD;
    }

    ty.pop_back();
    return res * mul % MOD;
}

int dfs(int u) {
    ty.push_back(u);
    if (u == 0) return calc();
    int res = 0;
    repa (i,4) if (u - i >= 0) (res += dfs(u - i)) %= MOD;
    ty.pop_back();
    return res;
}

void init() {
    scanf(II,&n,&k);
    if (n == 0 && k == 0) exit(0);
}

void solve() {
    int res = 0; repa (i,k) (res += dfs(i)) %= MOD;
    printf(IN,res);
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
    while (1) {
        init();
        solve();
    }
    return 0;
}
