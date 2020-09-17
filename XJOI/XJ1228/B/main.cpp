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

const int N = 10005;
int kd[N];
int nu[6];

pr get(int u) {
    if (u == 1) { return pr(0,0); }
    if (u <= 7) { return pr(1,0); }
    int pid = 1;
    int times = 6;
    while (pid + times < u) {pid += times; times += 6; }
    int id = u - pid;
    int pir = times / 6;
    if (id % pir == 0) { 
        int rt = 0; if (pid + times == u) rt = pid + 1;
        return pr( pid - times + 6 + (pir - 1) * (id/pir) , rt ); 
    }
    int msd = id / pir;
    int aid = id - msd;
    int ost = pid - times + 6;
    int rb = ost + aid - 1; if (rb <= ost) rb = 0;
    return pr (ost + aid, rb);
}

void init() {
    kd[0] = 0;
    nu[0] = 0x3f3f3f3f;
    repa (i,10000) {
        pr p = get(i);
        int fa = kd[p.L], fb = kd[p.R];
        int res = 0;
        repa (k,5) {
            if (k == fa || k == fb || k == kd[i - 1]) continue;
            if (nu[k] < nu[res]) res = k;
        }
        kd[i] = res;
        nu[res] ++;
    }    
}

void solve() {
    int T; scanf(I,&T);
    while (T--) {
        int r; scanf(I,&r);
        printf(IN,kd[r]);
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
