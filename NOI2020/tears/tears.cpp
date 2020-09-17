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

const int N = 100005;
const int M = 200005;
typedef pair<int,int> Pt;
Pt p[N]; Pt ml[M], mr[M];
int n,m;

bool le(Pt &a, Pt &b) {
    return a.L <= b.L && a.R <= b.R; }

void init() {
#ifndef __LOCALE__
    freopen("tears.in","r",stdin);
    freopen("tears.out","w",stdout);    
#endif
    scanf(II,&n,&m);
    rep (i,n) {
        int a; scanf(I,&a); 
        p[i] = {i+1,a}; }
    rep (i,m) {
        int r1,r2,c1,c2; scanf(IIII,&r1,&r2,&c1,&c2);
        ml[i] = {r1,c1}; mr[i] = {r2,c2}; }
}

struct FTree {
    int a[N];
    FTree() { memset(a,0,sizeof(a)); }
    inline int low(int u) { return u&(-u); }
    void modify(int p, int u) {
        while (p<N) {
            a[p]+=u; p+=low(p); } }
    int query(int p) {
        int res=0;
        while (p) {
            res += a[p]; p-=low(p); }
        return res; }
};

namespace Bf {
    bool isIn[N];
    long long calc() {
        FTree cnt;
        long long ans=0;
        rep (i,n) {
            if (!isIn[i]) continue;
            ans += cnt.query(p[i].R);
            cnt.modify(p[i].R,1); }
        return ans; }
    void main() {
        rep (i,m) {
            rep (j,n) isIn[j] = le(ml[i],p[j]) && le(p[j],mr[i]);
            printf("%lld\n",calc()); } }
}

namespace A {
    bool jury() {
        rep (i,m) { if (ml[i].R!=1 || mr[i].R!=n) return 0; } 
        return 1; }

    struct Querys {
        int l, r, sl, id;
        void set() { sl = (int)(sqrt(l)); }
        bool operator < (const Querys& B) {
            return sl==B.sl ? r<B.r : sl<B.sl; } };

    int r_add(FTree& cnt, int val) {
        int res = cnt.query(val);
        cnt.modify(val,1);
        return res; }
    int r_del(FTree& cnt, int val) {
        cnt.modify(val,-1);
        int res = cnt.query(val);
        return res; }
    int l_add(FTree& cnt, int val) {
        int res = cnt.query(n) - cnt.query(val);
        cnt.modify(val,1);
        return res; }
    int l_del(FTree& cnt, int val) {
        cnt.modify(val,-1);
        int res = cnt.query(n) - cnt.query(val);
        return res; }

    long long ans[M];
    void main() {
        vector <Querys> q;
        rep (i,m) q.push_back( (Querys){ml[i].L-1,mr[i].L-1,0,i} );
        rep (i,m) q[i].set();
        sort(q.begin(), q.end());
        int l=1,r=0; long long pos=0;
        FTree cnt;
        rep (i,m) {
            while (l>q[i].l) { l--; pos += l_add(cnt,p[l].R); }
            while (r<q[i].r) { r++; pos += r_add(cnt,p[r].R); }
            while (l<q[i].l) { pos -= l_del(cnt,p[l].R); l++; }
            while (r>q[i].r) { pos -= r_del(cnt,p[r].R); r--; } 
            ans[ q[i].id ] = pos; }
        rep (i,m) printf("%lld\n",ans[i]); }
}

void solve() {
    if (A::jury()) A::main();
    else Bf::main();    
}

