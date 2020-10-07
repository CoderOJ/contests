#include <iostream>
#include <cstdio>
using namespace std; 
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

#ifdef ENABLE_LL
#define int long long
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
#define repe(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)

typedef pair < int , int > pr; 
typedef pair < pr  , int > prr; 
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); } 
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); } 
void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } } 
bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }
#define L first
#define R second

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#define ses(a) std::cout << #a << "=" << a << " " 
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#define ses(a)
#endif

#ifndef CUSTOM_MAIN

void preInit();
void init(); 
void solve(); 

int32_t main(){ 
preInit();

#ifdef MULTIPLE_TEST_CASES_WITH_T
int T; 

#ifdef _LIB_SCANNER
T = sc.nextInt();
#else
scanf("%d",&T); 
#endif /* _LIB_SCANNER */

while(T--) {init(); solve();} 
#else

#ifdef MULTIPLE_TEST_CASES_WITHOUT_T 
while(1) {
    try {init(); } 
    catch(bool t) {return 0;} 
    solve();
}
#else
init(); solve(); 
#endif /* MULTIPLE_TEST_CASES_WITHOUT_T  */

#endif /* MULTIPLE_TEST_CASES_WITH_T */
    return 0;
}

#endif /* CUSTOM_MAIN */

// my code begins here



const int N = 90;
const int D = 20;
const int H = D/2;
const int H2 = (1<<H);

bitset <N> e[N][2];
int n,m,d;

void preInit() { } 
void init() {
    scanf(III,&n,&m,&d);
    rep (i,m) { int u,v,w; scanf(III,&u,&v,&w); u--; v--; e[u][w][v]=1; e[v][w][u]=1; }
}

bitset<N> trans( bitset<N> u, int w ) {
    bitset<N> res;
    rep (i,n) if (u[i]) { res |= e[i][w]; }
    return res; }

bitset<N> state1[1024];
bitset<H2> valid[N];

void solve() {
    int h1=d/2, h2=d-h1;
    // sub1
    {
        bitset<N> init; rep (i,n) init[i] = (i==0);
        rep (i, (1<<h1)) {
            bitset<N> &pos = state1[i];
            pos = init;
            rep (j, h1) { pos = trans(pos, (i>>j)&1);  } }
    }
    // sub2
    {
        rep (i,n) { // start point
            rep (j, (1<<h2)) { // transfer mask
                bitset<N> pos;
                rep (k,n) pos[k] = (k==i);
                rep (k,h2) { pos = trans(pos, (j>>k)&1); }
                valid[i][j] = pos.any();  } }
    }
    // merge
    int ans = 0;
    rep (i,(1<<h1)) { // left_half mask
        bitset <H2> va;
        rep (j,n) { // mid point 
            if (state1[i][j]) va |= valid[j]; }
        ans += va.count(); }
    printf(IN,ans);
}
