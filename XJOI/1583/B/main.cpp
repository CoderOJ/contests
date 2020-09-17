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

const int MOD = 1e9+7;
const int N = 55;
int len[N]; char s[N][N];
int prime[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
bool isPrime[N];
int n;

int gcd(int a, int b) { return b? a : gcd(b,a%b); }
int lcm(int a, int b) { return a*b/gcd(a,b); }

void init() {
    scanf(I,&n);
    rep (i,n) { scanf(I,&len[i]); scanf("%s", s[i]); }
    rep (i,15) isPrime[prime[i]]=1;
}

int roundCnt[N], roundMaxCnt[N];
int getRound() {
    repa (i,50) {
        int x=i;
        rep (j,15) {
            while (x%prime[j]==0) { x/=prime[j]; roundCnt[j]++; } } }
    rep (i,n) {
        int x=len[i];
        rep (j,15) {
            int tmp=0;
            while (x%prime[j]==0) { x/=prime[j]; tmp++; }
            checkMax(roundMaxCnt[j],tmp); } }
    int res=1;
    rep (i,15) rep (j,roundCnt[i] - roundMaxCnt[i]) (res*=prime[i])%=MOD;
    return res; }

vector <int> v[N];
vector <int> cnt;

void solve() {
    int round= getRound();
    int L=1;
    rep (i,n) {
        if (len[i]>=11 && isPrime[len[i]]) {
            v[ len[i] ].push_back(i); }
        else {
            L=lcm(L, len[i]); } }
    cnt.resize(L);
    rep (i,n) {
        if (len[i]>=13 && isPrime[len[i]]) continue;
        rep (j,L) if (s[i][j % len[i]] =='O') cnt[j]++; }
}

