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

const int N = 1000000000;
const int P = 100005;

struct Pt {
    int x,y;
    bool operator < (const Pt& B) const { 
        return x==B.x ? y<B.y : x<B.x; }
    bool operator == (const Pt& B) const {
        return x==B.x && y==B.y; }
};

struct Node {
    Node *l,*r;
    int v;
    
    void pushUp() {
        if (l==NULL&&r==NULL) return;
        v = 0;
        if (l!=NULL) checkMin(v,l->v);
        if (r!=NULL) checkMin(v,r->v); }
};

struct STree {
    Node* R;
    STree() { R = NULL; }

    void modify(int l, int r, int p, int v, Node* &u) {
        if (u == NULL) u = new Node();
        if (l == r) { u->v = v; return; }
        int mid = (l+r) / 2;
        if (p <= mid) modify(l,mid,p,v,u->l);
        else          modify(mid+1,r,p,v,u->r); 
        u->pushUp(); }

    int query(int l, int r, int sl, int sr, Node* u) {
        if (u == NULL) return 0;
        if (sl <= l && sr >= r) return u->v;
        int mid = (l+r)/2;
        int ans = 0;
        if (sl <= mid) checkMin(ans, query(l,mid,sl,sr,u->l));
        if (sr > mid) checkMin(ans, query(mid+1,r,sl,sr,u->r)); 
        return ans; }

    void add(Pt u, int val) {
        modify(0,N,u.y,val - u.x - u.y,R); }

    int get(Pt u) {
        return query(0,N,0,u.y,R) + u.x + u.y; }
};

const Pt START_TAG = {N+5,N+5};
const Pt O = {0,0};
Pt T;

Pt st[P], ed[P];
vector < Pt > pts;
map < Pt , int > dis;
int n,p;

STree ps;

inline Pt read() { int u,v; scanf(II,&u,&v); return (Pt){u,v}; }

void BREAK() {
    while (1) {puts("MYY AK IOI");} }

map < Pt,Pt > fr;

void init() {
    scanf(II,&n,&p); T = {n,n};
    rep (i,p) { st[i] = read(); ed[i] = read(); }
    rep (i,p) { fr[ ed[i] ] = st[i]; }
    rep (i,p) pts.push_back(st[i]);
    rep (i,p) pts.push_back(ed[i]);
    pts.push_back(T);
    sort(pts.begin(),pts.end());
}

void solve() {
    for (Pt u: pts) {
        int br = ps.get(u);
        ses(u.x);ses(u.y);see(br);
        dis[u] = br;
        if (fr.count(u)) {
            int lg = dis[fr[u]];
            if (lg < br) dis[u] = lg; } 
        ps.add(u, dis[u]); }
    printf(IN,dis[T]); 
}

