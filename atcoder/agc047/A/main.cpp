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

#define double long double

const int N = 50;
typedef pair<int,int> Pt;

struct Arr {
    int a[N*2][N*2];
    Arr () { memset(a,0,sizeof(a)); }
    int& at(int x, int y) { return a[x+N][y+N]; }
};

Arr t;

inline bool isInt(double x) {
    double r=(int)(x); return abs(r-x) < 1e-10; }

Pt get(double x) {
    int a=9, b=9;
    x *= (double)1e9;
    int u=(x+0.1);
    see(u);
    while (u%2==0) { a--; u/=2; }
    while (u%5==0) { b--; u/=5; }
    return (Pt){a,b}; }

void init() {
    int n; scanf(I,&n);
    rep (i,n) {
        double x; scanf("%Lf",&x); 
        Pt u = get(x);
        ses(u.L); see(u.R);
        t.at( u.L , u.R )++; }    
}

void solve() {
    int ans=0;
    repi (a,-25,25) repi (b,-25,25) repi (c,-25,25) repi (d,-25,25) { 
        if (a+c<=0 && b+d<=0 && t.at(a,b) && t.at(c,d)) {
            ses(a);ses(b);ses(c);see(d);
            ans += (t.at(a,b) * t.at(c,d));
            if (a==c && b==d) ans -= t.at(a,b); } }
    printf(IN,ans/2);
}

