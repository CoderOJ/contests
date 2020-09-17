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

const int N = 200005;
vector <int> e[N]; int n, m, s;
int w[N], trace[N], line[N];

void init() {
    scanf(II,&n,&m);
    repa (i,n) scanf(I,&w[i]);
    rep (i,m) {
        int u, v; scanf(II,&u,&v);
        e[u].push_back(v); e[v].push_back(u); }
    scanf(I,&s);
}

vector <int> st; int dep[N]; int vis[N];
int dfs(int u, int f) {
    ses(u);see(f);
    dep[u]= dep[f]+1; vis[u]=1; line[u]=w[u]; st.push_back(u);
    int minDep=dep[u], minId=u;
    for (int v: e[u]) {
        if (v==f) continue;
        if (vis[v]) { if (dep[v]<minDep) { minDep=dep[v]; minId=v; } }
        else {
            int anc=dfs(v,u);
            if (dep[anc]<minDep) { minDep=dep[anc]; minId=anc; }
            trace[u] |= trace[v];
            checkMax(line[u], w[u]+line[v]); } }
    if (minId==u) {
        if (st.back()==u) { st.pop_back(); return minId; }
        while (st.back()!=u) { trace[st.back()]=1; st.pop_back(); }
        trace[st.back()]=1; st.pop_back(); }
    return minId; }


void solve() {
    dfs(s,0);
    int ans=0, maxLine=0;
    repa (i,n) {
        if (trace[i]) ans+=w[i];
        else checkMax(maxLine, line[i]); }
    printf(IN,ans+maxLine);
}

