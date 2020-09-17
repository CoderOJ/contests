#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
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

const int N = 300005;

struct STree {
    struct Node{
        Node *l, *r;
        int t;
        Node () : l(NULL), r(NULL), t(0) {}

        void pushUp() {}
    };

    static Node pool[N*60];
    static int cnt;
    static Node* newNode() {
        return &pool[cnt++]; }

    Node *R;
    STree () {
        R = NULL; }

    void modify(int l, int r, int p, int v, Node* &u) {
        if (u == NULL) u = newNode();
        if (l==r) { u->t += v; return; }
        int m = l+(r-l)/2;
        if (p <= m)     modify(l,m,p,v,u->l);
        else            modify(m+1,r,p,v,u->r);
        u->pushUp(); }

    Node* merge(int l, int r, Node* u, Node* v) {
        if (u == NULL) return v;
        if (v == NULL) return u;
        if (l == r) {
            u->t += v->t;
            return u; }
        int m = l+(r-l)/2;
        u->l = merge(l,m,u->l,v->l);
        u->r = merge(m+1,r,u->r,v->r);
        u->pushUp();
        return u; }

    int query(int l, int r, int p, Node* u) {
        if (p < l || p > r) return 0;
        if (u == NULL) return 0;
        if (l==r) return u->t;
        int m = l+(r-l)/2;
        if  (p <= m)    return query(l,m,p,u->l);
        else            return query(m+1,r,p,u->r); }
};

STree::Node STree::pool[N*60];
int STree::cnt = 0;
STree St[N];
STree St2[N];
vector <int> e[N];
int w[N];
int n,m;

const int B = 20;
int dep[N];
int fa[N][B];
void dfs(int u, int f) {
    dep[u] = dep[f]+1; fa[u][0] = f;
    rep (i,B-1) fa[u][i+1] = fa[ fa[u][i] ][i];
    for (int v: e[u]) if (v!=f) {
        dfs(v,u); } }
int lca(int u, int v) {
    if (dep[u] < dep[v]) { swap(u,v); }
    int del = dep[u]-dep[v]; 
    repb (i,B-1,0) if ((del>>i)&1) { u = fa[u][i]; }
    repb (i,B-1,0) if (fa[u][i] != fa[v][i]) {
        u = fa[u][i]; v = fa[v][i]; }
    return u==v ? u : fa[u][0]; }

int ans[N];

void init() {
    scanf(II,&n,&m);
    rep (i,n-1) { int u,v; scanf(II,&u,&v); e[u].push_back(v); e[v].push_back(u); }
    repa (i,n) scanf(I,&w[i]);
    dfs(1,0);
    rep (i,m) {
        int s,t; scanf(II,&s,&t); 
        int l = lca(s,t);
        St[s].modify(-n,n,dep[s],1,St[s].R);
        St[fa[l][0]].modify(-n,n,dep[s],-1,St[fa[l][0]].R);
        int arr = dep[s] + dep[t] - 2*dep[l];
        St2[t].modify(-n,n,arr-dep[t],1,St2[t].R);
        St2[fa[l][0]].modify(-n,n,arr-dep[t],-1,St2[fa[l][0]].R);
        if (dep[s] - dep[l] == w[l]) {
            ans[l]--; } }
}

void dfs2(int u, int f) {
    for (int v: e[u]) if (v!=f) {
        dfs2(v,u);
        St[u].R = St[u].merge(-n,n,St[u].R, St[v].R); 
        St2[u].R = St2[u].merge(-n,n,St2[u].R, St2[v].R); }
    ans[u] += St[u].query(-n,n,dep[u]+w[u],St[u].R); 
    ans[u] += St2[u].query(-n,n,w[u]-dep[u],St2[u].R); }

void solve() {
    dfs2(1,0);
    repa (i,n) printf("%d ", ans[i]);
}

