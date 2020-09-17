#pragma GCC optimize(2)
#pragma GCC optimize(3)
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

#define repe(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)

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
typedef pair < int , int > pr; typedef pair < pr  , int > prr;
#define L first
#define R second
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); }
class Scanner{ private: istream& ist;public: Scanner(istream& in):ist(in){} string next(){ string r; ist >> r; return r; } string nextLine(){ string r; getline(ist,r); return r; } int nextInt(){ int r; ist >> r; return r; } double nextDouble(){ double r; ist >> r; return r; } char nextChar(){ char r; ist>>r; return r;} }; Scanner sc(cin);
void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } }
bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }

const int INF = (int)(2e18);
int gcd(int a, int b) { return b==0 ? a : gcd(b,a%b); }
inline int poptCount(int a) { int ans=0; while(a) { a -= (a&(-a)); ans++; } return ans; }
inline int getBit(int a, int w) { return (a>>w) & 1; }
inline bool willEx(int a, int b, int l=INF) { return l/a < b; }
inline int lcm(int a, int b) {
    a/=gcd(a,b);
    if (willEx(a,b)) { return -1; } 
    else return a*b; }

const int N = 16;
int a[N], b[N], d[N], n,m;
vector <int> fac; int fac_b; int fac_sz;
const int POP_COUNT=(1<<18);
int pops[POP_COUNT];

void init() {
    scanf(II,&n,&m);
    int cnt=0;
    rep (i,n) {
        int _a,_b,_d; scanf(III,&_a,&_b,&_d);
        if (gcd(_d,m)==1) {
           a[cnt]=_a; b[cnt]=_b; d[cnt]=_d; cnt++; } }
    n = cnt; 

    int u=m;
    for (int i=2;i*i<=u;i++) {
        if (u%i==0) {
            while (u%i==0) { u/=i; }
            fac.push_back(i); } }
    if (u!=1) { fac.push_back(u); }
    fac_b = (1<<fac.size());
    fac_sz = fac.size();

    rep (i,POP_COUNT) pops[i] = poptCount(i);
}

int get(int u) {
    int ans=0;
    rep (b,fac_b) {
        int pop=pops[b]; int wei = (pop&1) ? -1 : 1;
        int pos=1; rep (i,fac_sz) if (getBit(b,i)) pos *= fac[i];
        ans += wei * (u/pos); }
    return ans; }

inline int suc(int u, int t) { return (u-1)/t+1; }
inline int pre(int u, int t) { return u/t; }
int getAns(int bt) {
    int g=1;
    rep (i,n) {
        if (getBit(bt,i)) {
            g = lcm(g,d[i]);
            if (g==-1) return 0; } }
    int l=0, r=INF;
    rep (i,n) {
        if (getBit(bt,i)) {
            checkMax(l, suc(a[i],g/d[i]));
            checkMin(r, pre(b[i],g/d[i])); } }
    if (l > r) return 0;
    return get(r) - get(l-1); }

void solve() {
    int ans=0;
    repa (b,(1<<n)-1) {
        int pop=pops[b]; int wei = (pop&1) ? 1 : -1;
        ans += wei * getAns(b); }
    printf(IN,ans); 
}

