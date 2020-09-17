#define ENABLE_LL
#define MULTIPLE_TEST_CASES_WITH_T
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

void init() {
     
}

namespace t1 {
    int power (int a, int b, int MOD) {
        int r=1;
        while (b) {
            if (b&1) (r*=a)%=MOD;
            (a*=a)%=MOD; b>>=1; }
        return r; } 
    void main() {
        int y,z,p; scanf(III,&y,&z,&p);
        printf(IN,power(y,z,p)); } }

namespace t2 {  //ExBSGS
    int gcd(int a, int b) {return b==0 ? a: gcd(b,a%b); }

    int ExBSGS(int a, int b, int p) {
        if (p == 1) return 0;
        a%=p; b%=p;
        if (a==0 && b==0) { return 1; } if (b==1) { return 0; } if (a==0) { return -1; }
        int g, step=0, k=1;
        while ( (g=gcd(a,p)) != 1 ) {
            if (b%g != 0) return -1;
            p /=g; b /=g; (k *= a/g) %= p; step++;
            if (b == k) return step; }
        // normal BSGS
        unordered_map <int,int> mp;
        int m= ceil(sqrt(p)); int babyStep= b;
        rep (i,m+1) {
            mp[ babyStep ]=i;
            (babyStep *= a) %= p; }
        int giantUnit = t1::power(a,m,p);
        int giantStep = k*giantUnit % p;
        repa (i,m) {
            if (mp.count(giantStep)) return i*m - mp[giantStep] + step;
            (giantStep *= giantUnit) %= p; }
        return -1; }

    void main () { 
        int y,z,p; scanf(III,&y,&z,&p);
        int res=ExBSGS(y,z,p);
        if (res==-1) puts("Math Error");
        else printf(IN,res); }
}

namespace t3 { //ExLucas
int power(int a, int b, int p) {
    int r=1; a%=p;
    while (b) {
        if (b&1) (r*=a) %=p;
        (a*=a) %= p; b>>=1; }
    return r; }
int exgcd(int a, int b, int&x, int& y) {
    if (b == 0) { x=1; y=0; return a; }
    int x0 = x, y0 = y;
    int res = exgcd(b, a%b, x0, y0);
    x = y0; y = x0 - a / b * y0;
    return res; }
inline int inv(int u, int p) {
    u%=p;
    int x, y; exgcd(u,p,x,y);
    int res=(x%p+p)%p;  return res; }
int CRT(vector<int>& dd, vector<int>& mm) {
    int m=1, ans=0; for (int& a: dd) m*=a;
    repe (i,dd) {
        int cm= m/dd[i];
        int x,y; exgcd(cm,dd[i],x,y);
        (ans += cm*x%m*mm[i]) %=m; }
    return (ans+m)%m; }

int calc (int n, int x, int p) {
    if (n==0) return 1;
    int ans=1;
    repa (i,p) if (i%x != 0) (ans *= i) %= p;
    ans = power(ans,n/p,p);
    for (int i=n/p*p+1; i<=n;i++) if (i%x != 0) (ans*=i%p)%=p;
    return ans * calc(n/x,x,p) % p; }

int multiLucas(int n, int m, int x, int p) {
    int a=0; for (int i=n;i;i/=x) a+=i/x;
    int b=0; for (int i=m;i;i/=x) b+=i/x;
    int c=0; for (int i=n-m;i;i/=x) c+=i/x;
    return power(x,a-b-c,p)
           * calc(n,x,p)%p
           * inv( calc(m  ,x,p) , p)%p
           * inv( calc(n-m,x,p) , p)%p; }

int exLucas(int n, int m, int p) {
    vector <int> dd, mm;
    for (int i=2;i*i<=p;i++) {
        if (p%i == 0) {
            dd.push_back(1);
            while (p%i==0) { dd.back() *= i; p /=i; }
            mm.push_back( multiLucas(n,m,i,dd.back()) ); } }
    if (p > 1) { dd.push_back(p); mm.push_back( multiLucas(n,m,p,p) ); }
    return CRT(dd, mm); }

    void main() {
        int y,z,p; scanf(III,&y,&z,&p);
        printf(IN, exLucas(z,y,p)); }
}

void solve() {
    int type; scanf(I,&type);
    if (type==1) t1::main();
    if (type==2) t2::main();
    if (type==3) t3::main();
}

