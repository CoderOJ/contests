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


const int N = 1000005;
int ri[N];
pr p[N];
int wax[N];
int n,m;


void preInit() {

}

void init() {
    scanf(II,&n,&m);
    memset(ri,-1,sizeof(ri));
    rep (i,n) { scanf(II,&p[i].L,&p[i].R); }
    rep (i,m) { int x,y; scanf(II,&x,&y); ri[x] = y; wax[i] = x; }
    repb (i,N-2,0) { checkMax(ri[i], ri[i+1]); }
}

struct Change { int i,x,y; };
vector <Change> ch;
int pans[N];

void solve() {
    rep (i,n) {
        // ch.push_back( {i, 0, max(0,ri[p[i].L] - p[i].R)} );
        pans[i] = max(0,ri[p[i].L] - p[i].R + 1); 
        rep (j,m) { if (wax[j] >= p[i].L) { ch.push_back( {i, wax[j]-p[i].L+1, max(0, ri[wax[j]+1] - p[i].R+1)} ); } } }
    sort(ch.begin(), ch.end(), [](Change a, Change b) { return a.x < b.x; });
    multiset <int> ans; rep (i,n) ans.insert(pans[i]);  
    int Tans = *ans.rbegin();
    for (Change u: ch) {
        int id = u.i, pos = u.x, v = u.y;
        ans.erase( ans.find(pans[id]) ); ans.insert(pans[id] = v);
        checkMin(Tans, pos + *ans.rbegin()); }
    printf(IN,Tans);
}
