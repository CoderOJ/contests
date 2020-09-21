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
#include <stack>
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

struct Ln {
    int x,y;
    bool operator <= (const Ln &v) const {
        return 1ll*x*v.y <= 1ll*v.x*y; }
    bool operator >= (const Ln &v) const {
        return v <= *this; }
    bool operator == (const Ln B) const {
        return x==B.x && y==B.y; }
};

const int N = 200005;
const int B = 20;
Ln NCR = {0x3f3f3f3f,1};
int n;

int h[N],ord[N];
int dw[N][B], up[N][B];

void preInit() {
    n = sc.nextInt();
    repa (i,n) h[i] = sc.nextInt();
    repa (i,n) ord[i] = i;
}

Ln _cross(Ln x, Ln y) {
    int dx = x.x-y.x, dy = x.y-y.y;
    if (dy < 0) { dy=-dy; dx=-dx; }
    if (dx < 0) { return NCR; }
    int g = __gcd(dy,dx);
    return {dy/g,dx/g}; }
Ln cross (int x, int y) {
    return _cross({x,h[x]},{y,h[y]}); }

void print(Ln u) {
    if (u == NCR) {                                 /* answer does not exist */
        puts("-1"); }
    else {                                          /* exist */
        // we know that u is the return value of `cross`
        // so it's guaranteed $gcd(u.x,u.y)$ = $1$
        printf("%d/%d\n",u.x,u.y); } }

void init() {
    sort(ord+1,ord+n+1,[](int a, int b) { return h[a]<h[b]; }); 
    {                                                                   /* go down*/
        int st[N]; int top=0;
        repb (_i,n,1) { int i = ord[_i];
            while (
                (top>0 && cross(i,st[top-1]) == NCR) ||
                (top>1 && cross(i,st[top-2]) <= cross(i,st[top-1])) ) 
            {
                top--; } 
            if (top != 0) { dw[i][0] = st[top-1]; }
            st[top++] = i; }
        rep (b,B-1) { repa (i,n) { dw[i][b+1] = dw[ dw[i][b] ][b]; } }
    }
    {                                                                   /* go up*/
        int st[N]; int top=0;
        repi (_i,1,n) { int i = ord[_i];
            while (
                (top>0 && cross(i,st[top-1]) == NCR) ||
                (top>1 && cross(i,st[top-2]) <= cross(i,st[top-1])) ) 
            {
                top--; } 
            if (top != 0) { up[i][0] = st[top-1]; }
            st[top++] = i; }
        rep (b,B-1) { repa (i,n) { up[i][b+1] = up[ up[i][b] ][b]; } }
    }
}

// is up next valiable
// to judge whether we can go to $y$ if we go along $x$ to $next x$
// `u` is the cross of $x$ and $next x$
// the bool expression:
//      (h[x]-h[y])/(x-y) ?<= u.x/u.y
//      is to compare the x-ais value (to judge if can transfer)
//  
//  `dwNexVal` is in the same way.
bool upNexVal(int x, int y) {
    if (up[x][0] == 0) return 0;
    Ln u = cross(up[x][0],x);
    Ln v = cross(x,y);
    return u <= v; }
bool dwNexVal(int x, int y) {
    if (dw[x][0] == 0) return 0;
    Ln u = cross(dw[x][0],x);
    Ln v = cross(x,y);
    return u <= v; }

void solve() {
    repa (i,n) {
        int q = sc.nextInt(); int j = i;
        if (h[q] > h[i] && upNexVal(i,q)) 
        {                                           /* to go up (and guaranteed can reach) */
            repb (b,B-1,0)  {
                if (    up[j][b] != 0 &&            /* has next */
                        upNexVal(up[j][b], q)) {    /* will not exceed */
                    j = up[j][b]; }                 /* transfer */ 
            }
            j = up[j][0];
        }
        if (h[q] < h[i] && dwNexVal(i,q)) 
        {
            repb (b,B-1,0) {
                if (    dw[j][b] != 0 &&
                        dwNexVal(dw[j][b], q)) {
                    j = dw[j][b]; }
            }
            j = dw[j][0];
        }
        // now if the ans is not -1,
        // $next(j)$ is $q$
        //
        // and if not
        // j is still i
        print(cross(j,q));
    }
}
