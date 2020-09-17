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

const int NN = 1024;
const int MOD = 998244353;
struct Matrix {
    static int N;
    int a[NN][NN];
    Matrix () {
        memset(a,0,sizeof(a)); } 
    void toI() { rep (i,N) a[i][i]=1; }
    Matrix mul2(Matrix& B) const {
        Matrix C;
        rep (i,N) rep (k,N) (C.a[i][0] += (long long)a[k][0]*B.a[i][k]%MOD) %= MOD;
        return C; }
    Matrix mul(Matrix& B) const {
        Matrix C=mul2(B);
        rep (j,N-1) rep (i,N) C.a[(i+1)%N][j+1]=C.a[i][j]; 
        return C; }   
    Matrix pow(int e) const {
        Matrix B=*this, A; A.toI();
        while (e) {
            if (e&1) A=A.mul(B);
            B=B.mul(B); e>>=1; }
        return A; } };

int a[NN]; int n,l,m,k;
pr xy[NN];
int Matrix::N;

void init() {
    scanf(III,&n,&l,&m); Matrix::N=n;
    rep (i,m) scanf(II,&xy[i].L, &xy[i].R);
    scanf(I,&k);
}
void solve() {
    Matrix A,C; 
    rep (i,k) {
        int a; scanf(I,&a); a%=n;
        rep (j,n) { C.a[ (j+a)%n ][j] ++;  } }
    A.a[0][0]=1;
    xy[m]={l,1}; m++;
    sort(xy, xy+m); 
    repb (i,m-1,1) xy[i].L -= xy[i-1].L;
    rep (i,m) {
        see(i);
        Matrix T=C.pow(xy[i].L);
        A = A.mul2( T );
        A.a[xy[i].R][0] = 0; }
    printf(IN, A.a[0][0]);
}

