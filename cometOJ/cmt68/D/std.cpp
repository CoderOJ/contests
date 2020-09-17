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
class Scanner{ private: istream& ist;public: Scanner(istream& in):ist(in){} string next(){ string r; ist >> r; return r; } string nextLine(){ string r; getline(ist,r); return r; } int nextInt(){ int r; ist >> r; return r; } double nextDouble(){ double r; ist >> r; return r; }};
Scanner sc(cin);

const int N = 100005;
int t[N];
int n, m, k, D;

void init() {
    scanf(IIII,&n,&m,&D,&k);
    rep (i,m) scanf(I,&t[i]); 
    sort (t,t+m);
}

int s[N];

void solve() {
    rep (i,m) s[i] = (i?s[i-1]:0) + t[i];
    int ans = 0;
    rep (i,n + 1) {
        int c = i * (s[m-1]);
        ses(c);
        if (c > k) break;
        if (i == n) {ans = i*(m+D); break; }
        int pans = i * (m + D);
        int r = (k-c) / (n-i);
        ses(r);
        int id = upper_bound(s,s+m,r) - s - 1;
        ses(id);
        pans += (id+1) * (n-i);
        int rr = k - c - (n-i) * (id>=0?s[id]:0);
        see(rr);
        if (id != m-1) pans += rr / (t[id + 1]);
        see(pans);
        checkMax(ans,pans);
    }
    printf(IN,ans);
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
    int T; scanf("%d",&T);
    while (T--) {
        init();
        solve();
    }   
    return 0;
}
