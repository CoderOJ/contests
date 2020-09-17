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

const int N = 300005;
int a[N];
int n;

void init() {
    scanf(I,&n);
    rep (i,n) scanf(I,&a[i]);
    reverse(a,a+n);
}

int dp[N][2][2];

inline int get(int i, int a, int b, int c, int d) {
    return  max( max(dp[i][0][0]+a,dp[i][0][1]+b) , max(dp[i][1][0]+c,dp[i][1][1]+d) ) ;
}

void solve() {
    dp[0][0][0] = 1;
    rep (i,n) {
        if (a[i] % 2 == 0) {
            a[i+1][0][0] = get(i,0,0,0,0) + a[i]/2;
            a[i+1][1][0] = get(i,0,1,0,1) + a[i]/2 - 1;
            a[i+1][0][1] = get(i,0,0,1,1) + a[i]/2 - 1;
            a[i+1][1][1] = get(i,0,0,0,0) + a[i]/2 - 1;
        } else {
            a[i+1][0][0] = get(i,0,0,1,1) + a[i]/2;
            a[i+1][1][0] = get(i,0,0,0,0) + a[i]/2;
        }
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
