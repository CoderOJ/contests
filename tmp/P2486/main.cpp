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

LCT T;
int n,q;

void init() {
    scanf(II,&n,&q);
    repa (i,n) { int c; scanf(I,&c); T.update(i,i,c); }
    rep (i,n-1) { int u,v; scanf(II,&u,&v); T.link(u,v); }
}

void solve() {
    while (q--) {
        char opt[2]; int u,v,c;
        scanf("%s",opt);
        if (opt[0]=='C') {
            scanf(III,&u,&v,&c);
            T.update(u,v,c); }
        else if (opt[0]=='Q') {
            scanf(II,&u,&v); 
            printf(IN, T.query(u,v)); } }
}

