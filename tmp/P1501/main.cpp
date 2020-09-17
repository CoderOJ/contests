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

const int MOD = 51061;
const int N = 100005;
struct LCT {
    struct Node {
        Node *s[2], *f;
        int siz, val, tot, mul, add, rev;
        Node () { s[0]=s[1]=f=NULL; siz=val=tot=add=rev=0; mul=1; }

        bool isRoot() {
            if (f==NULL) return 1;
            return f->s[0]!=this && f->s[1]!=this; }
        int getSon() {
            return this == f->s[1]; }
        void pushUp() {
            siz = 1;   rep (i,2) if (s[i]) siz+=s[i]->siz; 
            tot = val; rep (i,2) if (s[i]) (tot+=s[i]->tot)%=MOD; }
        void pushRev() {
            rev^=1; swap(s[0],s[1]); }
        void pushMul(int u) {
            (val*=u) %=MOD; (tot*=u) %= MOD; 
            (mul*=u) %=MOD; (add*=u) %= MOD; }
        void pushAdd(int u) {
            (val+=u) %=MOD; (tot+=u*siz) %=MOD;
            (add+=u) %=MOD; }
        void pushDown() {
            if (mul != 1) { rep (i,2) if (s[i]) s[i]->pushMul(mul); }
            if (add != 0) { rep (i,2) if (s[i]) s[i]->pushAdd(add); }
            if (rev) { rep (i,2) if (s[i]) s[i]->pushRev(); }
            rev = add = 0; mul = 1; }
        void push() {
            if (!isRoot()) f->push();
            pushDown(); }
        void rotate() {
            int ss = getSon();
            Node *uu=this, *ff=f, *aa=f->f, *cc=s[!ss];
            if (!ff->isRoot()) { aa->s[ ff->getSon() ] = uu; }
            ff->f = uu; ff->s[ss] = cc;
            uu->f = aa; uu->s[!ss] = ff;
            if (cc!=NULL) cc->f = ff; 
            ff->pushUp(); pushUp(); }
        void _splay() {
            if (isRoot()) return; 
            if (f->isRoot()) { rotate(); return; }
            ( f->getSon() == getSon() ? f : this ) -> rotate(); rotate();
            _splay(); }
        Node* splay() {
            push(); _splay(); return this; }
        void access() {
            Node *uu=this, *vv=NULL;
            while (uu!=NULL) {
                uu->splay(); uu->s[1] = vv; uu->pushUp(); 
                vv=uu; uu=uu->f; } }
        void makeRoot() {
            access(); splay(); pushRev(); }
        Node* straight(int ss) {
            Node* u=this; while(u->s[ss]!=NULL) { u=u->s[ss]; } return u->splay(); }
        Node* findRoot() {
            access(); splay(); 
            return straight(0); }
    };

    Node p[N];

    void link(int u, int v) {
        p[u].makeRoot(); p[u].splay(); p[u].f = &p[v]; }
    void cut(int u, int v) {
        p[u].makeRoot(); p[v].access(); p[v].splay(); 
        p[v].s[0] = p[u].f = NULL; p[v].pushUp(); }
    void split(int u, int v) {
        p[u].makeRoot(); p[v].access(); p[v].splay(); }
    int query(int u, int v) {
        split(u,v); return p[v].tot; }
};

LCT T;
int n,q;

void init() {
    scanf(II,&n,&q);
    repa (i,n) T.p[i].pushAdd(1); 
    rep (i,n-1) { int u,v; scanf(II,&u,&v); T.link(u,v); }
}

void solve() {
    while (q--) {
        char opt[2]; scanf("%s",opt);
        if (opt[0] == '+') { 
            int u,v,c; scanf(III,&u,&v,&c); T.split(u,v); T.p[v].pushAdd(c); }
        else if (opt[0] == '-') {
            int u1,v1,u2,v2; scanf(IIII,&u1,&v1,&u2,&v2);
            T.cut(u1,v1); T.link(u2,v2); }
        else if (opt[0] == '*') {
            int u,v,c; scanf(III,&u,&v,&c); T.split(u,v); T.p[v].pushMul(c); }
        else if (opt[0] == '/') {
            int u,v; scanf(II,&u,&v); printf(IN,T.query(u,v)); } }
}

