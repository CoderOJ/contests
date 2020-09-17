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

const int N = 255;
int c[N];
int u[N], v[N], w[N];
int t[N], x[N], y[N]; 
int n,m,T,k;

void init() {
    scanf(IIII,&n,&m,&T,&k);
    repa (i,n) scanf(I,&c[i]); 
    rep (i,m) scanf(III,&u[i],&v[i],&w[i]);
    rep (i,k) scanf(III,&t[i],&x[i],&y[i]); 
}

namespace Circ {
    bool jury() {
        if (n!=m) return 0;
        rep (i,m) if (v[i] != u[i]%n+1) return 0;
        return 1; }
    int tt[N];
    void main() {
        int sumW=0; rep (i,m) sumW+=w[i]; 
        if (T%sumW!=0) { puts("-1"); return; }
        tt[1]=0; repi (i,2,n) tt[i] = tt[i-1] + w[i-2];
        int ans=0; repa (i,n) ans+=c[i]; 
        ans *= (T/sumW);
        rep (i,k) {
            if (t[i] > T) continue;
            if (t[i] < tt[x[i]]) continue;
            if ( (t[i]-tt[x[i]]) % sumW != 0 ) continue;
            ans += y[i]; }
        printf(IN,ans+c[1]); }
}

namespace Bf {
    bool jury() {
        return T <= 52501; }

    const int TT = 52505;
    int dp[TT][N];
    vector <pr> fr[N];

    void main() {
        rep (i,m) fr[ v[i] ].push_back( (pr){u[i],w[i]} );
        memset(dp,-1,sizeof(dp)); dp[0][1] = c[1];
        repa (i,T) {
            repa (u,n) for (pr v:fr[u]) {
                int p = i-v.R;
                if (p < 0) continue;
                if (dp[p][v.L]==-1) continue;
                checkMax(dp[i][u], dp[p][v.L]+c[u]); }
            rep (j,k) {
                if (t[j]==i) {
                    if (dp[i][x[j]] == -1) continue;
                    dp[i][x[j]] += y[j]; } } }
        printf(IN,dp[T][1]); }
}

namespace Ran {
    void main() {
        puts("-1"); }
}

void solve() {
    if (Circ::jury()) Circ::main();
    else if (Bf::jury()) Bf::main();
    else Ran::main();
}

