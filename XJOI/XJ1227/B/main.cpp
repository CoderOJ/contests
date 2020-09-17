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

#define int double
#define I "%lf"
#define II "%lf%lf"
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
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)
typedef pair < int , int > pr;
typedef pair < pr  , int > prr;
#define L first
#define R second

const long long N = 300005;
int a[4][N];
int n , m;
int q[4];

void init() {
    scanf(II,&n,&m);
    rep (i,n) rep (_,4) scanf(I,&a[(int)_][i]);
}

void solve() {
    rep (i,m) {
        rep (_,4) scanf(I,&q[_]);
        int ans = 0;
        rep (i,n) {
            int b = 0; rep (_,4) if (q[_] > a[_][i]) {b = 1; break; }
            ans += !b;
        }
        printf(IN,ans);
    }
}


#undef int
int main(){
    init();
    solve();
    return 0;
}
