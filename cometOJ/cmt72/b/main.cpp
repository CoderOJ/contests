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

const int N = 405;
const int M = 100005;
char m[N][N];
int fn[N][N];
int n, _m;
int l;
char o[M];

void init() {
    scanf(II,&n,&_m);
    rep (i,n) scanf("%s",m[i]);
    scanf("%s",o); l = strlen(o); 
}

void solve() {
    memset(fn,-1,sizeof(fn));
    int x, y;
    rep (i,n) rep (j,_m) if (m[i][j] == '@') { x=i, y=j; break; }
    m[x][y] = '.';
    fn[x][y] = 0;
    int len = 1;
    rep (i,l) {
        int ux=x, uy=y;
        char p = o[i];
        if (p == 'A') uy--; 
        if (p == 'D') uy++;
        if (p == 'W') ux--;
        if (p == 'S') ux++;
        if (ux < 0 || ux >= n || uy <0 || uy >= _m) { puts("GG"); return; }
        fn[ux][uy] = i+1;
        if (m[ux][uy] == 'o') len++; 
        m[ux][uy] = '.'; 
        x=ux; y=uy;
    }
    rep (i,n) rep (j,_m) if (l - fn[i][j] < len) m[i][j] = 'X';
    m[x][y] = '@';
    rep (i,n) printf("%s\n",m[i]); 
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    return 0;
}
