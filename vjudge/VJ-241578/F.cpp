#include <bits/stdc++.h>
using namespace std;

const long long SZ = 1005;
long long ta[SZ];
long long tb[SZ];
long long dp[SZ][SZ];
const long long MOD = 1e9 + 7;

void updata(long long& a,long long x,long long c,long long d){
    a = x * c % MOD * d % MOD;
}

void add(long long& a,long long b){
    a = a + b % MOD;
}

int main(){
    long long c,n,m;
    scanf("%lld%lld%lld",&n,&m,&c);
    for (long long i=1;i<=n;i++){
        long long read;
        scanf("%lld",&read);
        ta[read] ++;
    }
    for (long long i=1;i<=m;i++){
        long long read;
        scanf("%lld",&read);
        tb[read] ++;
    }
    for (long long i=0;i<=c;i++){
        dp[1][i] = ta[i] * tb[i] % MOD;
    }
    for (long long i=2;i<=c+1;i++){
        long long pre = 0;
        for (long long j=1;j<=c;j++){
            updata(dp[i][j],pre,ta[j],tb[j]);
            add(pre,dp[i-1][j]);
        }
    }
    for (long long i=2;i<=c+1;i++){
        long long ans = 0;
        for (long long j=1;j<=c;j++){
            add(ans,dp[i][j]);
        }
        printf("%lld ",ans);
    }
    puts("");
    return 0;
}
