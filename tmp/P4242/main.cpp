#include <iostream>
#include <cstdio>
using namespace std; 
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
#ifndef _LIB_ARRAY
#define _LIB_ARRAY 1

template <int N, class T> class Array {
protected:
    T a[N]; int upt[N];
    int t;

public:
    Array () {
        t=0; for (int i=0;i<N;i++) upt[i]=0; }
    T& operator [] (const int i) {
        if (upt[i] < t) {
            a[i] = T(); upt[i] = t; }
        return a[i]; }
    void clear() {
        t++; }
};

#endif /* _LIB_ARRAY */



const int N = 100005;

struct LCT {
    struct Node {
        Node *s[2], *f;
        int c, lc, rc, tot;
        int rev, tag;
        Node() { s[0]=s[1]=f=NULL; c=lc=rc=tot=rev=0; }

        bool isRoot() {
            if (f==NULL) return 1;
            return this!=f->s[0] && this!=f->s[1]; }
        int getSon() {
            return f->s[1] == this; }
        void pushUp() {
            if (s[0]==NULL && s[1]==NULL) { lc=rc=c; tot=1; }
            else if (s[0]==NULL) { lc=c; rc=s[1]->rc; tot=s[1]->tot + (c!=s[1]->lc); }
            else if (s[1]==NULL) { lc=s[0]->lc; rc=c; tot=s[0]->tot + (c!=s[0]->rc); }
            else {
                lc=s[0]->lc; rc=s[1]->rc;
                tot = s[0]->tot + s[1]->tot + 1 - (s[0]->rc==c) - (c==s[1]->lc) ; } }
        void pushRev() {
            rev ^= 1; swap(s[0],s[1]); swap(lc,rc); }
        void pushTag(int nc) {
            tag=1; c=lc=rc=nc; tot=1; }
        void pushDown() {
            if (tag) { rep (i,2) if (s[i]!=NULL) { s[i]->pushTag(c); } }
            if (rev) { rep (i,2) if (s[i]!=NULL) { s[i]->pushRev(); } }
            tag = rev = 0; } 
        void push() {
            if (!isRoot()) f->push();
            pushDown(); }
        void rotate() {
            int ss = getSon();            
            Node *uu=this, *ff=f, *aa=ff->f, *cc = s[!ss];
            if (!ff->isRoot()) aa->s[ ff->getSon() ] = uu;
            ff->s[ss] = cc; ff->f = uu;
            uu->s[!ss] = ff; uu->f = aa;
            if (cc!=NULL) cc->f = ff;
            ff->pushUp(); uu->pushUp(); }
        void _splay() {
            if (isRoot()) return;
            if (f->isRoot()) { rotate(); return; }
            ( getSon() == f->getSon() ? f : this ) -> rotate(); rotate();
            _splay(); }
        void splay() {
            push(); _splay(); }
        void access() {
            Node *uu=this, *ss=NULL;
            while (uu!=NULL) {
                uu->splay(); uu->s[1]=ss; uu->pushUp(); 
                ss=uu; uu=uu->f; } }
        void makeRoot() {
            access(); splay(); pushRev(); }
    };

    Node p[N];

    void link(int u, int v) {
        p[u].makeRoot(); p[u].f=&p[v]; }
    void split(int u, int v) {
        p[u].makeRoot(); p[v].access(); p[v].splay(); }
    void update(int u, int v, int c) {
        split(u,v); p[v].pushTag(c); }
    int query(int u, int v) {
        split(u,v); return p[v].tot; }
};

struct Tree {
    int ef[N], en[N*2], ev[N*2], ec;
    Tree () { memset(ef,-1,sizeof(ef)); memset(en,-1,sizeof(en)); ec = 0; }
    void addEdge (int u, int v) {
        en[ec] = ef[u]; ef[u] = ec; ev[ec] = v; ec++;
        en[ec] = ef[v]; ef[v] = ec; ev[ec] = u; ec++; }
    void clear(int u) { ef[u] = -1; }
    void clearAll() { ec = 0; }
};

struct Tree1 : public Tree {
    int ew[N*2];
    void addEdge (int u, int v, int w) { w--;
        en[ec] = ef[u]; ef[u] = ec; ev[ec] = v; ew[ec] = w; ec++;
        en[ec] = ef[v]; ef[v] = ec; ev[ec] = u; ew[ec] = w; ec++; }
     
    int sz[N]; long long sum[N], ans[N];
    void clear(int u) { this->Tree::clear(u); sz[u] = 0; }
    void dfs0 (int u, int f) {
        sum[u] = 0; 
        for (int e=ef[u]; e!=-1; e=en[e]) if (ev[e] != f) {
            dfs0(ev[e], u); 
            sz[u] += sz[ev[e]]; sum[u] += 1LL*sz[ev[e]]*ew[e] + sum[ev[e]]; } }
    void dfs1 (int u, int f, long long ups) {
        ans[u] = ups + sum[u];
        for (int e=ef[u]; e!=-1; e=en[e]) if (ev[e] != f) {
            dfs1(ev[e], u, ups + 1LL*ew[e]*(sz[1]-sz[ev[e]]) + sum[u]-sum[ev[e]]-1LL*ew[e]*sz[ev[e]]); } }
} T1;

struct Tree0 : public Tree {
    static const int B = 20;
    LCT T; 
    int d[N], fa[N][B], dfn[N], dfnCnt;

    void addEdge(int u, int v) {
        this->Tree::addEdge(u,v); T.link(u,v); }
    void dfs(int u, int f) {
        dfn[u] = dfnCnt++; d[u] = d[f]+1;
        fa[u][0] = f; rep (i,B-1) { fa[u][i+1] = fa[ fa[u][i] ][i]; }
        for (int e=ef[u]; e!=-1; e=en[e]) if (ev[e] != f) {
            dfs(ev[e], u); } } 
    void init(int _n) {
        repa (i,_n) { int w; scanf(I,&w); T.update(i,i,w); }  }
    void pre() {
        dfnCnt=0; dfs(1,0);  }
    void up(int &u, int d) {
        repb (i,B-1,0) { if ((d>>i) & 1) { u = fa[u][i]; } } }
    int lca(int u, int v) {
        if (d[u] < d[v]) { swap(u,v); } up(u, d[u]-d[v]); 
        repb (i,B-1,0) { if (fa[u][i] != fa[v][i]) { u = fa[u][i]; v = fa[v][i]; }  }
        return u==v ? u : fa[u][0]; }
    
    int st[N], stTop;
    void VT (int u[], int n, Tree1 &Tg) {
        sort(u, u+n, [this](int a, int b) { return dfn[a]<dfn[b]; });
        stTop=0; if (u[0]!=1) { st[stTop++] = 1; } Tg.clearAll(); Tg.clear(1);
        rep (i,n) {
            while (stTop > 1) {
                int f=st[stTop-1], ff=st[stTop-2], l=lca(u[i],f); 
                if (l == f) { break; }
                else if (dfn[l] <= dfn[ff]) { Tg.addEdge(ff,f,T.query(ff,f)); stTop--; }
                else { Tg.clear(l); Tg.addEdge(l,f,T.query(l,f)); stTop--; st[stTop++] = l; break; } }
            Tg.clear(u[i]); st[stTop++] = u[i]; }
        while (stTop > 1) { int f = st[stTop-1], ff = st[stTop-2]; Tg.addEdge(f,ff,T.query(f,ff)); stTop--; } 
        rep (i,n) Tg.sz[u[i]] = 1; }
} T0;

int n,q;

void preInit() { } 
void init() {
    scanf(II,&n,&q); 
    T0.init(n); 
    rep (i,n-1) { int u,v; scanf(II,&u,&v); T0.addEdge(u,v); } 
    T0.pre(); }

int a[N], b[N], m;

void solve() {
    while (q--) {
        int opt; scanf(I,&opt);
        if (opt == 1) { int u,v,x; scanf(III,&u,&v,&x); T0.T.update(u,v,x); }
        else {
            scanf(I,&m); rep (i,m) { scanf(I,&a[i]); b[i]=a[i]; }
            T0.VT(a, m, T1);
            T1.dfs0(1,0); T1.dfs1(1,0,0);
            rep (i,m) { printf("%lld ", T1.ans[b[i]]+m); } puts(""); } }
}
