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
typedef pair < int , int > pr;
typedef pair < pr  , int > prr;
#define L first
#define R second

const int N = 1505;
double dp[N][N]; // dp[i][j] represents the possibility that Alice will win when Alice has a score of i and bob has j
int n;

void init() {
    scanf("%d",&n);
}

void solve() {
    rep (i,N) dp[n][i] = 1;
    for (int i=n;i>=0;i--) for(int j=n - 1;j>=0;j--) { // i & j are for indexing dp[i][j]
        for (int r = 1;r <= 1024;r <<= 1) { //represents Alice choose to attempt on a task whose point is r
            int gn = min(n , i + r);
            // Alice has a possibility of (1 / (r + r)) to get the score , and ( (r + r - 1) / (r + r) ) get nothing
            // Bob always have a possibility of 0.5 to get 1 point . and 0.5 get nothing
            // needn't to consider a kind of possibilities that Alice and Bob all get noting
            // so , 1 / (r + r + 1) is for dp[gn][j] , 1 / (r + r + 1) for dp[gn][j + 1] , (r + r - 1) / (r + r + 1) for dp[i][j + 1];
            double gpos = (dp[gn][j] + dp[gn][j + 1] + (double)(r + r - 1) * dp[i][j + 1]) / (r + r + 1);
            dp[i][j] = max(dp[i][j] , gpos);
        }
    }
    printf("%.6lf\n",dp[0][0]);
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    return 0;
}
