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
typedef pair < int , int > pr;
typedef pair < pr  , int > prr;
#define L first
#define R second

string s;

const int N = 300005;
const int MOD = 1e9 + 7;
int fac[N];

void initFac() {
    fac[0] = 1;
    repa (i,N - 1) fac[i] = fac[i - 1] * i % MOD;
}

int power(int bas , int exp , int mod) {
    int res = 1;
    while (exp) {
        if (exp & 1) (res *= bas) %= mod;
        (bas *= bas) %= mod;
        exp >>= 1;
    }
    return res;
}

inline int inv(int u , int mod = MOD) {
    return power(u , mod - 2 , mod);
}

int nCr (int bas , int exp) {
    ses(bas);ses(exp);ses(fac[bas]);ses(inv(fac[bas - exp]));see(inv(fac[exp]));see( fac[bas] * inv(fac[bas - exp]) % MOD * inv(fac[exp]) % MOD);
    return fac[bas] * inv(fac[bas - exp]) % MOD * inv(fac[exp]) % MOD;
}

int cnt[256];

void init() {
    initFac();
    cin >> s;
    rep (i,(int)s.length()) cnt[ (int)s[i] ]++;
}

void solve() {
    int q; scanf(I,&q);
    int n = s.size() / 2;

    int pre = 1;
    int totr = n * 2;
    rep (i,256) {
        if (!cnt[i]) continue;
        (pre *= nCr(totr , cnt[i])) %= MOD;
        totr -= cnt[i]; 
    }
    rep (_,q) {
        int x , y; scanf(II,&x,&y); x-- ; y-- ;
        int cx = s[x] , cy = s[y];
        int cntx = cnt[ (int)s[x] ] , cnty = cnt[ (int)s[y] ];
        if (cx == cy) {
            if (cntx > n) { puts("0"); continue; }
            printf(IN,nCr(n , cntx) * pre % MOD * inv( nCr(n * 2 , cntx) ) % MOD  * 2 % MOD);
        }else {
            if (cntx + cnty > n) { puts("0"); continue; }
            printf(IN,nCr(n , cntx + cnty) * nCr(cntx + cnty , cntx) % MOD * pre % MOD * inv( nCr(n * 2 , cntx) ) % MOD * inv( nCr(n * 2 - cntx , cnty)) % MOD * 2 % MOD);
        }
    }
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    return 0;
}
