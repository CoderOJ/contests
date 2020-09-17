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

void init() {
     
}

struct OOMap {
    map <string, string> a,b;
    bool _jury(map <string,string> &a, string _a, string _b) {
        if (!a.count(_a)) return 1;
        return a[_a] == _b; }
    bool jury(string _a, string _b) {
        return _jury(a,_a,_b) && _jury(b,_b,_a); }
    void add(string _a, string _b) {
        a[_a] = _b;
        b[_b] = _a; }
};

void solve() {
    OOMap conflict;

    string a,b; cin >> a >> b;
    vector < pair < string , string > > ans;
    pair < string , string > pos = {"",""};
    int len = (int)a.size();
    rep (i,len) {
        pos = { pos.L+a[i], pos.R+b[i] };
        if (conflict.jury(pos.L,pos.R)) {
            ans.push_back(pos); 
            conflict.add(pos.L,pos.R); 
            pos = {"",""}; } }
    ans.back().L += pos.L;
    ans.back().R += pos.R;
    cout << ans.size() << endl;
    for (auto a: ans) {
        cout << a.L << ' '; }
   cout << endl;
    for (auto a: ans) {
        cout << a.R << ' '; }
    cout << endl;
}
