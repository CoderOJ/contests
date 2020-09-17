#define ENABLE_LL
#pragma GCC optimize(3)
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

template <class T> void read(T &u)
{
    u=0; char c=getchar(); int flag=0;
    while (c<'0'||c>'9') flag|=(c=='-'),c=getchar();
    while (c>='0'&&c<='9') u=(u<<3)+(u<<1)+(c^48),c=getchar();
    if (flag) u=-u;
}
const int N = 500005;
const int B = 20;
vector < int > e[N];
int a[N];
int n;

void init() {
    n = sc.nextInt();
    repa (i,n) read(a[i]);
    rep (i,n-1) {
        int u, v; read(u); read(v);
        e[u].push_back(v);
        e[v].push_back(u);
    } 
}

int dep[N];
int fa[N][B];
void dfs(int u, int f) {
    dep[u] = dep[f] + 1;
    fa[u][0] = f;
    repa (i,B-1) fa[u][i] = fa[ fa[u][i-1] ][ i-1 ];
    foreach(i,e[u]) {
        int v = e[u][i];
        if (v == f) continue;
        dfs(v,u);
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int dd = dep[u] - dep[v];
    rep (b,B) if ( (dd>>b) & 1 ) u = fa[u][b];
    repb (b,B-1,0) if (fa[u][b] != fa[v][b]) { u = fa[u][b]; v = fa[v][b]; }
    return u == v ? u : fa[u][0];
}

int calc(int u, int v) {
    int g = lca(u,v);
    int db = dep[u] + dep[v] - dep[g] * 2;
    int da = 0;
    int ans = 0;
    while (u != g) {
        ans += a[u] | da;
        u = fa[u][0];
        da++;
    }
    ans += a[g] | da;
    while (v != g) {
        ans += a[v] | db;
        v = fa[v][0];
        db--;
    }
    return ans;
}

void solve() {
    dfs(1,0);
    int q = sc.nextInt();
    rep (i,q) {
        int u, v; scanf(II,&u,&v);
        printf(IN,calc(u,v));
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
