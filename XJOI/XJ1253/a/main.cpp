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
int _f[2*N], *f=_f+N;
int n;

void init() {
    memset(a,0,sizeof(a));
    memset(_f,0,sizeof(_f));
    scanf(I,&n);
    rep (i,n) scanf(I,&a[i]);
    sort(a, a+n);
}

int solve() {
    if (n>=31) return 0;
    if (n == 1) return a[0];
    int s = 0; f[0] = 1;
    rep (i,n) {
        if (f[ a[i] ]) return 0;
        repi (j,-s,s) f[j-a[i]] |= f[j];
        repb (j,s,-s) f[j+a[i]] |= f[j];
        s += a[i];
    }  
    int ans = a[n-1];
    do {
        int lp = 1<<(n-1);
        for (int i=0;i<lp;i++) {
            int res = a[0];
            repa (j,n-1) {
                int u = i & (1<<(j-1));
                if (u) res = abs(res - a[j]);
                else {
                    res *= a[j];
                    if (res >= N) break;
                }
            }
            checkMin(ans,res);
        } 
    } while(next_permutation(a, a+n));
    return ans;
}

#ifdef ENABLE_LL
#undef int
#endif
int main(){
    int T; scanf(I,&T);
    while (T--) {
        init();
        printf(IN,solve());
    }
    return 0;
}
