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
void init(); void solve(); int main(){ try { 
#ifdef MULTIPLE_TEST_CASES_WITH_T
int T; scanf("%d",&T); while(T--) {init(); solve();} 
#else
#ifdef MULTIPLE_TEST_CASES_WITHOUT_T 
while(1) {try{init(); } catch(bool t){return 0;} solve(); } 
#else
init(); solve(); 
#endif
#endif
} catch (...) { return 0; } return 0; }
#endif
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
#define L first
#define R second
typedef pair < int , int > pr; typedef pair < pr  , int > prr; template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); } template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); } void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } } bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }
class Scanner { private: static const int BUFFER_SIZE = 10000; char buff[BUFFER_SIZE]; int buffPos, buffLim; public: Scanner () { buffLim = fread(buff, 1, BUFFER_SIZE, stdin); buffPos = 0; } private: inline void flushBuff() { buffLim = fread(buff, 1, BUFFER_SIZE, stdin); if (buffLim==0) { buff[buffLim++] = '\n'; } buffPos = 0; } inline bool isWS(char t) { return t==' ' || t=='\n'; } inline bool isDig(char t) { return t>='0' && t<='9'; } void nextPos() { buffPos++; if (buffPos == buffLim) { flushBuff(); } } 
#define getChar() buff[buffPos]
public: inline char getchar() { char ch=getChar(); nextPos(); return ch; } inline void next(char* s) { while ( isWS(getChar()) ) { nextPos(); } while ( !isWS(getChar()) ) { *s = getChar(); s++; nextPos(); } *s = '\0'; } inline void nextLine(char* s) { while ( getChar()!='\n' ) { nextPos(); } if ( getChar()=='\n' ) { nextPos(); } while ( getChar() != '\n' ) { *s = getChar(); s++; buffPos++; } *s = '\0'; } inline int nextInt() { while ( !isDig(getChar()) ) { nextPos(); } int sign = (getChar() == '-') ? nextPos(),-1 : 1; int res = 0; while (isDig(getChar())) { res = res*10 + getChar()-'0'; nextPos(); } return res * sign; } inline double nextDouble() { while ( isWS(getChar()) ) { nextPos(); } int sign = (getChar() == '-') ? nextPos(),-1 : 1; double res = 0; while (isDig(getChar())) { res = res * 10 + getChar()-'0'; nextPos(); } if (getChar() == '.') { nextPos(); double ep = 1; while (isDig(getChar())) { ep *= 0.1; res += ep * (getChar()-'0'); nextPos(); } } return sign * res; } inline char nextChar() { while (isWS(getChar())) nextPos(); char res = getChar(); nextPos(); return res; } 
#undef getChar
}; 
// Integer under mod

#ifndef _LIB_INTM
#define _LIB_INTM

class Intm {
private:
    static unsigned long long MOD;
    static unsigned long long k;

    unsigned long long a;

public:
    inline static void setMod(const unsigned long long _MOD) {
        MOD = _MOD;
        k = (__uint128_t(1) << 64) / _MOD; }
    inline static void getModSub(unsigned long long & a) {
        if (a>=MOD) a-=MOD; }
    inline static void getModAdd(unsigned long long & a) {
        if (a < 0) a+=MOD; }
    inline static void getMod(unsigned long long & a) {
        unsigned long long q = (unsigned long long)((__uint128_t(k) * a) >> 64);
        a -= q*MOD; getModSub(a); }
    inline static unsigned long long power(unsigned long long a, unsigned long long b) {
        unsigned long long r = 1;
        while (b) {
            if (b&1) getMod(r*=a);
            getMod(a*=a); b>>=1; }
        return r; }

    Intm () { a=0; }
    Intm (unsigned long long _a) : a(_a) { getMod(a); }
    Intm& operator += (const Intm b) {
        a += b.a; getModSub(a); return *this; }
    Intm operator + (const Intm b) const {
        Intm R(a); return (R += b); }
    Intm& operator -= (const Intm b) {
        a += MOD-b.a; getModSub(a); return *this; }
    Intm operator - (const Intm b) const {
        Intm R(a); return (R -= b); }
    Intm& operator *= (const Intm b) {
        a *= b.a; getMod(a); return *this; }
    Intm operator * (const Intm b) const {
        Intm R(a); return (R *= b); }
    Intm& operator /= (const Intm b) {
        a *= power(b.a,MOD-2); getMod(a); return *this; }
    Intm operator / (const Intm b) const {
        Intm R(a); return (R /= b); }
    Intm pow(int e) {
        return Intm(power(a,e)); }

    operator int()  {
        return (int)a; }
};


unsigned long long Intm::MOD;
unsigned long long Intm::k;

#endif /* _LIB_INTM */


vector <long long> factor(int u) {
    vector <int> res(1,1);
    for (int i=2;i*i<=u;i++) {
        if (u%i==0) {
            res.push_back(i);
            if (i*i!=u) res.push_back(u/i); } }
    return res; }

int phi(int u) {
    int res=u;
    for (int i=2;i*i<=u;i++) {
        if (u%i==0) {
            res = res/i * (i-1);
            while (u%i == 0) { u/=i; } } }
    if (u != 1) { res = res/u * (u-1); }
    return res; }

int n;
Scanner sc;

void init() {
    n = sc.nextInt(); 
    Intm::setMod(1000000007);
}

void solve() {
    Intm ans=0;
    auto fac = factor(n);
    Intm n2 = 2;
    for (int u: fac) {
        ses(u);ses(n2.pow(u));see(phi(u));
        ans += n2.pow(u) * Intm(phi(n/u)); }
    see(Intm(n));
    printf(IN,(int)(ans+n2-Intm(n)));
}

