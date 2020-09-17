#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
typedef pair < int , int > pr; typedef pair < pr  , int > prr; template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); } template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); } class Scanner{ private: istream& ist;public: Scanner(istream& in):ist(in){} string next(){ string r; ist >> r; return r; } string nextLine(){ string r; getline(ist,r); return r; } int nextInt(){ int r; ist >> r; return r; } double nextDouble(){ double r; ist >> r; return r; } char nextChar(){ char r; ist>>r; return r;} }; Scanner sc(cin); void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } } bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }

const int INF = 0x3f3f3f3f;
const int N = 200005;

template <class T> void extend(vector <T> &a, vector <T> b) {
    for (T u: b) a.push_back(u); }

struct STGraph {
    vector <pr> e[N*4];
    
    int sp[N*4];
    int dis[N*4];

    STGraph() { 
        memset(sp,0,sizeof(sp)); }

    void init(int l, int r, int u=1) {
        if (l==r) { return; }
        e[u+u].push_back( pr(u,0) );
        e[u+u+1].push_back( pr(u,0) );
        int mid = (l+r)/2; 
        init(l,mid,u+u); init(mid+1,r,u+u+1); }

    vector <int> getReturn;
    void _get(int l, int r, int sl, int sr, int u=1) {
        if (sl > sr) { return; }
        if (sl <= l && sr >= r) { getReturn.push_back(u); return; }
        int mid = (l+r)/2; vector <int> ans;
        if (sl <= mid) _get(l,mid,sl,sr,u+u);
        if (sr > mid) _get(mid+1,r,sl,sr,u+u+1);
        return;  }   
    vector <int> get(int l, int r, int sl, int sr, int u=1) {
        getReturn.clear();
        _get(l,r,sl,sr,u); 
        return getReturn; }

    void addEdge(int ul, int ur, int v, int w, int n) {
        vector <int> us = get(0,n-1,ul,ur); 
        for (int u: us) e[u].push_back({v,1}); }

    void SP(int n) {
        memset(dis,INF,sizeof(dis));
        priority_queue <pr, vector<pr>, greater<pr>> que;
        rep (i,n*4) if (sp[i]) {
            dis[i] = 0; que.push({0,i}); }
        while (!que.empty()) {
            pr pos = que.top(); que.pop();
            int u = pos.R , uw = pos.L;
            //ses(u);see(uw);
            if (dis[u] != uw) continue;
            for (pr _v: e[u]) {
                int v = _v.L, vw = uw + _v.R;
                if (checkMin(dis[v],vw)) {
                    que.push( {vw,v} ); } } } }
};

struct Pie { int L,R,id; };

STGraph e;
int n, m;
Pie a[N];

void init() {
    scanf(II,&n,&m);
    rep (i,n) { int x,y; scanf(II,&x,&y); a[i] = {x,y,i}; }
    rep (i,n) { int x,y; scanf(II,&x,&y); a[n+i] = {y,x,n+i}; }
    sort (a, a+n, [](Pie a, Pie b) { return a.L < b.L; });
    sort (a+n, a+n+n, [](Pie a, Pie b) { return a.L < b.L; });
}

int ans[N];
int to[N];

void solve() {
    e.init(0,n+n-1);
    rep (i,n*2) to[i] = e.get(0,n*2-1,i,i)[0];
    see("pass get");
    rep (i,n) {
        int l = lower_bound(a+n,a+n+n, (Pie){a[i].R,0,0}, [](Pie a, Pie b){return a.L<b.L;}) -a;
        int r = upper_bound(a+n,a+n+n, (Pie){a[i].R+m,0,0}, [](Pie a, Pie b){return a.L<b.L;}) -a-1;
        e.addEdge(l,r,to[i],1,n*2); }
    repi (i,n,n+n-1) {
        int l = lower_bound(a,a+n, (Pie){a[i].R,0,0}, [](Pie a, Pie b){return a.L<b.L;}) -a;
        int r = upper_bound(a,a+n, (Pie){a[i].R+m,0,0}, [](Pie a, Pie b){return a.L<b.L;}) -a-1;
        e.addEdge(l,r,to[i],1,n*2); }
    see("pass build");
    rep (i,n*2) if (a[i].R == 0) e.sp[ to[i] ] = 1;
    e.SP(n*2);
    rep (i,n) ans[a[i].id] = e.dis[ to[i] ];
    rep (i,n) printf(IN, ans[i] >= INF ? -1 : ans[i]+1);
}

