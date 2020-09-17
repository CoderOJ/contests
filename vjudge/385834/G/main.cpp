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

const int N = 1005;
vector <pr> e[N]; int n,m;

void init() {
    scanf(II,&n,&m); 
    rep (i,m) { int u,v,w; scanf(III,&u,&v,&w); e[u].push_back({v,w}); e[v].push_back({u,w}); }
}

int dis[N][2], cnt[N][2];
inline int update(int u, int s, int t) {
    int res=1;
    if (s < dis[u][0]) {
        dis[u][1]=dis[u][0]; dis[u][0]=s; cnt[u][1]=cnt[u][0]; cnt[u][0]=t; }
    else if (s == dis[u][0]) { cnt[u][0]+=t; }
    else {
        if (s < dis[u][1]) { dis[u][1]=s; cnt[u][1]=t; }
        else if (s==dis[u][1]) { cnt[u][1]+=t; } 
        else { res=0; } }
    return res; }
void solve() {
    memset(dis,0x3f,sizeof(dis)); memset(cnt,0,sizeof(cnt));
    int S,F; scanf(II,&S,&F); dis[S][0]=0; cnt[S][0]=1;
    set<pr> que; que.insert({S,0});
    while (!que.empty()) {
        pr pos=*que.begin(); que.erase(que.begin()); int u=pos.R, w=pos.L;
        if (w > dis[u][1]) continue;
        repe (i, e[u]) {
            int v=e[u][i].L, uw=e[u][i].R;
            if (update(v,w+uw,cnt[u][ w==dis[u][1] ])) {
                que.insert({w+uw,v}); } } }
    printf(IN, cnt[F][0] + (dis[F][1]-dis[F][0] == 1) ? cnt[F][1] : 0);
}

