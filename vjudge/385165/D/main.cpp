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

const int N = 205;
int p[N], q[N], n;
vector <int> first, loop;

void init() {
    scanf(I,&n); first.resize(n); loop.resize(n);
    rep (i,n) { scanf(I,&p[i]); p[i]--; }
    rep (i,n) { scanf(I,&q[i]); q[i]--; }
    rep (i,n) {
        int u=p[i]; first[i]=-1; int step=0;
        while (1) {
            ALERT(step>n*2, "-1");
            if (u == i) {
                if (first[i] != -1) { loop[i] = step - first[i]; break; }
                else first[i] = step; }
            u = q[u]; step++; } }
    rep (i,n) { ses(first[i]); see(loop[i]); }
    rep (i,n) rep (j,n) if (i!=j) if (loop[i] == loop[j]) ALERT(first[i]!=first[j], "-1");
}

int exgcd(int a, int b, int&x, int& y) {
    if (b == 0) {
        x=1; y=0;
        return a;
    }
    int x0 = x, y0 = y;
    int res = exgcd(b, a%b, x0, y0);
    x = y0;
    y = x0 - a / b * y0;
    return res;
}

int multiply(int a, int b, int mod) {
    int res = 0;
    while (b) {
        if (b & 1) (res += a) %= mod;
        b >>= 1;
        (a += a) %= mod;
    }
    return res;
}

int merge(int pos, int delta, int mod) {
    int res, k;
    int gcd = exgcd(pos, mod, res, k);
    if (delta % gcd != 0) throw "Answer Not Exists";
    int multi = delta / gcd;
    res = multiply(res, multi, mod);
    ( (res%=mod)+=mod ) %= (mod/gcd);
    return res;
}

int excrt(vector < int > m, vector < int > b) {
    int n = m.size();
    int pos = b[0];
    int multi = m[0];
    repa (i,n-1) {
        int delta = (b[i] - pos%m[i] + m[i]) % m[i];
        int mul=merge(multi, delta, m[i]);
        pos += mul * multi;
        ses(delta);ses(mul);see(pos);
        multi *= m[i] / __gcd(m[i], multi);
    }
    return pos;
}


void solve() {
    try {
        printf(IN,excrt(loop, first));
    } catch (...) {
        puts("-1"); 
    }
}

