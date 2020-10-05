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
 
 
 
 
 
int dp[85][85][85];
 
 
 
void preInit() {
    int n = 82;
    dp[0][0][0] = 1;
    rep (i,n) rep (j,n) rep (k,n) {
        rep (ni,i) {
            int nj = min(j,ni), nk = min(k,ni);
            dp[i][j][k] |= !dp[ni][nj][nk]; }
        rep (nj,j) {
            int ni=i, nk = min(k,nj);
            dp[i][j][k] |= !dp[ni][nj][nk]; }
        rep (nk,k) {
            int ni=i, nj=j;
            dp[i][j][k] |= !dp[ni][nj][nk]; } }
}
 
void init() {
      
}
 
void solve() {
    int n; scanf(I,&n);
    int a[5]; rep (i,n) scanf(I,&a[i]);
    if (n == 1)
    {
        if (a[0] == 1) { puts("Lose"); }
        else { puts("1"); }
    }
    if (n == 2)
    {
        if (a[0] == a[1]+1) { puts("Lose"); }
        else {
            int m = min(a[0], a[1]+1);
            printf("%d %d\n", m, m-1); }
    }
    if (n == 3)
    {
        if (a[0] <= 80)
        {
            if ( dp[ a[0] ][ a[1] ][ a[2] ] == 0 ) { puts("Lose"); }
            else {
                int i=a[0], j=a[1], k=a[2];
                rep (ni,i) {
                    int nj = min(j,ni), nk = min(k,ni);
                    if (dp[ni][nj][nk] == 0) { printf("%d %d %d\n", ni,nj,nk); goto finish; } }
                rep (nj,j) {
                    int ni=i, nk = min(k,nj);
                    if (dp[ni][nj][nk] == 0) { printf("%d %d %d\n", ni,nj,nk); goto finish; } }
                rep (nk,k) {
                    int ni=i, nj=j;
                    if (dp[ni][nj][nk] == 0) { printf("%d %d %d\n", ni,nj,nk); goto finish; } }
                finish:; }
        }
        else if (a[2] == 0)
        {
            if (a[0] == a[1]+1) { puts("Lose"); }
            else {
                int m = min(a[0], a[1]+1);
                printf("%d %d 0\n", m, m-1); }
        }
        else if (a[2] == 1)
        {
            if (a[1] == 1) { puts("3 1 1"); }
            else { puts("2 2 1"); }
        }
        else if (a[2] == 2)
        {
            if (a[0] == a[1] + 2) { puts("Lose"); }
            else {
                int m = min(a[0], a[1]+2);
                printf("%d %d 2\n",m,m-2); }
        }
        else if (a[2] == 3)
        {
            if (a[1] == 3) { puts("6 3 3"); }
            else if (a[1] == 4) { puts("7 4 3"); }
            else { puts("5 5 3"); }
        }
        else
        {
            puts("Lose");
        }
    }
}
