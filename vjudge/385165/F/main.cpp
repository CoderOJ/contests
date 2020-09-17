#pragma GCC optimize(3)
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

typedef vector<double> Pt;
typedef vector<double> Vec;
const int N = 205;
const double eps = 1e-3;
Pt p[N]; int n, k; Pt o;

void init() {
    scanf(II,&n,&k);
    rep (i,n) { double x,y; cin >> x >> y; p[i]={x,y}; }
}

double dis(Pt a, Pt b) {
    return sqrt( (a[0]-b[0])*(a[0]-b[0]) + (a[1]-b[1])*(a[1]-b[1]) ); }
bool cmp(Pt a, Pt b) {
    return dis(o,a) > dis(o,b); }

Pt operator += (Pt& a, Pt b) {
    a[0]+= b[0]; a[1]+=b[1]; return a; }
Pt operator - (Pt a, Pt b) {
    return {a[0]-b[0], a[1]-b[1]}; }
Pt operator / (Pt a, double b) {
    return {a[0]/b, a[1]/b}; }

double get(double x, double y) {
    o = {x,y};
    sort(p, p+n, cmp);
    double sum=0; rep (i,k) sum+=dis(o,p[i]); 
    return sum; }

double get(double x) {
    double l=-1000, r=1000;
    while (r-l > eps) {
        double m1=l+(r-l)/3;
        double m2=l+(r-l)/3*2;
        double a1=get(x,m1);
        double a2=get(x,m2);
        if (a1 < a2) r=m2;
        else l=m1; }
    return get(x,l); }

void solve() {
    double l=-1000, r=1000;
    while (r-l > eps) {
        ses(l);see(r);
        double m1=l+(r-l)/3;
        double m2=l+(r-l)/3*2;
        double a1=get(m1);
        double a2=get(m2);
        if (a1 < a2) r=m2;
        else l=m1; }
    printf("%.10lf\n",get(l));
}

