#define ENABLE_LL
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

struct FTree{
    int a[N*2];
    FTree () { memset(a,0,sizeof(a)); }
    inline int low(int u) { return u & (-u); }
    void modfiy(int u) {
        u += N;
        while (u<N*2) { 
            a[u]++; u += low(u);  } }
    int query(int u) {
        u+=N; int res =0 ;
        while (u) {
            res += a[u];
            u -= low(u); } 
        return res; }
};

int a[N];
int n;



void preInit() {

}

void init() {
    scanf(I,&n);
    rep (i,n) scanf(I,&a[i]);
    if (n==1) {
        printf(IN,a[0]); fflush(stdout);
        __asm__("movl $1, %eax; movl $0, %ebx; int $0x80"); }
}

int b[N];
int lows(int u) {
    FTree st; st.modfiy(0);
    rep (i,n) b[i] = (a[i]<=u) ? -1 : 1;
    int cur = 0; int res = 0;
    rep (i,n) {
        cur += b[i];
        res += i+1-st.query(cur);
        st.modfiy(cur); }
    return res; }

void solve() {
    int l=1, r=0x3f3f3f3f;
    int tot = n*(n+1)/2;
    int stand = tot/2;
    while (l<r) {
        int m = (l+r)/2;
        if (lows(m) > stand) { r = m; }
        else { l=m+1; } }
    printf(IN,l);
}
