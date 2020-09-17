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

const int N = 500005;
int n;
int a[N], h[N][3];
int dp[N][3][2]; // dp[i][j][k] represents the max sum of 1 to i-th buildings that obey: the hight of i is h[j], and ? allow the i+1th one to be higher than h[j] (k==1: do ; k==0: do not)
int fr_h[N][3][2], fr_o[N][3][2];

void init() {
    scanf(I,&n);
    repa (i,n) scanf(I,&a[i]);
    h[0][0] = h[0][1] = h[0][2] = a[0] = 0;
    repa (i,n) { h[i][0] = a[i]; h[i][1] = a[i-1]; h[i][2] = a[i+1]; }
    repa (i,n) rep (j,3) checkMin(h[i][j], a[i]);
}

void solve() {
    repa (i,n + 1) rep (j,3) {
        int uh = h[i][j]; // pos h
        {
            // case k == 0: previous one can be higher than this.
            rep (phi,3) {
                int ph = h[i-1][phi];
                if (ph >= uh) { if (checkMax(dp[i][j][0], dp[i-1][phi][0] + uh)) { fr_h[i][j][0] = phi; fr_o[i][j][0] = 0; } }
                                if (checkMax(dp[i][j][0], dp[i-1][phi][1] + uh)) { fr_h[i][j][0] = phi; fr_o[i][j][0] = 1; }
            } 
        }
        {
            // case k == 1: previos one should not be higher than this.
            rep (phi,3) {
                int ph = h[i-1][phi];
                if (ph > uh) continue;
                if (ph == uh) { if (checkMax(dp[i][j][1], dp[i-1][phi][0] + uh)) { fr_h[i][j][1] = phi; fr_o[i][j][1] = 0; } }
                                if (checkMax(dp[i][j][1], dp[i-1][phi][1] + uh)) { fr_h[i][j][1] = phi; fr_o[i][j][1] = 1; }
            } 
        }
    } 
}

int ans[N];
void print() {
    int ph = fr_h[n+1][0][0], po = fr_o[n+1][0][0];
    repb (i,n,1) {
        ans[i] = h[i][ph];
        int _ph = ph, _po = po;
        ph = fr_h[i][_ph][_po]; po = fr_o[i][_ph][_po];
    } 
    repa (i,n) { printf(I,ans[i]); putchar(' '); }
}

#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    print();
    return 0;
}
