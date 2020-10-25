#pragma GCC optimize(2,3,"Ofast")
#pragma GCC target("avx", "avx2")
#define ENABLE_LL
#include <iostream>
#include <cstdio>
using namespace std;
  
#ifndef _LIB_SCANNER
#define _LIB_SCANNER 1
#include <stdio.h>
#include <stdlib.h>
class Scanner {
private:
    static const int BUFFER_SIZE = 10000; char buff[BUFFER_SIZE]; int buffPos, buffLim;
public:
    Scanner () { buffLim = fread(buff, 1, BUFFER_SIZE, stdin); buffPos = 0; }
private:
    inline void flushBuff() { buffLim = fread(buff, 1, BUFFER_SIZE, stdin); if (buffLim==0) { buff[buffLim++] = '\n'; } buffPos = 0; }
    inline bool isWS(char t) { return t==' ' || t=='\n'; }
    inline bool isDig(char t) { return t>='0' && t<='9'; }
    void nextPos() { buffPos++; if (buffPos == buffLim) { flushBuff(); } }
#define getChar() buff[buffPos]
public:
    inline char getchar() { char ch=getChar(); nextPos(); return ch; }
    inline void next(char* s) { while ( isWS(getChar()) ) { nextPos(); } while ( !isWS(getChar()) ) { *s = getChar(); s++; nextPos(); } *s = '\0'; }
    inline void nextLine(char* s) { while ( getChar()!='\n' ) { nextPos(); } if ( getChar()=='\n' ) { nextPos(); } while ( getChar() != '\n' ) { *s = getChar(); s++; buffPos++; } *s = '\0'; }
    inline int nextInt() { while ( !isDig(getChar()) && getChar() != '-' ) { nextPos(); } int sign = (getChar() == '-') ? nextPos(),-1 : 1; int res = 0; while (isDig(getChar())) { res = res*10 + getChar()-'0'; nextPos(); } return res * sign; }
    inline int n() { while ( getChar()<'0' || getChar()>'9' ) { buffPos++; if ( buffPos == buffLim ) { flushBuff(); } } int res = 0; while ( getChar()>='0' && getChar()<='9' ) { res = res*10 + (getChar()-'0'); buffPos++; if ( buffPos == buffLim ) { flushBuff(); } } return res; }
    inline double nextDouble() { while ( isWS(getChar()) ) { nextPos(); } int sign = (getChar() == '-') ? nextPos(),-1 : 1; double res = 0; while (isDig(getChar())) { res = res * 10 + getChar()-'0'; nextPos(); } if (getChar() == '.') { nextPos(); double ep = 1; while (isDig(getChar())) { ep *= 0.1; res += ep * (getChar()-'0'); nextPos(); } } return sign * res; }
    inline char nextChar() { while (isWS(getChar())) nextPos(); char res = getChar(); nextPos(); return res; }
#undef getChar
};
#endif /* _LIB_SCANNER */
  
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
#define repe(a,b) for (uint32_t a=0;a<(int)b.size();a++)
#define rep(i,n) for (uint32_t i=0;i<n;i++)
#define repa(i,n) for (uint32_t i=1;i<=n;i++)
#define repi(i,a,b) for (uint32_t i=a;i<=b;i++)
#define repb(i,a,b) for (uint32_t i=a;i>=b;i--)
  
typedef std::pair < int , int > pr;
typedef std::pair < pr  , int > prr;
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); }
void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } }
bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }
#define L first
#define R second
  
#ifdef __LOCALE__
template <typename T> void __ses(T a) { cout << a << " "; }
template <typename T, typename ... Args> void __ses(T a, Args... b) { cout << a << " "; __ses(b...); }
#define ses(...) cout << #__VA_ARGS__ << " = "; __ses(__VA_ARGS__)
#define see(...) ses(__VA_ARGS__); cout << endl
#define slog(format, ...) printf(format, __VA_ARGS__)
#else
#define see(...)
#define ses(...)
#define slog(format, ...)
#endif
  
  
#ifndef CUSTOM_MAIN
void preInit(); void init(); void solve(); int32_t main(){ preInit();
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
while(1) { try {init(); } catch(bool t) {return 0;} solve(); }
#else
init(); solve();
#endif /* MULTIPLE_TEST_CASES_WITHOUT_T  */
#endif /* MULTIPLE_TEST_CASES_WITH_T */
    return 0; }
#endif /* CUSTOM_MAIN */
  
// my code begins here
  
  
const int UPP = 5;
const int MOD = 998244353;
const int N = 1000005;
char s[N];
int n;
  
inline int power(int a, int b, int MOD) { int r = 1; while (b) { if (b&1) (r*=a) %= MOD; (a*=a)%=MOD; b>>=1; } return r; }
int pinv[N];
inline int inv(int u, int MOD) { return power(u,MOD-2,MOD); }
void initPinv() { repa (i,N-1) pinv[i] = inv(i, MOD); }
  
namespace NCR {
    int fac[N], finv[N];
    void init() { fac[0] = 1; finv[0] = 1; repa (i,N-1) { fac[i] = (fac[i-1]*i) % MOD; finv[i] = inv(fac[i], MOD); } }
    int get(int n, int r) { return fac[n] * finv[r] % MOD * finv[n-r] % MOD;  } };
  
template <int MOD, int D> struct HashString {
    int d[N];
    int inv[N];
  
    void init(char *s) {
        int p = 1; int i = 0;
        while (*s) {
            if (i) { d[i] = d[i-1]; } (d[i] += p * (*s-'a')) %= MOD;
            inv[i] = power(p, MOD-2, MOD); p = p * D % MOD; s++; i++; } }
    int query(int l, int r) {
        int pos = d[r]; if (l > 0) { pos += MOD-d[l-1]; }
        return pos * inv[l] % MOD; } };
  
HashString<19490027, 133> HA;
HashString<19260011, 123> HB;
  
int Pr(int a, int b) { return a*200000000 + b; }
  
template <int N> struct HashDis {
    int first[N], next[N], value[N];
    uint32_t n, MOD, cnt;
  
    inline uint64_t hash(uint64_t u) { return u%MOD; }
    void init(uint64_t a[], uint32_t _n, uint32_t _MOD) {
        n = _n; MOD = _MOD;
        memset(first, -1, sizeof(*first) * n); memset(next, -1, sizeof(*next) * n); cnt = 0;
        rep (i,n) {
            int val = hash(a[i]);
            next[cnt] = first[ val ]; first[ val ] = cnt; value[ cnt ] = a[i];
            cnt++; } }
    inline int query(int u) {
        int val = hash(u);
        for (int attemp = first[val]; attemp != -1; attemp = next[ attemp ]) {
            if (value[attemp] == u) { return attemp; } }
        return -1; }
};
  
template <int N, uint64_t SEED> struct HashSeq {
    uint64_t weight[N], val[N];
    uint32_t n; int value;
  
    void init(int32_t _n) {
        n = _n; memset(val, 0, sizeof(*val) * n);  value=0;
        weight[0] = SEED; repa (i,n-1) { weight[i] = weight[i-1] * SEED; } }
    inline void update(int pos, int del) {
        val[pos] += del;
        value += del * weight[pos]; }
    inline uint64_t getHash() { return value; }
    inline int at(int pos) { return val[pos]; }
};
  
template <int N> struct HashSet {
    int8_t cnt[N];
    HashDis<N*UPP> Trigger;
    inline void init(uint64_t a[], int n) {
        memset(cnt, 0, sizeof(*cnt) * n);
        Trigger.init(a, n, n*UPP); }
    inline void insert(int a) {
        cnt[ Trigger.query(a) ] ++; }
    inline int count(int a) {
        return cnt[ Trigger.query(a) ]; }
};
  
  
void preInit() { initPinv();  } void init() {
    scanf("%s", s); n = strlen(s);   
    HA.init(s); HB.init(s); NCR::init();
}
  
inline int strHash(int l, int r) { return Pr( HA.query(l,r), HB.query(l,r) ); }
  
  
uint64_t shs[N*2], shsCnt;
uint64_t pseq[N];
int pans[N];
int get(int len) {
    int32_t sk=n%len, sks=n/len;
    shsCnt=0;
    for (int32_t i=n%len; i<n; i+=len) shs[shsCnt++] = strHash(i, i+len-1);
    for (int32_t i=0; i<n-n%len; i+=len) shs[shsCnt++] = strHash(i, i+len-1);
    static HashDis<N*2*UPP> hd; hd.init( shs, shsCnt, shsCnt*UPP );
    static HashSeq<N*2, 1113> hs; hs.init(shsCnt);
  
    for (int32_t i=sk; i<n; i+=len) {
        int32_t pha = hd.query(strHash(i, i+len-1));
        hs.update(pha, +1); }
    int32_t rem=n/len; pseq[0] = hs.getHash(); pans[0]=1; int pCnt=1;
    rep (i,shsCnt) {
        (pans[0] *= NCR::get(rem, hs.at(i))) %= MOD; rem -= hs.at(i); }
    for (int32_t i=0; i+sk<n; i+=len) {
        int32_t ori = hd.query( shs[i/len] );
        int32_t upd = hd.query( shs[i/len + sks] );
        if (ori == upd) { continue; }
        int32_t na = hs.at(ori), nb = hs.at(upd);
        hs.update(ori, -1); hs.update(upd, +1);
        pans[pCnt] = pans[pCnt-1]; (pans[pCnt] *= na * pinv[nb+1] % MOD) %= MOD;
        pseq[pCnt] = hs.getHash(); pCnt++; }
  
    int ans = 0;
    static HashSet<N> st; st.init(pseq, pCnt);
    rep (i,pCnt) {
        if (st.count( pseq[i] ) == 0) {
            ans += pans[i];
            st.insert( pseq[i] ); } }
    return ans % MOD; }
  
void solve() {
    int ans = 0;
    repa (d,n) { ans += get(d); }
    printf(IN,ans % MOD);
}
