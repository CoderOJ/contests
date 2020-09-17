#pragma GCC optimize(4)
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
#include <bitset>
#include <sstream>
using namespace std;
 
#ifndef CUSTOM_MAIN
void init();
void solve();
int main(){
try {
 
#ifdef MULTIPLE_TEST_CASES_WITH_T
 
int T; scanf("%d",&T); while(T--) {init(); solve();}
 
#else
#ifdef MULTIPLE_TEST_CASES_WITHOUT_T
 
while(1) {try{init(); } catch(bool t){return 0;} solve(); }
 
#else
 
init(); solve();
 
#endif
#endif
 
} catch (const char* s) { return 0; }
    return 0;
}
#endif
 
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
 
const int N = 3005;
 
struct Dep {
    vector <int> a;
    int n;
 
    Dep () {
        n=1; a.resize(n); }
     
    Dep shift(int del) {
        Dep res;
        res.n = n+del; res.a.resize(res.n);
        rep (i,n) {
            res.a[i+del]= a[i]; }
        return res; }
 
    void add(Dep v) {
        checkMax(n,v.n); a.resize(n);
        int sz=min(n,v.n);
        rep (i,sz) a[i] += v.a[i]; }
    void sub(Dep v) {
        checkMax(n,v.n); a.resize(n);
        int sz=min(n,v.n);
        rep (i,sz) a[i] -= v.a[i]; }
 
    void log() { }
};
 
vector <int> e[N];
Dep dep[N];
int fa[N][20];
int d[N];
int n,p,q;
 
void dfs(int u, int f) {
    fa[u][0]=f;
    rep (i,19) fa[u][i+1] = fa[ fa[u][i] ][i];
    d[u] = d[f]+1;
    dep[u].a[0]=1;
    for (int v: e[u]) {
        if (v==f) continue;
        dfs(v,u);
        dep[u].add( dep[v].shift(1) ); }
}
 
bool isAnc(int u, int v) {
    if (d[u] < d[v]) swap(u,v);
    int del=d[u] - d[v];
    repb (i,19,0) { if (del >= (1<<i)) { u=fa[u][i]; del-=(1<<i); } }
    return u==v; }
 
void init() {
    scanf(III,&n,&p,&q);
    rep (i,n-1) { int u,v; scanf(II,&u,&v); e[u].push_back(v); e[v].push_back(u); }
    dfs(1,0);
    repa (i,n) { dep[i].log(); }
}
 
int _get(int u, int c) {
    int res=0;
    int mx=dep[u].n-1;
    if (mx*2 < c) return 0;
    int l=max(0,c-mx), r=min(mx,c);
    repi (i,l,r) {
        if (i!=c-i) {
            res += dep[u].a[i]*dep[u].a[c-i]; }
        else {
            res += (dep[u].a[i]-1) * dep[u].a[i]; } }
    return res/2; }
 
int get(int u, int c) {
    int res=_get(u,c);
    if (c>=2) { for (int v: e[u]) if (v != fa[u][0]) res -= _get(v,c-2); }
    return res; }

namespace Line {
    bool jury () {
        repa (i,n) if (e[i].size() > 2) return 0;
        return 1; }
    void main () {
        int x=n-p-q;
        if (x <= 2) { puts("0"); }
        else { printf(IN, x*(x-1)*4); }
        exit(0); }
}
 
void solve() {
    if (Line::jury()) Line::main();
    long long ans=0;
    repa (u,n) repa (v,n) {
        if (u==v) continue;
        bool isA = isAnc(u,v);
 
        if (isA) {
            int curu=u, curv=v;
            int curp=p, curq=q;
            if (d[curu] > d[curv]) {
                swap (curu, curv);
                swap(curp,curq); }
            int del= d[curv]-d[curu];
 
            Dep curu_bak=dep[curu];
            Dep curvv_bak;
            int curvv=curu;
 
            dep[curu].sub( dep[curv].shift(del) );
            for (int vv: e[curu]) {
                if (vv==fa[curu][0]) continue;
                if (!isAnc(curv,vv)) continue;
                curvv_bak = dep[vv];
                curvv=vv;
                dep[vv].sub( dep[curv].shift(del-1) );
                break; }
 
            int ga = get(curu,curp);
 
            dep[curu] = curu_bak;
            dep[curvv] = curvv_bak;
 
            int gb = get(curv,curq);
            ans += ga * gb; }
        else {
            ans += get(u,p)*get(v,q); }
    }
    printf("%lld\n", ans*4);
}
