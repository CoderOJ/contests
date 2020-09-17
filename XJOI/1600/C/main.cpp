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

int n,m;

void init() {
    scanf(II,&n,&m); 
}

namespace P1 {
    const int N = 1000005;

    struct UMap {
        int fst[N], nxt[N], key[N], val[N];
        int cnt;

        UMap() {
            memset(fst,-1,sizeof(fst));
            memset(nxt,-1,sizeof(nxt));
            cnt=0; }

        int query(int u) {
            int cur = u % N;
            for (int i=fst[cur]; i!=-1; i=nxt[i]) {
                if (key[i] == u) { return val[i]; } }
            return 0; }

        void suc(int u) {
            int cur = u % N;
            for (int i=fst[cur]; i!=-1; i=nxt[i]) {
                if (key[i] == u) { val[i]++; return; } }
            nxt[cnt] = fst[cur]; fst[cur] = cnt; key[cnt] = u; val[cnt] = 1; cnt++; }
    };

    bool jury() { return n<=1000000; }
    void main() {
        UMap cnt;
        int ans=0;
        rep (i,n) {
            int u = (1LL*i*i)%m;
            ans += cnt.query(u);
            cnt.suc(u); }
        printf(IN,ans); } 
}

namespace P2 {
    const int N = 1000005;
    int cnt[N];

    bool jury() { return m<=1000000; }
    void main() {
        memset(cnt,0,sizeof(cnt));
        rep (i,m) {
            cnt[ 1LL*i*i%m ] += (n-i-1)/m+1; }
        int ans=0;
        rep (i,m) { ans += (cnt[i]-1)*cnt[i]/2; }
        printf(IN,ans); }
}

void solve() {
    if (P1::jury()) P1::main(); 
    else if (P2::jury()) P2::main();
}

