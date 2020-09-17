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

#define long long long
#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 

const int M = 50;
const int N = 1005;
int loc[M][N];
int cst[M][N];
int dp[M][N];
int n,m,k;

void init(){
    scanf("%d%d%d",&m,&n,&k) ;
    rep (i,m) rep (j,n) {
        scanf("%d",&loc[i][j]);
    }
    rep (i,m) rep (j,n) scanf("%d",&cst[i][j]);
    memset(dp,0x3f,sizeof(dp));
}

void solve() {
    rep (i,n) dp[0][i] = abs(k - loc[0][i]) + cst[0][i];
    repa (i,m - 1) rep (j,n) rep (k,n) {
        dp[i][j] = min(dp[i][j] , dp[i - 1][k] + abs(loc[i - 1][k] - loc[i][j]) + cst[i][j]);
    }
    int ans = 0x3f3f3f3f;
    rep (i,n) ans = min(ans,dp[m  - 1][i]);
    printf("%d\n",ans);
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--) {
        init();
        solve();
    }
    return 0;
}
