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

const int N = 100005;
vector <int> o[N]; int deg[N];
vector <int> e[N];
int n,m;

void init() {
    scanf(II,&n,&m);
    rep (i,m) {
        int n; scanf(I,&n);
        rep (j,n) { int a; scanf(I,&a); o[i].push_back(a); } }
}

vector <int> ans;

bool jury0(int m) {
    ans.clear();
    repa (i,n) { e[i].clear(); deg[i] = 0; }
    rep (i,m) {
        rep (j,(int)o[i].size()-1) { 
            e[o[i][j]].push_back(o[i][j+1]); 
            deg[ o[i][j+1] ]++; } }
    queue <int> st; repa (i,n) if (deg[i]==0) st.push(i);
    while (!st.empty()) {
        int u=st.front(); st.pop();
        ans.push_back(u);
        for (int v: e[u]) { 
            deg[v] --;
            if (deg[v] == 0) st.push(v); }  }
    return (int)ans.size() == n; } 

bool jury(int m) {
    ans.clear();
    repa (i,n) { e[i].clear(); deg[i] = 0; }
    rep (i,m) {
        rep (j,(int)o[i].size()-1) { 
            e[o[i][j]].push_back(o[i][j+1]); 
            deg[ o[i][j+1] ]++; } }
    priority_queue <int,vector<int>,greater<int>> st; repa (i,n) if (deg[i]==0) st.push(i);
    while (!st.empty()) {
        int u=st.top(); st.pop();
        ans.push_back(u);
        for (int v: e[u]) { 
            deg[v] --;
            if (deg[v] == 0) st.push(v); }  }
    return (int)ans.size() == n; } 

void solve() {
    int l=1, r=m;
    while (l<r) {
        int mid = (l+r+1)/2;
        if (jury0(mid)) l=mid;
        else r=mid-1; }
    jury(l);
    for (int u: ans) printf("%d ",u);
    puts("");
}

