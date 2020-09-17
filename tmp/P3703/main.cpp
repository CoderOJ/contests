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

void init();
void solve();
int main(){
try { 

#ifndef CUSTOM_MAIN
#ifdef MULTIPLE_TEST_CASES_WITH_T

int T; scanf("%d",&T); while(T--) {init(); solve();}

#else
#ifdef MULTIPLE_TEST_CASES_WITHOUT_T

while(1) {try{init(); } catch(bool t){return 0;} solve(); }

#else

init(); solve();

#endif
#endif
#endif

} catch (const char* s) { return 0; }
    return 0;
}

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

struct LCT {
    struct Node {
        Node *s[2], *f;
        Node() { s[0]=s[1]=f=NULL; }

        bool isRoot() {
            if (f==NULL) return 1;
            return this!=f->s[0] && this!=f->s[1]; }
        int getSon() {
            return f->s[1] == this; }
        void rotate() {
            int ss= getSon();
            Node *uu=this, *ff=f, *aa=ff->f, *cc=s[!ss];
            if (!ff->isRoot()) aa->s[ f->getSon() ] = uu;
            ff->f = uu; ff->s[ss] = cc;
            uu->f = aa; uu->s[!ss] = ff;
            if (cc!=NULL) cc->f = ff; }
        void splay() {
            if (isRoot()) return;
            if (f->isRoot()) { rotate(); return; }
            ( getSon() == f->getSon() ? f : this ) -> rotate(); rotate();
            splay(); }
        Node* findRoot() {
            Node *u=this; splay();
            while (u->s[0] != NULL) u=u->s[0];
            u->splay(); 
            return u; }
    };

    Node p[N];
};

struct STree {
    struct Node {
        int val, tag; };
    
    Node p[N*4];

    inline int ls(int u) { return u+u; }
    inline int rs(int u) { return u+u+1; }
    void pushUp(int u) {
        p[u].val = max( p[ls(u)].val , p[rs(u)].val ); }
    void update(int u, int val) {
        p[u].val+=val; p[u].tag+=val; }
    void pushDown(int u) {
        int& tag=p[u].tag;
        p[ ls(u) ].val+=tag; p[ ls(u) ].tag+=tag;
        p[ rs(u) ].val+=tag; p[ rs(u) ].tag+=tag;
        tag=0; }
    void modify(int l, int r, int sl, int sr, int val, int u=1) {
        if (u==1) { ses(sl);ses(sr); see(val);}
        if (sl<=l && sr>=r) { update(u,val); return; }
        pushDown(u);
        int mid= (l+r)/2;
        if (sl <= mid) { modify(l,mid,  sl,sr,val,ls(u)); }
        if (sr >  mid) { modify(mid+1,r,sl,sr,val,rs(u)); }
        pushUp(u); }
    int query(int l, int r, int sl, int sr, int u=1) {
//        ses(l);ses(r);ses(sl);ses(sr);see(u);
        if (sl<=l && sr>=r) { return p[u].val; }
        pushDown(u);
        int mid= (l+r)/2, ans=0;
        if (sl <= mid) { checkMax(ans, query(l,mid,  sl,sr,ls(u))); }
        if (sr >  mid) { checkMax(ans, query(mid+1,r,sl,sr,rs(u))); }
        return ans; }
};

STree S;
LCT T;

const int B = 20;
vector <int> e[N];
int n,m;

int dep[N], fa[N][B], ld[N], rd[N], cnt;

void dfs(int u, int f) {
    fa[u][0]=f;
    rep (i,B-1) fa[u][i+1] = fa[ fa[u][i] ][i];
    ld[u]=++cnt; dep[u]= dep[f]+1;
    for (int v: e[u]) {
        if (v==f) continue;
        T.p[v].f = &T.p[u];
        dfs(v,u); }
    rd[u]=cnt; }

int go(int u, int dd) {
    repb (i,19,0) { if (dd >= (1<<i)) { u=fa[u][i]; dd-= (1<<i); } }
    return u; }
int lca(int u, int v) {
    if (dep[u]<dep[v]) swap(u,v);
    u= go(u,dep[u]-dep[v]);
    repb(i,19,0) { if (fa[u][i] != fa[v][i]) { u=fa[u][i]; v=fa[v][i]; } }
    if (u==v) return u;
    return fa[u][0]; }
    
void init() {
    scanf(II,&n,&m); 
    rep (i,n-1) { int u,v; scanf(II,&u,&v); e[u].push_back(v); e[v].push_back(u); }
    cnt=0; dfs(1,0);
    repa (i,n) S.modify(1,n,ld[i],ld[i],dep[i]);
}

inline int getId(LCT::Node *u) { return u-T.p; }
void access(int u) {
    see(u);
    LCT::Node *uu=&T.p[u], *ss=NULL;
    while (uu) {
        uu->splay(); 
        ses(uu->f-T.p); see(uu-T.p);
        if (uu->s[1] != NULL) {
            LCT::Node *cut=uu->s[1]; uu->s[1]=NULL;
            int v = getId(cut->findRoot());
            see(v);
            S.modify(1,n,ld[v],rd[v],1); }
        if (ss != NULL) {
            int v = getId(ss->findRoot());
            ss->splay();
            S.modify(1,n,ld[v],rd[v],-1); }
        uu->s[1] = ss; 
        ss=uu; uu=uu->f; }
}

inline int get(int u) {
    if (u==0) return 0;
    return S.query(1,n,u,u); }
void solve() {
    while (m--) {
        int opt; scanf(I,&opt); 
        if (opt==1) {
            int u; scanf(I,&u);
            access(u); }
        else if (opt==2) {
            int u,v; scanf(II,&u,&v);
            printf(IN, get(ld[u])+get(ld[v])-2*get(ld[lca(u,v)])+1); }
        else if (opt==3) {
            int u; scanf(I,&u); 
            printf(IN, S.query(1,n,ld[u],rd[u])); }
    }
}

