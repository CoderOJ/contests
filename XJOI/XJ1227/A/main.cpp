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

int slope (pr o, pr a, pr b) {
    int x  = o.L, y  = o.R;
    int ax = a.L, ay = a.R;
    int bx = b.L, by = b.R;
    int dax = ax - x, day = ay - y;
    int dbx = bx - x, dby = by - y;
    return dax * dby - dbx * day;
}
 
const int N = 300005;
int a[N];
int n, q;
vector < pr > sh;

void init() {
    scanf(II,&n,&q);
    rep (i,n) scanf(I,&a[i]);
    sh.push_back( pr(0,a[0]) );
    if (n > 1) sh.push_back( pr(1,a[1]) );
    repi (i,2,n-1) {
        pr pos = pr(i,a[i]);
        int s = sh.size();
        while (s >= 2 && slope( sh[s-2], sh[s-1], pos) <= 0) {
            sh.pop_back(); s--; }
        sh.push_back( pos );
    }
    rep (i,(int)sh.size()) see(sh[i].L);
}

double sl[N];

void solve() {
    int s = sh.size();
    rep (i,s-1) sl[i] = (sh[i + 1].R - sh[i].R) * (double)(1.0) / (sh[i + 1].L - sh[i].L);
    rep (_,q) {
        int slp; scanf(I,&slp);
        int id = lower_bound(sl,sl+s-1,(double)(-slp)) - sl;
        printf(IN, a[ sh[ id ].L ] + slp * sh[id].L + slp);
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
