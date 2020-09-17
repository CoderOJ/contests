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

const int N = 500005;
int n, l;
pr inter[N];

void init() {
    scanf(II,&n,&l); rep (i,n) scanf(II,&inter[i].L, &inter[i].R); 
    vector <int> fs; fs.push_back(l); rep (i,n) { fs.push_back(inter[i].L); fs.push_back(inter[i].R); }
    sort(fs.begin(), fs.end()); fs.erase(unique(fs.begin(), fs.end()), fs.end());
    l= lower_bound(fs.begin(),fs.end(),l)-fs.begin();
    rep (i,n) {
        inter[i].L = lower_bound(fs.begin(), fs.end(), inter[i].L) - fs.begin();
        inter[i].R = lower_bound(fs.begin(), fs.end(), inter[i].R) - fs.begin(); }
}

int reach[N], times[N];
void solve() {
    rep (i,n) checkMax(reach[inter[i].L], inter[i].R);
    rep (i,n) { times[inter[i].L]++; times[inter[i].R]--; }
    repa(i,l-1) times[i] += times[i-1];
    int minTop=times[0]; rep (i,l) checkMin(minTop, times[i]);
    int r=-1, mr=reach[0]; int ans=0;
    rep (i,l) {
        if (i>=r) { ans++; r=mr; }
        checkMax(mr, reach[i]); }
    printf("%lld %lld\n", ans, n-minTop+1);
}

