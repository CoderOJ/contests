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

struct State {
    int t;
    long double s, q;
    
    State (int t=0) : t(t) { s=q=0; }
    State add(int d) {
        State res = *this;
        res.q += res.t * (d*d) + 2*res.s*d;
        res.s += res.t*d;
        return res;
    }
    State merge(State v) {
        State res = *this;
        res.t += v.t;
        res.s += v.s;
        res.q += v.q;
        return res;
    }
    State separate (State v) {
        State res = *this;
        res.t -= v.t;
        res.s -= v.s;
        res.q -= v.q;
        return res;
    }
};

const int N = 200005;
vector < pr > e[N];
int n;
int c[N];

State sub[N];

State dfs0(int u, int f) {
    State res(c[u]);
    repe (i,e[u]) {
        int v=e[u][i].L, w=e[u][i].R;
        if (v == f) continue;
        State sv = dfs0(v, u);
        res = res.merge(sv.add(w));
    }
    return sub[u] = res;
}

void init() {
    scanf(I,&n);
    repa (i,n) scanf(I,&c[i]);
    rep (i,n-1) {
        int u, v, w; scanf(III,&u,&v,&w);
        e[u].push_back( pr(v,w) );
        e[v].push_back( pr(u,w) );
    }
    dfs0(1,0);
}

State ans[N];

void dfs1(int u, int f, State up) {
    ans[u] = up.merge( sub[u] );
    repe (i,e[u]) {
        int v = e[u][i].L, w=e[u][i].R;
        if (v == f) continue;
        State vp = ans[u].separate( sub[v].add(w) ).add(w);
        dfs1(v,u,vp);
    }
}

void solve() {
    dfs1(1,0,State(0));
    long double res = ans[1].q;
    repi (i,2,n) checkMin(res, ans[i].q);
    printf("%.5Lf",res);
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
#ifndef __LOCALE__
freopen("problem3.in","r",stdin);
freopen("problem3.out","w",stdout);
#endif
    init();
    solve();
    return 0;
}
