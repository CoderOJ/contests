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

struct Node;
vector <Node> trans;

inline int eval(char* s) {
    int res=0; while(*s) { res *=10; res += (*s-'0'); s++; } 
    return res; }

map <Node,int> mem;

const int N = 15;
struct Node {
    int8_t a[N];
    Node() { memset(a,0,sizeof(a)); }

    int8_t  operator [] (int idx) const { return a[idx]; }
    int8_t& operator [] (int idx) { return a[idx]; }
    bool operator < (const Node& B) const {
        rep (i,N) if (a[i] != B[i]) return a[i]<B[i];
        return 0; }
    void log() {
        rep (i,N) printf("%d ",a[i]); 
        puts(""); }
    Node sub (const Node& B) const {
        Node C; rep (i,N) C.a[i] = a[i] - B.a[i]; 
        return C; }
    bool valid(const Node& B) const {
        rep (i,N) if (a[i]<B[i]) return 0;
        return 1; }
    inline int count() {
        int res=0; rep (i,N) res += (a[i]>0);
        return res; }
    int step() {
        if (mem.count(*this)) return mem[*this];
        int ans = count();
        if (ans == 0) return ans;
        for (auto i: trans) {
            if (!valid(i)) continue;
            Node C = sub(i);
            checkMin(ans, C.step()+1); }
        log();see(ans);
        return mem[*this]=ans; }
    void scan(int n) {
        rep (i,n) {
            char s[5]; int t; scanf("%s%d",s,&t);
            if (strcmp(s,"01") == 0) t=13; 
            else if (strcmp(s,"02") == 0) t=14;
            else t = eval(s) -1; 
            if (t<13) t=(t-2+13)%13;
            a[t]++; } }
};

int T,n;

void P0() { Node A; A[13] = A[14] = 1; trans.push_back(A); }
void P1() { rpi (c,2,4) rep (i,N-2) { Node A; A[i]=c; trans.push_back(A); } }
void P2(int n2) { rep (i,13) rep (j,N) if (i!=j) { Node A; A[i]=3; A[j]=n2; trans.push_back(A); } }
void P4(int n, int c) { rep (t,12) rep (s,t) if (t-s+1>=n) { Node A; repi (i,s,t) { A[i] = c; } trans.push_back(A); } }
void P5() { rep (i,13) rep (j,N) rep (k,N) if (i!=j && i!=k) { Node A; A[i]+=4; A[j]++; A[k]++; trans.push_back(A); } }

void init() {
    scanf(II,&T,&n);
    P0(); P1(); P2(1); P2(2); P4(5,1); P4(3,2); P4(2,3); P5(); 
    for (Node i: trans) {
        i.log(); }
}

void solve() {
    while (T--) {
        Node A; A.scan(n);
        printf(IN,A.step()); }
}

