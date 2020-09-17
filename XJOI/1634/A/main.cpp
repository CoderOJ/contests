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

} catch (...) { return 0; }
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

const int N = 100005;

struct Dsu {
    int p[N], s[N];
    Dsu () { 
        rep (i,N) { p[i]=i; s[i]=1; } }
    int get(int u) { return u == p[u] ? u : p[u] = get(p[u]); }
    void merge(int u, int v) {
        int pu=get(u), pv=get(v);
        if (pu == pv) return;
        s[pu] += s[pv]; p[pv] = pu; }
    int size(int u) { return s[get(u)]; }
};

struct Query { int k,v,id; };
struct Edge { int u,v,w; };
Query qs[N];
Edge e[N];
int ans[N];
Dsu st;
int n, q;

void init() {
    scanf(II,&n,&q); 
    rep (i,n-1) { int u,v,w; scanf(III,&u,&v,&w); e[i] = {u,v,w}; }
    rep (i,q) { int k,v; scanf(II,&k,&v); qs[i] = {k,v,i}; }
    sort(e,e+n-1, [](Edge a, Edge b) { return a.w > b.w; });
    sort(qs,qs+q, [](Query a,Query b) { return a.k > b.k; });
}

void solve() {
    int eCnt=0;
    rep (i,q) {
        while (eCnt < n-1 && qs[i].k <= e[eCnt].w) { st.merge(e[eCnt].u,e[eCnt].v); eCnt++; }
        ans[ qs[i].id ] = st.size(qs[i].v); }
    rep (i,q) printf(IN,ans[i]-1);
}

