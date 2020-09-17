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

const int N = 100005;
vector <int> e[N]; int n, m;
int sz[N], k[N];

void init() {
    scanf(II,&n,&m);
    rep (i,m) {
        int u, v; scanf(II,&u,&v);
        e[u].push_back(v); e[v].push_back(u); }
}

int S, T;
void dfs1(int u, int f) {
    sz[u]=-sz[f];
    for (int v: e[u]) {
        if (v==f) continue;
        if (sz[v]!=0) { S=u; T=v; }
        else dfs1(v,u); } }
void dfs2(int u, int f) {
    ses(u);see(f);
    for (int v:e[u]) {
        if (v==f || (S==v&&T==u) || (S==u&&T==v)) continue;
        dfs2(v,u); k[u]+=k[v]; sz[u]+=sz[v]; } }

void solve() {
    sz[0]=-1; dfs1(1,0);
    int ans=0;

    // judge -1 verdict
    int sum=0; repa (i,n) sum+=sz[i];
    if (m==n-1) { ALERT(sum!=0,"-1"); }
    else {
        if (sz[S]==sz[T]) { // odd circle
            ALERT(sum&1, "-1");
            ans += abs(sum/2); sz[S]-=sum/2; sz[T]-=sum/2; }
        else { //even circle
            ALERT(sum!=0, "-1");
            k[S]=1; k[T]=-1; /* set k in the path from S to T  */ } }
    dfs2(1,0);
    vector <int> st; st.push_back(0);
    repa (i,n) {
        if (k[i]!=0) st.push_back(k[i]*sz[i]); 
        else ans+=abs(sz[i]); }
    sort(st.begin(),st.end()); 
    int m=st[st.size()/2];
    for (int i: st) ans+= abs(i-m);
    printf(IN,ans);
}

