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

const int MOD = 1000000007;
int n, m, k;

void init() {
    scanf(III,&n,&m,&k); 
}

int power(int a, int b) {
    int r=1;
    while (b) {
        if (b&1) (r*=a) %= MOD;
        (a*=a) %= MOD; b>>=1; }
    return r; }

namespace BruteForce {
    bool check() { return n<=100 && m<=100 && k!=1; }
    void main() {
        int ans=0;
        repa (i,n) repa (j,m) (ans+= power(__gcd(i,j), k)) %= MOD;
        printf(IN, ans); } }

namespace k1 {
    const int N = 5000005;
    int phi[N], isPrime[N]; vector <int> prime;

    void initPhi() {
        phi[1]=1;
        rep (i,N) isPrime[i]=1;
        repi (i,2,N-1) {
            if (isPrime[i]) { prime.push_back(i); phi[i]=i-1; }
            for (int j: prime) {
                int t=i*j; if (i*j>=N) break;
                isPrime[i*j] = 0;
                if (i%j==0) {
                    phi[t]= phi[i]*j;
                    break; }
                else phi[t]= phi[i]*(j-1); } } }

    bool check() { return k==1; }
    void main() {
        initPhi(); 
        repa (i,max(n,m)) ses(phi[i]); see("");
        int ans=0;
        repa (i,min(n,m)) (ans += phi[i]*(n/i)%MOD*(m/i)%MOD) %=MOD;
        printf(IN,ans); } }

namespace AC {
    const int N = 5000005;
    int p[N], isp[N], f[N]; vector<int> prime;
    void seive() {
        f[1]=1; p[1]=1; rep (i,N) isp[i]=1;
        repi (i,2,N-1) {
            if (isp[i]) { prime.push_back(i); p[i]=power(i,k); (f[i]=p[i]-1+MOD)%=MOD; }
            for (int j: prime) {
                int t=i*j; if (t>=N) break;
                isp[t]=0; 
                if (i%j==0) { f[t]=f[i]*p[j]%MOD; }
                else { f[t]=f[i]*f[j]%MOD; } } } 
        repa (i,3) {ses(f[i]);see(p[i]);}}
    void main() {
        seive(); int ans=0;
        repa (i,min(n,m)) (ans += f[i] * (n/i)%MOD * (m/i)%MOD) %=MOD;
        printf(IN,ans); } }

void solve() {
    AC::main();
}

