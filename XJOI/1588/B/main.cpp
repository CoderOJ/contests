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

const int INF=9223372036854775807;
int s,t,a,b;

void init() {
    scanf(IIII,&s,&t,&a,&b); 
}

inline bool willOver(int a, int b, int t) {
    return b/a < t; }
inline int lg(int a, int b) {
    if (a==0 && b!=0) return -1;
    if (a==1&&b!=1) return -1;
    int ans=0;
    if (b==0) return -1;
    while (b!=1) {
        if (b%a!=0) return -1;
        b/=a; ans++; }
    return ans; }

int calc(int s, int t, int ts, int a, int b) {
    ses(s);ses(t);ses(ts);ses(a);see(b);
    int ans=0;
    vector<int> devs; devs.push_back(1);
    int ps=1; rep (i,ts) { ps*=b; devs.push_back(ps); }
    int rem= (t-ps*s)/a;
    while (!devs.empty()) { 
        ses(rem); ses(devs.back()); ses(rem/devs.back()); see(rem%devs.back()); 
        ans+= rem/devs.back(); rem%=devs.back();
        devs.pop_back(); }
    see(ans);
    return ans; }

void solve() {
    if (s==t) { puts("0"); return; }
    if (s==0 && a==0) { puts("-1"); return; }
    if (t==0) {
        if (b==0) puts("1");
        else puts("-1");
        return; }

    int preAns=0;
    if (a==0) {
        if (t%s!=0) { puts("-1"); return; }
        int ans=lg(b,t/s);
        if (ans==-1) puts("-1");
        else printf(IN,ans); 
        return; }
    if (s==0) {
        if (t==0) { puts("0"); return; }
        else {
            if (a==0) { puts("-1"); return; }
            else { preAns=1; s=a; } } }
    if (preAns==1 && b==0) {
        if (t%a==0) { printf(IN,t/a); }
        else { puts("-1"); }
        return; }
    if (t<s) {
        if (b==0 && t%a == 0) { 
            if (preAns) { printf(IN, t/a); }
            else { printf(IN,t/a+1); } }
        else { puts("-1"); } 
        return; }
    if (b==0) {
        int ans=INF;
        if ((t-s) % a ==0) checkMin(ans,(t-s)/a);
        if ( t    % a ==0) checkMin(ans,t/a+1);
        if (ans==INF) puts("-1");
        else printf(IN,ans);
        return; }
    if (b==1) {
        if ((t-s)%a==0) { printf(IN,(t-s)/a+preAns); }
        else { puts("-1"); }
        return; }
    
    int ans=INF;

    int current=0;
    int us=s;
    while (1) {
        see(us);
        if ((t-us)%a == 0)  {
            checkMin(ans, current + calc(s,t,current,a,b)); }
        if (willOver(us,t,b)) break;
        current++; us*=b; }

    if (ans==INF) { puts("-1"); return; }
    printf(IN,ans+preAns);
}    

