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
typedef pair < int , int > pr; 
typedef pair < pr  , int > prr; 
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); } 
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); } 
void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } } 
bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }
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








// my code begins here

const int N = 100005;
struct Dsu {
    int p[N];
    Dsu () { rep (i,N) p[i] = i; }
    int get(int u) { return u==p[u] ? u : p[u]=get(p[u]); }
    void merge(int u, int v) {
        p[ get(v) ]=get(u); }
};

Dsu st;

int n,k,q;
struct Inter {
    int l,r,i; };

vector <int> oks;
int ok[N];
Inter qs[N];
vector <int> bel[N];
vector <Inter> bans;

Inter minMax(vector <int> u) {
    sort(u.begin(), u.end());
    return {u[0], u.back(), 0}; }

void init() {
    scanf(II,&n,&k); 
    rep (i,k) {
        int u,v; scanf(II,&u,&v);
        if (st.get(u) == st.get(v)) {
            oks.push_back(u); }
        st.merge(u,v); }
    scanf(I,&q);
    rep (i,q) {
        int l,r; scanf(II,&l,&r);  
        qs[i] = {l,r,i}; }
    for (int u: oks) { ok[st.get(u)] = 1; }
    repa (i,n) bel[ st.get(i) ].push_back(i);
    repa (i,n) if (bel[i].size() != 0 && ok[i]==0) bans.push_back(minMax(bel[i]));
}

int ans[N];

void solve() {
    sort(bans.begin(), bans.end(), [](Inter a, Inter b) { return a.r < b.r; });
    sort(qs,qs+q,                  [](Inter a, Inter b) { return a.r < b.r; });
    int bansId = 0, maxL = -1;
    rep (i,q) {
        while (bansId<(int)bans.size() && bans[bansId].r <= qs[i].r) {
            checkMax(maxL, bans[bansId].l);
            bansId++; }
        ans[qs[i].i] = (qs[i].l > maxL); }
    rep (i,q) puts(ans[i] ? "Yes" : "No");
}
