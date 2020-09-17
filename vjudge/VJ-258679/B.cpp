#include <bits/stdc++.h>
using namespace std;
#define int long long  

const int N = 400;
const int MOD = 1e9 + 7;
int dp[N][N];
int nCr[N][N];

void init(){
    memset(dp,0xff,sizeof(dp));
}

void init_nCr(int n = N){
    for (int i=0;i<n;i++){
        nCr[i][0] = 1;
    }
    for (int i=1;i<n;i++){
        for (int j=1;j<=i;j++){
            nCr[i][j] = (nCr[i - 1][j - 1] + nCr[i - 1][j]) % MOD;
            //cout << i << ' ' << j  << ' ' << nCr[i][j] << endl;
        }
    }
}

int solve(int n,int d){
    if (n == 1LL){
        return d >= 1LL? 1LL : 0LL;
    }
    if (d == 0){
	return 0;
    }
    if (dp[n][d] != -1){
        return dp[n][d];
    }
    int& ans = dp[n][d];
    ans = solve(n - 1,d - 1) * nCr[n][1] * 2 % MOD;
    for (int i=1;i<=n - 2;i++){ // i means sizeof leftSubTree
        ans += ( solve(i,d - 1) * solve(n - i - 1,d - 1) % MOD * nCr[n - 2][i] ) % MOD * n % MOD;
        ans %= MOD;
    }
    return ans;
}

#undef int 
int main(){
#define int long long
    init();
    init_nCr();
    int T;
    scanf("%lld",&T);
    for (int cs = 1;cs <= T;cs++){
        int n,d;
        scanf("%lld%lld",&n,&d);
        printf("Case #%lld: %lld\n",cs,(solve(n,d) - solve(n,d - 1LL) + MOD) % MOD);
    }
    return 0;
}


