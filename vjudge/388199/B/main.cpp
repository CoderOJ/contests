#define CUSTOM_MAIN
#include <iostream>
#include <cstdio>
using namespace std;

void init();
void solve();
#ifndef CUSTOM_MAIN
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

struct RotateRootException {} ;
struct LCT {
    struct Node {
        Node *s[2], *f;
        int val, sum, rev;
        Node () { s[0]=s[1]=f=NULL; val=sum=0; }
        bool isRoot() {
            if (f==NULL) return 1;
            return this!=f->s[0] && this!=f->s[1]; }
        void pushUp() {
            sum=val; rep (i,2) if (s[i]) sum += s[i]->sum; }
        void pushRev() {
            swap(s[0],s[1]); rev^=1; }
        void pushDown() {
            if (rev==1) rep (i,2) if (s[i]) s[i]->pushRev();
            rev=0; }
        void push() {
            if (!isRoot()) f->push();
            pushDown(); }
        int getSon() {
            if (f==NULL) throw;
            return this == f->s[1]; }
        void rotate() {
            if (isRoot()) throw RotateRootException();
            bool ss=getSon(); 
            Node *uu=this, *ff=f, *aa=ff->f, *cc=s[!ss];
            if (!ff->isRoot()) aa->s[ ff->getSon() ] = uu;
            ff->f = uu; ff->s[ss] = cc;
            uu->f = aa; uu->s[!ss] = ff;
            if (cc!=NULL) cc->f = ff;
            ff->pushUp(); pushUp(); }
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
        void update(int _val) {
            splay(); val=_val; pushUp(); }
        void makeRoot() {
            access(); splay(); pushRev(); }
    };       

    Node p[N];
    void init(int n) {
        repa (i,n*2) p[i]=Node(); }
    void update(int u, int val) {
        p[u].update(val); }
    void link(int u, int v) {
        p[u].makeRoot();
        p[u].f = &p[v]; }
    void split(Node* u, Node* v) {
        u->makeRoot(); v->access(); v->splay(); }
    int query(int u, int v) {
        split(&p[u], &p[v]);
        return p[v].sum; }
};

LCT T;

int relay[N];
int n, m, cnt;

void init() {
    if (scanf(II,&n,&m)==EOF) throw (bool)(1);
//    scanf(II,&n,&m);
    repa (i,n-1) relay[i]=0;
    T.init(n);
    cnt=n+1;
    repa (i,n) T.update(i,0);
    repa (i,n-1) {
        int u,v,w; scanf(III,&u,&v,&w); relay[i]=cnt;
        T.link(u,cnt); T.link(cnt,v); T.update(cnt,w); cnt++; }
}

void solve() {
    while (m--) {
        int opt,u,v; scanf(III,&opt,&u,&v);
        if (opt==0) { T.update(relay[u], v); }
        else if (opt==1) { printf(IN, T.query(u,v)); } 
    }
}

signed main() {
    while (1) {
        try {
            init(); }
        catch (...) {
            return 0; }
        solve(); }
}
