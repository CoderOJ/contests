#define MULTIPLE_TEST_CASES_WITH_T
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
#ifndef __LOCALE__
    freopen("surreal.in","r",stdin);
    freopen("surreal.out","w",stdout);
#endif
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

const int N = 2000005;
struct Tree {
    int n;
    vector <pr> v;
    
    void scan() {
        scanf(I,&n);
        rep (i,n) {
            int l,r; scanf(II,&l,&r); l--; r--;
            v.push_back( pr(l,r) ); } }
    bool isChain() {
        rep (i,n) if (v[i].L!=-1 && v[i].R!=-1) return 0;
        return 1; }        
    vector <int> toLR() {
        vector <int> res;
        int u=0;
        while (v[u].L!=-1 || v[u].R!=-1) {
            res.push_back(v[u].L==-1);
            u = ( v[u].L==-1 ? v[u].R : v[u].L ); }
        return res; }
    void log() {
        see(n);
        rep (i,n) { ses(v[i].L); see(v[i].R); } }
};

struct Trie {
    struct Node {
        Node *s[2];
        int tg;

        Node() { s[0]=s[1]=NULL; tg=0; } 
    };

    Node p[N];
    int cnt;

    Trie () {
        cnt=0;
        p[cnt++] = Node(); }

    void insert(vector <int> lr) {
        for (int i: lr) ses(i); see("");
        Node* u=&p[0];
        for (int i: lr) {
            if (u->s[i]==NULL) u->s[i] = &p[cnt++];
            u = u->s[i]; }
        u->tg=1; }

    bool jury(Node *u) {
        if (u->tg == 1) return 1;
        if (u->s[0] == NULL || u->s[1] == NULL) return 0;
        return jury(u->s[0]) && jury(u->s[1]); }
};

void init() {
    see("init_pass");
}

void solve() {
    int n; scanf(I,&n);
    Trie t;
    rep (i,n) {
        Tree a; a.scan();
        if (a.isChain()) {
            see(i);
            a.log();
            t.insert(a.toLR()); } }
    puts( t.jury(&t.p[0]) ? "Almost Complete" : "No" );
}

