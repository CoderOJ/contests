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

const int N = 50005;

struct Point {
    int x, y;
    Point (int x=0, int y=0) : x(x), y(y) {}
    bool    operator <  (const Point B) const   { return   y*B.x < x*B.y;    }
    bool    operator >  (const Point B) const   { return   y*B.x > x*B.y;    }
    bool    operator <= (const Point B) const   { return   y*B.x <= x*B.y;   }
    bool    operator >= (const Point B) const   { return   y*B.x >= x*B.y;   }
    Point   operator +  (const Point B) const   { return   {x+B.x, y+B.y};   }
    Point   operator -  (const Point B) const   { return   {x-B.x, y-B.y};   }
    void log () const {
        printf("%lld/%lld ",y,x); }
};

Point slope(Point a, Point b) { 
    Point res = {b.x-a.x, b.y-a.y}; 
    if (res.x < 0) { res.x = -res.x; res.y = -res.y; }
    return res; }
struct PStack {
    Point a[N];
    int l,r;
    PStack () {
        l = r = 0; }
    void push (const Point u) {
        while (r > l && u.x <= a[r-1].x) { r--; }
        while ( r > l+1  && slope(a[r-2],a[r-1]) <= slope(a[r-1],u) ) { r--; }
        a[r++] = u; }
    Point query(const Point s) {
        while (l<r-1 && slope(a[l],a[l+1]) > s) { l++; }
        return a[l]; }
};
struct PStack2 {
    Point a[N];
    int l,r;
    PStack2 () {
        l = r = 0; }
    void push (const Point u) {
        while (r > l && u.x >= a[r-1].x) { r--; }
        while ( r > l+1 && slope(a[r-1],a[r-2]) <= slope(a[r-1],u) ) { r--; }
        a[r++] = u; }
    Point query(const Point s) {
        while (l<r-1 && slope(a[l],a[l+1]) > s) { l++; }
//        ses(l);ses(r);a[l].log();a[l+1].log();slope(a[l],a[l+1]).log();see("");
        return a[l]; }
};


int n;
Point p[N];

void preInit() {
    n = sc.nextInt();
    rep (i,n) { int x=sc.nextInt(), y=sc.nextInt(); p[i] = {y,x}; }
    sort(p,p+n);
}

Point preMax[N], sufMin[N];

void init() {
//    rep (i,n) { p[i].log(); } see("");
    {
        PStack pre;
        Point sum;
        rep (i,n) sum = sum + p[i];
        rep (i,n-1) {
            pre.push(p[i]); sum = sum - p[i];
            preMax[i+1] = pre.query(sum); }
    }
    {
        PStack2 suf;
        Point sum;
        repb (i,n-1,1) {
            suf.push(p[i]); sum = sum + p[i];
            sufMin[i] = suf.query(sum);  }
    }
}

bool cmp(Point a, Point b, Point s) {
    return a.y*s.x - a.x*s.y > b.y*s.x - b.x*s.y; }

void solve() {
    vector <int> ans;
    Point sum; rep (i,n) sum = sum + p[i];
    repa (i,n-1) { 
        sum = sum - p[i-1];
//        sum.log();
//        preMax[i].log(); sufMin[i].log();see("");
        if (cmp(preMax[i],sufMin[i],sum)) { ans.push_back(i); } }
    printf(IN,(int)ans.size());
    for (int v : ans) { printf(IN,v); }
}
