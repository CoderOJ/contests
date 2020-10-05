#include <iostream>
#include <cstdio>
using namespace std; 
#ifndef _LIB_STREE
#define _LIB_STREE 1

#include <algorithm>

namespace STree {

// Template Node for maintain sums
struct NodeSum {
    long long val; long long tg;
    NodeSum (long long val=0, long long tg=0) : val(val), tg(tg) {}
    void update(int _val) {
        val += _val; tg += _val; }
    void pushUp (NodeSum a, NodeSum b) {
        val = a.val + b.val; }
    void pushDown (NodeSum &a, NodeSum &b) {
        a.val += tg; b.val += tg;
        a.tg += tg; b.tg += tg;
        tg = 0; }
};

// Template Node for maintain maxs
struct NodeMax {
    int val; int tg;
    NodeMax (int val=0, int tg=0) : val(val), tg(tg) {}
    void update(int _val) {
        val += _val; tg += _val; }
    void pushUp (NodeMax a, NodeMax b) {
        val = std::max(a.val, b.val); }
    void pushDown (NodeMax &a, NodeMax &b) {
        a.val += tg; b.val += tg;
        a.tg += tg; b.tg += tg;
        tg = 0; }
};

//Default STree for maintain maxs
template <int N, class Item=NodeMax> class STree {
protected:
    Item a[N*4];
    int g_l, g_r;

    template <class T> 
    void _modify(int l, int r, int sl, int sr, T val, int u) {
        if (sl <= l && r <= sr) {
            a[u].update(val); 
            return; }
        a[u].pushDown(a[u+u],a[u+u+1]); 
        int mid = (l+r)/2;
        if (sl <= mid)   _modify(l,mid,  sl,sr,val,u+u);
        if (sr > mid)    _modify(mid+1,r,sl,sr,val,u+u+1);
        a[u].pushUp(a[u+u],a[u+u+1]); }

    Item _query(int l, int r, int sl, int sr, int u) {
        if (sl <= l && r <= sr) {
            return a[u]; }
        a[u].pushDown(a[u+u],a[u+u+1]); 
        int mid = (l+r)/2;
        if (sl > mid)        return _query(mid+1,r,sl,sr,u+u+1); 
        else if (sr <= mid)  return _query(l,mid,sl,sr,u+u);
        else {   
            Item res; 
            res.pushUp( _query(l,mid,sl,sr,u+u), _query(mid+1,r,sl,sr,u+u+1) );
            return res; } }
public:
    void setLR(int _l, int _r) {
        g_l = _l, g_r = _r; }
    template <class T> 
    void modify(int l, int r, T val) {
        if (r > g_r) { r = g_r; }
        _modify(g_l,g_r,l,r,val,1); }
    Item query(int l, int r) {
        return _query(g_l,g_r,l,r,1); }
};

} /* namespace STree */ 

#endif /* _LIB_STREE */
// Integer under mod

#ifndef _LIB_INTM
#define _LIB_INTM

namespace Intm {

class Intm {
private:
    static unsigned long long MOD;
    static unsigned long long k;

    unsigned long long a;

public:
    inline static void setMod(const unsigned long long _MOD) {
        MOD = _MOD;
        k = (unsigned long long)(-1) / _MOD; }
    inline static void getModSub(unsigned long long & a) {
        if (a>=MOD) a-=MOD; }
    inline static void getMod(unsigned long long & a) {
        a = a - (unsigned long long)((__uint128_t(k) * a) >> 64) * MOD; }
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
        getModSub(a);
        return (int)a; }
};


unsigned long long Intm::MOD;
unsigned long long Intm::k;

}

#endif /* _LIB_INTM */
#ifndef _LIB_SCANNER
#define _LIB_SCANNER 1

#include <stdio.h>
#include <stdlib.h>

class Scanner {
private:
    static const int BUFFER_SIZE = 10000;
    char buff[BUFFER_SIZE];
    int buffPos, buffLim;

public:
    Scanner () { 
        buffLim = fread(buff, 1, BUFFER_SIZE, stdin);
        buffPos = 0;
    }

private:
    inline void flushBuff() {
        buffLim = fread(buff, 1, BUFFER_SIZE, stdin);
        if (buffLim==0) {
            buff[buffLim++] = '\n';
        }
        buffPos = 0; 
    }

    inline bool isWS(char t) {
        return t==' ' || t=='\n';
    }

    inline bool isDig(char t) {
        return t>='0' && t<='9'; 
    }

    void nextPos() {
        buffPos++;
        if (buffPos == buffLim) {
            flushBuff();
        }
    }

#define getChar() buff[buffPos]

public:
    inline char getchar() {
        char ch=getChar();
        nextPos();
        return ch; 
    }

    inline void next(char* s) {
        while ( isWS(getChar()) ) {
            nextPos(); 
        }
        while ( !isWS(getChar()) ) {
            *s = getChar(); s++;
            nextPos();
        }
        *s = '\0';
    }

    inline void nextLine(char* s) {
        while ( getChar()!='\n' ) {
            nextPos();
        }
        if ( getChar()=='\n' ) {
            nextPos();
        }
        while ( getChar() != '\n' ) {
            *s = getChar(); s++;
            buffPos++;
        }
        *s = '\0';
    }

    inline int nextInt() {
        while ( !isDig(getChar()) ) {
            nextPos();
        }
        int sign = (getChar() == '-') ? nextPos(),-1 : 1;
        int res = 0;
        while (isDig(getChar())) {
            res = res*10 + getChar()-'0';
            nextPos();
        }
        return res * sign; 
    }

    inline double nextDouble() {
        while ( isWS(getChar()) ) {
            nextPos();
        }
        int sign = (getChar() == '-') ? nextPos(),-1 : 1;
        double res = 0;
        while (isDig(getChar())) {
            res = res * 10 + getChar()-'0';
            nextPos();
        }
        if (getChar() == '.') {
            nextPos();
            double ep = 1;
            while (isDig(getChar())) {
                ep *= 0.1;
                res += ep * (getChar()-'0');
                nextPos();
            }
        }
        return sign * res;
    }

    inline char nextChar() {
        while (isWS(getChar())) nextPos();
        char res = getChar(); nextPos();
        return res;
    }

#undef getChar
};
Scanner sc;
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
#define repe(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)

typedef pair < int , int > pr; 
typedef pair < pr  , int > prr; 
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); } 
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); } 
void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } } 
bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }
#define L first
#define R second

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#define ses(a) std::cout << #a << "=" << a << " " 
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#define ses(a)
#endif

#ifndef CUSTOM_MAIN

void preInit();
void init(); 
void solve(); 

int32_t main(){ 
preInit();

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
while(1) {
    try {init(); } 
    catch(bool t) {return 0;} 
    solve();
}
#else
init(); solve(); 
#endif /* MULTIPLE_TEST_CASES_WITHOUT_T  */

#endif /* MULTIPLE_TEST_CASES_WITH_T */
    return 0;
}

#endif /* CUSTOM_MAIN */

// my code begins here


const int MOD = 998244353;
const int N = 200005;
int n, q;
int a[N];
struct Query { int t,l,r; } qs[N];


void preInit() {
    Intm::Intm::setMod( MOD );
}

void init() {
    n = sc.nextInt(); q = sc.nextInt();
    rep (i,n) a[i] = sc.nextInt();
    rep (i,q) { 
        int t=sc.nextInt(), l=sc.nextInt()-1, r=sc.nextInt()-1;
        qs[i] = {t,l,r}; }
}

namespace BF {
    typedef Intm::Intm Int;
    const int N = 5005;
    Int _a[N];
    bool init() {
        return 1;
        return n <= 5000; }
    void main() {
        rep (i,n) { _a[i] = Int(a[i]); }
        rep (i,q) {
            if (qs[i].t == 1) {
                repi (j, qs[i].l, qs[i].r) { _a[j] *= _a[j]; } }
            else {
                Int ans(0);
                repi (j, qs[i].l, qs[i].r) { ans += _a[j]; } 
                printf(IN, static_cast<int>( ans )); } } }
}

namespace LR1 {
    const int N = 200005;
    bool init() {
        int nMatch = count_if( qs, qs+q, [](Query a) { return a.t==1 && a.l!=a.r; });
        return nMatch == 0; }
    void main() {
        STree::STree < N, STree::NodeSum > T;
        T.setLR(0,n-1);
        rep (i,n) { T.modify(i,i,a[i]); }
        rep (i,q) {
            if (qs[i].t == 1) {
                int _p = T.query(qs[i].l,qs[i].l).val;
                int _u = (1LL * _p * _p) % MOD;
                T.modify(qs[i].l, qs[i].l, _u-_p); }
            else { printf( "%lld\n",  T.query(qs[i].l, qs[i].r).val % MOD ); } } }
}

namespace LR2 {
    const int N = 200005;
    typedef Intm::Intm Int;
    Int _a[N];
    bool init() {
        int nMatch = count_if( qs, qs+q, [](Query a) { return a.t==2 && a.l!=a.r; });
        return nMatch == 0; }
    void main() {
        STree::STree < N, STree::NodeSum > T;
        T.setLR(0,n-1);
        rep (i,q) {
            if (qs[i].t == 1) { T.modify(qs[i].l, qs[i].r, 1); }
            else {
                int t = T.query(qs[i].l, qs[i].l).val;
                T.modify(qs[i].l, qs[i].l, -t); 
                _a[qs[i].l] = _a[qs[i].l].pow(t); 
                printf(IN, static_cast<int>( _a[qs[i].l] )); } } }
}

void solve() {
    if (BF::init()) { BF::main(); }
    else if (LR1::init()) { LR1::main(); }
    else if (LR2::init()) { LR2::main(); }
    else { puts("wh ak ioi"); }
}
