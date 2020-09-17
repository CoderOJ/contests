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

int power (int bas , int exp , int mod) {
    int res = 1;
    while (exp) {
        if (exp & 1) (res *= bas) %= mod;
        (bas *= bas) %= mod;
        exp >>= 1;
    }
    return res;
}

int inv(int u , int m) {
    return power(u , m - 2 , m);
}

const int N = 35;
const int MOD = 1e9 + 7;
int a[N];
int n , p , c;

void init() {
    scanf(III,&n,&p,&c);
    rep (i,n) scanf(I,&a[i]);
}

void calc(vector < int > & v , int* b , int* e) {
    v.push_back(1);
    while (b != e) {
        int len = (int)v.size();
        rep (i,len) v.push_back( v[i] * (*b) % p) ;
        b++;
    }
    sort(v.begin() , v.end());
}

void solve() {
    if (c > p) {
        puts("0");
        return ;
    }
    vector < int > qa , qb;
    calc(qa , a , a + n / 2); calc(qb , a + n / 2 , a + n);
    int ans = 0;
    foreach (i,qa) {
        int u = qa[i];
        int g = c * inv(u , p) % p ;
        ses(u);ses(inv(u,p));see(g);
        (ans += upper_bound(qb.begin() , qb.end() , g) - lower_bound(qb.begin() , qb.end() , g)) %= MOD;
    }
    printf(IN,(ans - (int)(c == 1) + MOD) % MOD);
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    return 0;
}
