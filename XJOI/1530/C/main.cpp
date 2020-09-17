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

void init();
void solve();
int main(){
try { 

#ifndef CUSTOM_MAIN
#ifdef MULTIPLE_TEST_CASES_WITH_T

int T; scanf("%d",&T); while(T--) {init(); solve();}

#else
#ifdef MULTIPLE_TEST_CASES_WITHOUT_T

while(1) {try{init(); } catch(bool t){return 0;} solve(); }

#else

init(); solve();

#endif
#endif
#endif

} catch (const char* s) { return 0; }
    return 0;
}

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
typedef pair < int , int > pr; typedef pair < pr  , int > prr;
#define L first
#define R second
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); }
class Scanner{ private: istream& ist;public: Scanner(istream& in):ist(in){} string next(){ string r; ist >> r; return r; } string nextLine(){ string r; getline(ist,r); return r; } int nextInt(){ int r; ist >> r; return r; } double nextDouble(){ double r; ist >> r; return r; } char nextChar(){ char r; ist>>r; return r;} }; Scanner sc(cin);
void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } }
bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }

const int N = 200005;
vector <int> e[N]; int n,m, c[N], t[N],a[N];
void init() {
    scanf(II,&n,&m);  
    repa (i,n) scanf(I,&c[i]);
    rep (i,n-1) {int u,v; scanf(II,&u,&v); e[u].push_back(v); e[v].push_back(u); }
    rep (i,m) scanf(II,&t[i],&a[i]);
}

namespace no1{
    bool check() { rep (i,m) if (t[i]==1) return 0; return 1; }
    void main() { rep (i,n) puts("0"); }
}

namespace Common {
    int fa[N]; long long w[N], s[N];

    void dfs(int u, int f) {
        fa[u] = f; s[u] = c[u]*u;
        for (int v: e[u]) {
            if (v==f) continue;
            dfs(v,u); s[u]+=s[v]; } }

    void revert(int u) {
        int cc = c[u] ? -u : u; c[u]^=1;
        while (u!=0) { s[u] += cc; u=fa[u]; } }

    void operate(int u) {
        w[u] += s[u]; int times=0;
        while (fa[u]!=0) { times++; w[fa[u]] += s[fa[u]]-s[u]; u=fa[u]; }  }

    void main() {
        dfs(1,0);  
        rep (i,m) {
            if (t[i]==1) operate(a[i]);
            else revert(a[i]); }
        repa (i,n) printf("%lld\n",w[i]); }
}

void solve() {
    if (no1::check()) no1::main();
    else Common::main();
}

