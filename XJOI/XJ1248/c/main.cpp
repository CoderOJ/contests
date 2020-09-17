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
class Scanner{ private: istream& ist;public: Scanner(istream& in):ist(in){} string next(){ string r; ist >> r; return r; } string nextLine(){ string r; getline(ist,r); return r; } int nextInt(){ int r; ist >> r; return r; } double nextDouble(){ double r; ist >> r; return r; }};
Scanner sc(cin);

const int N = 100005;
const int MOD = 998244353;
int a[N];
int s[N];
int n, k;

int power(int bas, int exp) {
    int res = 1;
    while (exp) {
        if (exp & 1) (res *= bas) %= MOD;
        (bas *= bas) %= MOD;
        exp >>= 1;
    }
    return res;
}

inline int inv(int u) {
    return power(u, MOD-2);
}

int fac[N];
void init_fac() {
    fac[0] = 1;
    repa (i,N-1) fac[i] = fac[i-1] * i % MOD;
}

inline int nCr(int n, int r) {
    return fac[n] * inv( fac[r] ) % MOD * inv( fac[n-r] ) % MOD;
}

void init() {
    init_fac();
}

inline int prop(int u, int t) {
    ses(t-1);ses(k);ses(u);see(power(t-1,k-u));
    int res = nCr(k,u) % MOD * power(t-1,k-u) % MOD * inv( pow(t,k) ) % MOD;
    see(res);
    return res;
}

void solve() {
    scanf(II,&n,&k);
    a[0] = s[0] = 1;
    repa (i,n-1) {
        int p = 0;
        repa (j,k) (p += j * prop(j,i)) %= MOD;
        see(p);
        a[i] = (s[i-1] * p) % MOD;
        s[i] = (s[i-1] + a[i]) % MOD;
    }
    int ans = 0;
    rep (i,n) rep (j,n) (ans += (a[i] + a[j]) * (a[i] + a[j])) %= MOD;
    (ans *= inv(n*n)) %= MOD;
    printf(IN,ans);
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    return 0;
}
