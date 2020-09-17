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

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
typedef pair < int , int > pr;
typedef pair < pr  , int > prr;
#define L first
#define R second

const int N = 40;
int dp[N][N][N][2];
// dp[i][j][k][l] means
// i bits , j bars , first bar has a width of k , begin with l(0 or 1)
int n,k,m;

void init(){
    scanf("%d%d%d",&n,&k,&m);
    dp[1][1][1][1] = dp[1][1][1][0] = 1; // though dp[1,1,1,0] is not allowed , there is still use of it
                                         // (not ONLY as the inital statement)
    for (int i=2;i<=n;i++) {
        repa (j,k) repa (k,m) rep(l,2) {
            if (k == 1) repa (p,m) dp[i][j][k][l] += dp[i - 1][j - 1][p][l ^ 1];
            else dp[i][j][k][l] = dp[i - 1][j][k - 1][l];
        }
    }
}

void solve_a () {
    int ans = 0;
    repa (i,m) ans += dp[n][k][i][1];
    printf("%d\n", ans);
}

char s[N];

void solve_b() {
    int q; scanf("%d",&q);
    while (q--) {
        scanf("%s",s);
        vector < int > bars;
        int pre = 0;
        repa (i , n - 1) {
            if (s[i - 1] != s[i]) {
                bars.push_back(i - pre);
                pre = i;
            }
        }
        bars.push_back(n - pre);
        int type = 1 , lbit = n , lbar = k;
        int ans = 0;
        foreach (i,bars) {
            int len = bars[i];
            if (type) {
                for (int j=0;j < len;j++) ans += dp[lbit][lbar][j][1];
            }else {
                for (int j=len + 1;j<=m;j++) ans += dp[lbit][lbar][j][0];
            }
            lbit -= len;
            lbar --;
            type ^= 1;
        }
        printf("%d\n",ans);
    }
}   

int main(){
    init();
    solve_a();
    solve_b(); 
    return 0;
}
