/*
####### #     # ###  #####
   #    #     #  #  #     #
   #    #     #  #  #
   #    #######  #   #####
   #    #     #  #        #
   #    #     #  #  #     #
   #    #     # ###  #####

###  #####
 #  #     #
 #  #
 #   #####
 #        #
 #  #     #
###  #####

   #
  # #
 #   #
#     #
#######
#     #
#     #

 #####  #     # ### #######
#     # #     #  #     #
#       #     #  #     #
 #####  #######  #     #
      # #     #  #     #
#     # #     #  #     #
 #####  #     # ###    #

######  ######  ####### ######  #       ####### #     #
#     # #     # #     # #     # #       #       ##   ##
#     # #     # #     # #     # #       #       # # # #
######  ######  #     # ######  #       #####   #  #  #
#       #   #   #     # #     # #       #       #     #
#       #    #  #     # #     # #       #       #     #
#       #     # ####### ######  ####### ####### #     #

 _______  _    _  _____   _____ 
|__   __|| |  | ||_   _| / ____|
   | |   | |__| |  | |  | (___  
   | |   |  __  |  | |   \___ \ 
   | |   | |  | | _| |_  ____) |
   |_|   |_|  |_||_____||_____/ 
                                
                                
 _____   _____ 
|_   _| / ____|
  | |  | (___  
  | |   \___ \ 
 _| |_  ____) |
|_____||_____/ 
               
               
          
    /\    
   /  \   
  / /\ \  
 / ____ \ 
/_/    \_\
          
          
  _____  _    _  _____  _______ 
 / ____|| |  | ||_   _||__   __|
| (___  | |__| |  | |     | |   
 \___ \ |  __  |  | |     | |   
 ____) || |  | | _| |_    | |   
|_____/ |_|  |_||_____|   |_|   
                                
                                
 _____   _____    ____   ____   _       ______  __  __ 
|  __ \ |  __ \  / __ \ |  _ \ | |     |  ____||  \/  |
| |__) || |__) || |  | || |_) || |     | |__   | \  / |
|  ___/ |  _  / | |  | ||  _ < | |     |  __|  | |\/| |
| |     | | \ \ | |__| || |_) || |____ | |____ | |  | |
|_|     |_|  \_\ \____/ |____/ |______||______||_|  |_|
                                                       
                                                       


*/
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

const double pi = acos(-1);
typedef pair <double,double> Pt;
typedef pair <double,double> Line;
typedef pair <double,double> Vec;

const int N = 100005;
double pv; Pt w[N]; double r[N]; Vec v[N]; int n;

void init() {
    scanf(I,&n); scanf("%lf",&pv);
    rep (i,n) scanf("%lf%lf%lf%lf%lf", &w[i].Lm, &w[i].R, &r[i], &v[i].L, &v[i].R);
}

double dis(Pt a, Pt b) {
    return sqrt( (a.L-b.L)*(a.L-b.L) + (a.R-b.R)*(a.R-b.R) ); }

namespace AC {
    double VecToAngle(Vec a) {
        if (a.L==0 && a.R==0) return 0;
        if (a.L==0) return a.R>0 ? pi/2 : -pi/2;
        return atan( a.R/a.L ); }
    
    double ans[N];    
}

namespace Pv0 {
    bool check() { return pv==0; } 
    void main() {
        
}

void solve() {
    if (Pv0::check()) Pv0::main();
}

