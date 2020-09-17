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

#ifndef _LIB_STREE
#define _LIB_STREE 1

#include <algorithm>

struct Node {
    long long val, tg;
    Node (long long val=0, long long tg=0) : val(val), tg(tg) {}
    void update(int _val) {
        val += _val; tg += _val; }
    void pushUp (Node a, Node b) {
        val = std::max(a.val, b.val); }
    void pushDown (Node &a, Node &b) {
        a.val += tg; b.val += tg;
        a.tg += tg; b.tg += tg;
        tg = 0; }
};

template <int N, class Item=Node> class STree {
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
        ses(l);ses(r);see(val);
        if (r > g_r) { r = g_r; }
        _modify(g_l,g_r,l,r,val,1); }
    Item query(int l, int r) {
        return _query(g_l,g_r,l,r,1); }
};

#endif /* _LIB_STREE */

const int N = 20005;
struct Point { int x,y,l; };
Point p[N];
int n,w,h;

void init() {
    scanf(III,&n,&w,&h); 
    rep (i,n) scanf(III,&p[i].x, &p[i].y, &p[i].l);
}

inline int _rank(vector <int>& a, int p) {
    return lower_bound(a.begin(),a.end(),p)-a.begin(); }

void solve() {
    vector <int> xs;
    rep (i,n) { xs.push_back(p[i].x); xs.push_back(p[i].x+w-1); }
    sort(xs.begin(), xs.end()); xs.erase(unique(xs.begin(),xs.end()),xs.end());
    sort(p,p+n, [](Point a, Point b) { return a.y < b.y; });

    STree<N> st;
    st.setLR(0,N-1);
    int low=0;
    long long ans = 0;
    rep (upp,n) {
        st.modify(_rank(xs,p[upp].x), _rank(xs,p[upp].x+w-1), p[upp].l);
        while (low<n && p[upp].y-p[low].y >= h) {
            st.modify(_rank(xs,p[low].x), _rank(xs,p[low].x+w-1), -p[low].l);
            low++; }
        checkMax(ans, st.query(0,N-1).val); }
    printf("%lld\n",ans);
}

