#define MULTIPLE_TEST_CASES_WITH_T
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


const int N = 100005;
const double eps = 1e-8;
int a[N];
int g_n,g_l;


void preInit() {

}

void init() {
    scanf(II,&g_n,&g_l);
    repa (i,g_n) { scanf(I,&a[i]); } a[0]=0; a[g_n+1]=g_l;
}

double aRun(double time) {
    int speed=1; int i = 0;
    double res = 0;
    while (i<=g_n && time > eps) {
        double dis = a[i+1] - a[i]; double cost = dis / speed;
        double go = min(cost,time); res += go*speed; time -= go; speed++; i++; }
    return res; }

double bRun(double time) {
    int speed=1; int i=g_n+1;
    double res = 0;
    while (i>=1 && time > eps) {
        double dis = a[i] - a[i-1]; double cost = dis / speed; 
        double go = min(cost,time); res += go*speed; time -= go; speed++; i--; }
    return res; }

bool check(double time) {
   // ses(time); ses(aRun(time)); see(bRun(time));
    return aRun(time) + bRun(time) >= g_l; }

void solve() {
    double l=0, r=g_l;
    rep (i,50) {
        double mid = (l+r)/2;
        if (check(mid)) { r=mid; }
        else { l = mid; } }
    printf("%.10lf\n",l);
}
