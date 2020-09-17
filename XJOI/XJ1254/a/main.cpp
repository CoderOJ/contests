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
typedef pair < int , int > pr;
typedef pair < pr  , int > prr;
#define L first
#define R second
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); }
class Scanner{ private: istream& ist;public: Scanner(istream& in):ist(in){} string next(){ string r; ist >> r; return r; } string nextLine(){ string r; getline(ist,r); return r; } int nextInt(){ int r; ist >> r; return r; } double nextDouble(){ double r; ist >> r; return r; }};
Scanner sc(cin);
 
const int N = 1005;
int c[N], w[N];
int n;
 
void init() {
    scanf(I,&n);
    rep (i,n) scanf(I,&c[i]);
    rep (i,n) scanf(I,&w[i]);
}
 
int jury(vector < int > s, vector < int > v) { // to determine what's the answer in [u,n) with avaliable ws in v(sorted)
    int res = 0; // the returning value, the maxial
}
 
void solve() {
    rep (i,n) { //determine each
        sort (w, w+n-i); // avaliable ws are in this scope (otherwise is used)
        int mx = 0, mxr = 0; // mx: max times win, mxr: place (max)w[?] when win for the max times
        vector < int > s; repi (j,i+1,n-1) s.push_back(c[j]); // used to store the cs left
        sort(s.begin(), s.end(), [](int x, int y) { return x > y; }); // sort to non-increasing for greedy
        rep (j,n-i) { // try each (j represents the index)
            vector < int > v; rep (k,n-i) if (k != j) if (k != j) v.push_back(w[k]); // avaliable ws left after choosing w[j]
            int nans = jury(s, v) + (w[j] > c[i]); // the new ans = (ans_after_this) + (ans_this);
            if (nans >= mx) { // update the ans (>= because we need to find the max possible j)
                mx = nans;
                mxr = w[j];
            }
        }
    }
}
 
#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    return 0;
}
