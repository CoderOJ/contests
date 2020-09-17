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

const int MOD = 1e9 + 7;
const int N = 200005;
int x[N]; 

inline int getValue(int a, int b) {
    int m = max(a,b);
    int c = abs(a-b);
    if (a < b) return x[m] + ( (m & 1) ? (-c) : (c) );
    else       return x[m] - ( (m & 1) ? (-c) : (c) );
}

inline pr getPos(int u) {
    int pos;
    for (pos=0;pos<N;pos++) if (x[pos] - pos <= u && u <= x[pos] + pos) break;
    bool greater = (u > x[pos]);
    int a = pos, b = pos;
    ((greater ^ (pos & 1)) ? a : b) -= abs(u - x[pos]);
    return pr(a,b);
}

void init() {
    x[0] = 1; repa (i,N - 1) x[i] += x[i - 1] + i * 2;
}

inline int calc (int a, int b, int k, int t1, int t2)  {
    return ( k * a % MOD * b % MOD +
             (a * t2 + b * t1 + MOD) % MOD * ( k*(k-1)/2 ) % MOD +
             t1 * t2 * ( (k-1) * k * (2*k-1) / 6 ) % MOD ) % MOD;
}

void solve() {
    int n; scanf(I,&n);
    pr pos = getPos(n); 
    int x = pos.L, y = pos.R;
    ses(x);see(y);
    int r = 0, c = 0;
    int ans = (x+1) * (y+1) % MOD;
    while (r < x || c < y) {
        ses(r);ses(c);ses(x);see(y);
        if (r < x) {
            r++; int a = getValue(r,c), b = y - c + 1;
            (ans += calc( a, b, c+1, (r&1) ? 1:-1, 1) * (x-r+1) % MOD) %= MOD;
        }
        see(ans);
        ses(r);ses(c);ses(x);see(y);
        if (c < y) {
            c++; int a = getValue(r,c), b = x - r + 1;
            ses(a);ses(b);see(r+1);
            (ans += calc( a, b, r+1, (c&1) ? -1:1, 1) * (y-c+1) % MOD) %= MOD;
        }
        see(ans);
    }
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
