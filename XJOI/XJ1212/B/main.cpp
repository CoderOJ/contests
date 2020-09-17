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
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)
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

const int N = 256;
int G[N][N];
int deg[N];
char tmp[N]; 
char res[N * N];
int n;

void dfs(int i) { 
    rep (j,N) {
        if(G[i][j]) {
            G[i][j] = G[j][i] = 0;
            dfs(j);
        }
    }
    res[n--] = i;
}

void init() {
    scanf(I, &n);
    rep (i,n) {
        scanf("%s", tmp);
        G[ (int)tmp[0] ][ (int)tmp[1] ] = G[ (int)tmp[1] ][ (int)tmp[0] ] = 1;
        deg[ (int)tmp[0] ]++;
        deg[ (int)tmp[1] ]++;
    }
}

void solve() {
    char fir = 0, cnt = 0;
    rep (i,N) if(deg[i] & 1) {
        cnt++;
        if(!fir) fir = i;
    }
    if(!fir) rep(i,N) if(deg[i]) { fir = i; break; }
    if(cnt && cnt != 2) { puts("No Solution"); return; }
    dfs(fir);
    puts(res);
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    return 0;
}
