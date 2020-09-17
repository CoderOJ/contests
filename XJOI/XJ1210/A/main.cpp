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

const double eps = 1e-8;
typedef pair < double , double > Node;
const int N = 100005;
Node w[N];
double a , b , d;
int n;
double dis[N];

inline double getDis(Node x) {
    return (x.L * a + x.R * b) / sqrt(a * a + b * b);
}

void init() {
    scanf("%lf%lf%lf",&a,&b,&d); scanf(I,&n);
    rep (i,n) scanf("%lf%lf",&w[i].L,&w[i].R);
    rep (i,n) dis[i] = getDis(w[i]);
    rep (i,n) see(dis[i]);
}

void solve() {
    sort(dis , dis + n);
    int ans = 0;
    rep (i,n) ans = max(ans , (int)(upper_bound(dis , dis + n , dis[i] + d * 2 + eps) - dis) - i);
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
