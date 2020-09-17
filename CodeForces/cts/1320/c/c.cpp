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
int n, m, p;
int a[N], ca[N];
int b[N], cb[N];
int x[N], y[N], k[N];
vector < int > lsa, lsb;

struct Tree {
    int a[N];


} tr;

void init() {
    scanf(III,&n,&m,&p);
    rep (i,n) scanf(II,&a[i],&ca[i]);
    rep (i,m) scanf(II,&b[i],&cb[i]);
    rep (i,p) scanf(III,&x[i],&y[i],&k[i]);
    rep (i,n) lsa.push_back(a[i]); rep (i,p) lsa.push_back(x[i]); sort (lsa.begin(), lsa.end()); lsa.remove( unique(lsa.begin(),lsa.end()), lsa.end());
    rep (i,m) lsb.push_back(b[i]); rep (i,p) lsb.push_back(y[i]); sort (lsb.begin(), lsb.end()); lsb.remove( unique(lsb.begin(),lsb.end()), lsb.end());
    rep (i,n) a[i] = lower_bound(lsa.begin(), lsa.end()) - lsa.begin() + 1;
    rep (i,p) x[i] = lower_bound(lsa.begin(), lsa.end()) - lsa.begin() + 1;
    rep (i,m) b[i] = lower_bound(lsb.begin(), lsb.end()) - lsb.begin() + 1;
    rep (i,p) y[i] = lower_bound(lsb.begin(), lsb.end()) - lsb.begin() + 1;
}

vector < pr > bs;

void solve() {
    rep (i,m) bs.push_back( pr(b[i], cb[i]) ); sort(bs.begin(), bs.end()); rep (i,m) { b[i] = bs[i].L; cb[i] = bs[i].R; }
    repa (i,m-1) cb[i] -= cb[i-1];

}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    return 0;
}
