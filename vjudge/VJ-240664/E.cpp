#include <bits/stdc++.h>
using namespace std;
 
const int MOD = 1e9 + 7;
const int N = 155;
int a[N];
int dp[2][N][N];
 
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        memset(a,0,sizeof(a));
        memset(dp,0,sizeof(dp));
        int n;
        scanf("%d",&n);
        for (int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        dp[1][a[1]][a[2]] = 1;
        for (int i=2;i<N;i++) {
            memset(dp[i % 2],0,sizeof(dp[i % 2]));
            for (int j=0;j<N;j++){
                for (int k=0;k<N;k++){
                    if (dp[(i - 1) % 2][j][k]){
                        //cout<<'#'<<i<<' '<<j<<' '<<k<<endl;
                        int loop = min(j,k);
                        for (int ch=0;ch<=loop;ch++){
                            int tj = k - ch;
                            int tk = a[i + 1] + ch;
                            //cout<<tj<<' '<<tk<<endl;
                            dp[i % 2][tj][tk] = ( dp[i % 2][tj][tk] + dp[(i - 1) % 2][j][k] ) % MOD;
                        }
                    }
                }
            }
        }
        printf("%d\n",dp[(N - 1) % 2][0][0]);
    }
    return 0;
}
