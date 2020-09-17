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

const int N = 400005;
const int INF = 0x3f3f3f3f3f3f3f3f;
int n, p;
int t[N];
int a[N];

struct STree {
    int v[N];

    void pushUp(int u) {
        v[u] = min(v[u+u], v[u+u+1]);
    }

    void modify(int l, int r, int w, int uv, int u = 1) {
        if (l == r) { v[u] = uv; return; }
        int m = (l+r) / 2;
        if (w <= m) modify(l, m, w, uv, u+u);
        else        modify(m+1, r, w, uv, u+u+1);
        pushUp(u);
    }

    int queryMin() {
        return v[1];
    }

    int queryFirst (int l, int r, int threshold, int u=1) {
        if (l == r) return l;
        int m = (l+r) / 2;
        if (v[u+u] <= threshold) return queryFirst(l, m, threshold, u+u);
        else                     return queryFirst(m+1,r,threshold, u+u+1);
    }    
};

STree st;

void init() {
    scanf(II,&n,&p);
    rep (i,n) scanf(I,&t[i]);
}

void solve() {
    rep (i,n) st.modify(0,n-1,i,t[i]);
    int re = 0;
    rep (i,n) {
        re = max(re, st.queryMin());
        int ps = st.queryFirst (0, n-1, re);
        re += p;
        a[ps] = re;
        st.modify(0, n-1, ps, INF);
    } 
    rep (i,n) printf("%lld ",a[i]);
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    return 0;
}
