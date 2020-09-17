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
typedef pair < int , int > pr; 
typedef pair < pr  , int > prr; 
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); } 
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); } 
void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } } 
bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }
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








// my code begins here

const int MOD = 1000000007;

template <int N> struct Node { 
    int a[N]; int tg;
    Node () { memset(a,0,sizeof(a)); tg = 1; } 
    void pushMul(int w) {
        rep (i,N) (a[i] *= w) %= MOD; 
        (tg *= w) %= MOD; }
    void pushUp(Node <N> l, Node <N> r) {
        rep (i,N) a[i] = ( l.a[i] + r.a[i] ) % MOD; }
    void pushDown(Node <N> &l, Node <N> &r) {
        l.pushMul(tg); r.pushMul(tg); 
        tg = 1; }
    int& operator [] (const int id) { return a[id]; }
};

template <int N, int M> struct STree {
protected:
    Node<M> a[N*4];
    int l,r;

    void _modify(int l, int r, int p, Node<M> val, int u) {
        if (l==r) { a[u] = val; return; }
        a[u].pushDown(a[u+u],a[u+u+1]);
        int m = l+(r-l)/2;
        if (p <= m) _modify(l,m,p,val,u+u); 
        else        _modify(m+1,r,p,val,u+u+1); 
        a[u].pushUp(a[u+u], a[u+u+1]);  }
    void _multiple(int l, int r, int sl, int sr, int val, int u) {
        if (sl <= l && r <= sr) {
            a[u].pushMul(val); return; }
        a[u].pushDown(a[u+u],a[u+u+1]);
        int m = l+(r-l)/2;
        if (sl <= m)    _multiple(l,m,sl,sr,val,u+u);
        if (sr > m)     _multiple(m+1,r,sl,sr,val,u+u+1); 
        a[u].pushUp(a[u+u], a[u+u+1]); }
    Node<M> _query(int l, int r, int sl, int sr, int u) {
        if (sl <= l && r <= sr) {
            return a[u]; }
        a[u].pushDown(a[u+u],a[u+u+1]);
        int m = l+(r-l)/2;
        if (sr <= m)    return _query(l,m,sl,sr,u+u);
        else if (sl>m)  return _query(m+1,r,sl,sr,u+u+1);
        Node <M> ans; ans.pushUp( _query(l,m,sl,sr,u+u) , _query(m+1,r,sl,sr,u+u+1) );
        return ans; }
public:
    void setLR (int _l, int _r) { l=_l; r=_r; }
    void modify(int p, Node<M> val) {
        _modify(l,r,p,val,1); }
    void multiple (int sl, int sr, int t) {
        if (sl > r) { return; }
        _multiple(l,r,sl,sr,t,1); } 
    Node<M> query (int sl, int sr) {
        return _query(l,r,sl,sr,1); } 
};

const int N = 200005;
const int K = 11;
int S[K+5][K+5];
pr inter[N];
int n,k;
STree <N,K> st;
typedef Node<K> Arr;

void init() {
    scanf(II,&n,&k);
    S[0][0] = 1;
    repa (i,K) {
        S[i][0]=0; S[i][i] = 1;
        repa (j,K-1) { S[i][j] = (S[i-1][j-1] + S[i-1][j]*j) % MOD; } }
    rep (i,n) { int l, r; scanf(II,&l,&r); inter[i] = {l,r}; }
    sort(inter,inter+n);
}

void solve() {
    st.setLR(0,2*n);
    Arr tmp; tmp.a[0] = 1;
    st.modify(0,tmp);
    rep (i,n) {
        int l=inter[i].L, r=inter[i].R;
        st.multiple(r+1,2*n,2); 
        Arr f = st.query(0,l-1); repb (i,k,1) (f[i] += f[i-1]) %= MOD;
        f.pushUp(f,st.query(l,r)); 
        st.modify(r,f); }
    tmp = st.query(0,2*n);
    int ans = 0; int fac = 1;
    rep (i,K+1) {
        (ans += fac * S[k][i]%MOD * tmp[i]%MOD) %= MOD;
        fac *= (i+1); }
    printf(IN,ans);
}
