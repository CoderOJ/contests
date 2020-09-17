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

} catch (...) { return 0; }
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

struct Node {
    Node *l, *r;
    int sum;
    Node () { l=r=NULL; sum=0; }

    void pushUp() {
        sum=0; 
        if (l!=NULL) sum += l->sum;
        if (r!=NULL) sum += r->sum; }
};

Node pool[N*40]; 
int cnt;


Node* newNode() {
    return &pool[cnt++]; }

struct STree {
    Node* R;
    STree() { R=NULL; }

    void modify(int l, int r, int p, int v, Node* &u) {
        if (u == NULL) u = newNode();
        if (l == r) { u->sum+=v; return; }
        int m = (l+r)/2;
        if (p <= m) modify(l,m,p,v,u->l);
        else        modify(m+1,r,p,v,u->r);
        u->pushUp(); }

    Node* merge(int l, int r, Node* u, Node* v) {
        if (u == NULL) return v;
        if (v == NULL) return u;
        if (l == r) {
            u->sum += v->sum; 
            return u; }
        int mid = (l+r)/2;
        u->l = merge(l,mid,u->l,v->l);
        u->r = merge(mid+1,r,u->r,v->r);
        u->pushUp();
        return u; }

    int kth(int l, int r, int k, Node* u) {
        if (k > u->sum) {
            ses(l);ses(r);ses(u->sum);see(k);
            return 0; }
        if (l==r) return l;
        int mid = (l+r)/2;
        if (u->l == NULL) {
            return kth(mid+1,r,k,u->r); }
        else if (u->l->sum < k) {
            return kth(mid+1,r,k - u->l->sum,u->r); }
        else {
            return kth(l,mid,k,u->l); } }
};

struct Dsu {
    int p[N];
    Dsu() { rep (i,N) p[i] = i; }

    int get(int u) { return u==p[u] ? u : p[u] = get(p[u]); }
    void merge(int u, int v) { 
        p[ get(v) ] = p[ get(u) ]; }
};

STree st[N];
Dsu ds;
int n,m,q;
int toId[N];

void init() {
    cnt = 0;
    scanf(II,&n,&m);
    toId[0] = -1;
    repa (i,n) {
        int a; scanf(I,&a); 
        toId[a] = i;
        st[i].modify(1,n,a,1,st[i].R); }
    rep (i,m) {
        int u,v; scanf(II,&u,&v);
        int pu=ds.get(u) , pv=ds.get(v);
        if (pu == pv) continue;
        st[u].merge(1,n,st[pu].R,st[pv].R); ds.merge(pu,pv); }
}

void solve() {
    int q; scanf(I,&q);
    while (q--) {
        char opt; scanf(" %c ",&opt);
        if (opt == 'B') {
            int u,v; scanf(II,&u,&v);
            int pu=ds.get(u) , pv=ds.get(v);
            if (pu == pv) continue;
            st[pu].merge(1,n,st[pu].R,st[pv].R); ds.merge(pu,pv); }
        else if (opt == 'Q') {
            int u,k; scanf(II,&u,&k);
            int pu = ds.get(u);
            printf(IN, toId[ st[pu].kth(1,n,k,st[pu].R) ]); }
    }
}

