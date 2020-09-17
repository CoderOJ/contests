#pragma GCC optimize(2)
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
#include <unordered_map>
#include <unordered_set>
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

const int MOD = 323232323;
const int N = 100005;
int a[N]; int n;

void init() {
    scanf(I,&n);
    rep (i,n) scanf(I,&a[i]); 
}

int power(int a, int b) {
    int r=1; a%=MOD;
    while (b) {
        if (b&1) (r*=a) %= MOD;
        (a*=a)%=MOD; b>>=1; }
    return r; }
int inv(int u) { return power(u,MOD-2); }

namespace A1 {
    bool jury() {
        rep (i,n) if (a[i]>1) return 0;
        return 1; }
    int f[N];
    void main() {
        f[0]=0; 
        repa (i,n) f[i] = ( (i-1)*inv(i)%MOD * f[i-1]%MOD +1 ) %MOD;
        printf(IN,f[n]); }
}

namespace N2 {
    bool jury() {
        return n<=2; }
    int f[1005][1005];
    void main() {
        memset(f,0,sizeof(f));
        rep (i,a[0]+1) f[i][0]=i;
        repa (j,a[1]) repa (i,a[0]) f[i][j] = ( (f[i-1][j]+f[i][j-1]) * inv(2) % MOD + 1 ) % MOD;
        printf(IN, f[a[0]][a[1]]); }
}

namespace Guess {
    void main() {
        int s=0; rep (i,n) s+=a[i];
        printf(IN,s*inv(2)%MOD); } 
}

void solve() {
//    if (A1::jury()) A1::main();
    if (N2::jury()) N2::main();
    else Guess::main();
}

