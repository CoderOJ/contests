#pragma GCC optimize(2)
#pragma GCC optimize(3)
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

typedef vector < int > Vint;
const int V = 5005;
const int N = 205;
int ov[N], ow[N];
Vint dp[V];
int k , v , n;

void init() {
    scanf(III,&k,&v,&n);
    rep (i,n) scanf(II,&ov[i],&ow[i]);
}

Vint merge (const Vint& a, const Vint& b, int w) {
    Vint res; 
    int ia = 0, ib = 0;
    rep (i,k) {
        if (a[ia] > b[ib]+w) { res.push_back(a[ia]  ); ia++; }
        else                 { res.push_back(b[ib]+w); ib++; }
    }
    res.push_back(-0x3f3f3f3f);
    return res;
}

void solve() {
    rep (i,v+1) { dp[i].resize(k+1, -0x3f3f3f3f); }
    dp[0][0] = 0;
    rep (i,n) repb (j,v,ov[i]) dp[j] = merge(dp[j], dp[j - ov[i]], ow[i]);
    int ans = 0; rep (i,k) ans += dp[v][i];
    // rep (i,k) printf("%d ",dp[v][i]);
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
