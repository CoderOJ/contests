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
#define repe(a,b) for (int a=0;a<(int)b.size();a++)
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

const int N = 1000005;
int s[N];
int n, d;

int su[N], fsu[N];

void init() {
    scanf(II,&n,&d);
    rep (i,n) scanf(I,&s[i]);
    su[0] = fsu[0] = s[0];
    repa (i,n-1) {
        su[i] = (su[i-1] + s[i]) % MOD;
        fsu[i] = (su[i-1] + s[i] * (i+1)) % MOD;
    } 
}

inline int inc(int s, int l) {
    if (s == 0) return fsu[l-1];
    return ( fsu[s+l-1] - fsu[s-1] - (su[s+l-1] - su[s-1]) * s + MOD*5 ) % MOD;
}

inline int dec(int s, int l) {
    return ( (su[s+l-1] - su[s-1]) * (s+2) - inc(s,l) + MOD*2) % MOD;
}

void solve() {
    int p=0, ans=0;
    checkMin(d, n/2);
    rep (i,d) (p += s[i] * (d-i-1) * (d-i-1)) %= MOD;

}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    return 0;
}
