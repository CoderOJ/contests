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

const int N = 300005;
const int M = 1000005;
vector < int > e[N];
pr ed[M];
int eid[M] , vid[N];
int ind[N] , cst[M];
int n , m;

void init() {
    scanf(II,&n,&m);
    rep (i,3 * n + 5) ind[i] = 0;
    rep (i,3 * n + 5) e[i].clear();
    repa (i,m) {
        int u , v; scanf(II,&u,&v);
        ind[u]++; ind[v]++;
        e[u].push_back(v); e[v].push_back(u);
        ed[i] = pr(u,v);
    }
    repa (i,m) cst[i] = ind[ ed[i].L ] + ind[ ed[i].R ];
}

bool solve1() {
    repa (i,n * 3) vid[i] = i;
    sort(vid + 1 , vid + n * 3 + 1 , [](int x , int y){ return ind[x] < ind[y]; });
    vector < int > ans;
    set < int > ignore;
    repa (_i,n * 3) {
        int i = vid[_i];
        if (ignore.count(i)) continue;
        ans.push_back(i);
        foreach(__i,e[i]) ignore.insert(e[i][__i]);
    }
    int sz = ans.size();
    if (sz >= n) {
        puts("IndSet");
        rep (i,n) { printf(I,ans[i]); putchar(' '); }
        puts("");
        return 1;
    }
    return 0;
}

bool solve2() {
    repa (i,m) eid[i] = i;
    sort(eid + 1 , eid + m + 1 , [](int x , int y){ return cst[x] < cst[y]; });
    vector < int > ans;
    set < int > ignore;
    repa (_i,m) {
        int i = eid[_i];
        if (ignore.count( ed[i].L ) || ignore.count( ed[i].R )) continue;
        ans.push_back(i);
        ignore.insert( ed[i].L );
        ignore.insert( ed[i].R );
    }
    int sz = ans.size();
    if (sz >= n) {
       puts("Matching");
       rep (i,n) { printf(I,ans[i]); putchar(' '); }
       puts("");
       return 1;
    }
    return 0;
}

#ifdef ENABLE_LL
#undef int
#endif
int main(){
    int T; scanf(I,&T);
    while (T--) {
        init();
        if (solve2()) continue;
        if (solve1()) continue;
        puts("Impossible");
    }
    return 0;
}
