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
const int MOD1 = 945386291;
const int MOD2 = 945386251;

int power(int a, int b, int MOD) {
    int r=1; a%=MOD;
    while (b) { 
        if (b&1) (r*=a)%=MOD;
        (a*=a)%=MOD; b>>=1; }
   return r; } 
int inv(int u, int MOD) { return power(u,MOD-2,MOD); }

vector <pair<int,pr>> e[N]; int n, m;
int len1[N], len2[N];

void init() {
    scanf(II,&n,&m);
    rep (i,m) {
        int u, v, w; scanf(III,&u,&v,&w);
        e[u].push_back( {v,pr(w,w)} ); e[v].push_back( {u,pr(inv(w,MOD1), inv(w,MOD2))} ); } 
}

int vis[N];
void dfs(int u, int f) {
    vis[u]=1;
    for (auto p: e[u]) {
        int v=p.L, w1=p.R.L, w2=p.R.R; w1%=MOD1; w2%=MOD2;  
        if (v==f) continue;
        if (vis[v]) {
            int l1 = w1*len1[u]%MOD1*inv(len1[v],MOD1)%MOD1;
            int l2 = w2*len2[u]%MOD2*inv(len2[v],MOD2)%MOD2;
            ALERT(l1 != 1 || l2 != 1, "No"); }
        else {
            len1[v] = len1[u]*w1%MOD1; 
            len2[v] = len2[u]*w2%MOD2;
            dfs(v,u); } } }

void solve() {
    repa (i,n) if (!vis[i]) { len1[i] = len2[i] = 1; dfs(i,0); }
    puts("Yes");
}

