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

const int M = 2005;
int dp[M];
vector < int > k1a , k1b , k2a , k2b , k3a , k3b;
int n , m;
int mx1[M];
int n1, n2, n3;

void init() {
    scanf(II,&n,&m);
    rep (i,n) {
        int opt; scanf(I,&opt);
        if (opt == 1) {
            int a , b; scanf(II,&a,&b);
            k1a.push_back(a); k1b.push_back(b);
        }else if (opt == 2) {
            int a , b , c; scanf(III,&a,&b,&c);
            rep (_,c) { k2a.push_back(a); k2b.push_back(b); }
        }else {
            int a , b;scanf(II,&a, &b);
            k3a.push_back(a); k3b.push_back(b);
        }
    }
    n1 = k1a.size(); n2 = k2a.size(); n3 = k3a.size();
    rep (i,n1) repa (j,m) checkMax( mx1[j], k1a[i] * j * j - k1b[i] * j);
}

void solve() {
    rep (i,n3) repi (j,k3b[i],m) checkMax(dp[j] , dp[j - k3b[i]] + k3a[i]);
    rep (i,n2) repb (j,m,k2b[i]) checkMax(dp[j] , dp[j - k2b[i]] + k2a[i]);
    rep (i,m) checkMax(dp[m], dp[i] + mx1[m - i]);
    printf(IN,dp[m]);
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    return 0;
}
