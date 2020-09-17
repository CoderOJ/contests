#include <bits/stdc++.h>
using namespace std;
 
const int N = 100005;
int dp[N];

void checkMax(int& a,int b){
    if (b > a){
        a = b;
    }
}

int main(){
    int n;
    scanf("%d",&n);
    if (n == 1){
        int read;
        scanf("%d",&read);
        printf("%d",1);
        return 0;
    }
    for (int i=1;i<=n;i++){
        int read;
        scanf("%d",&read);
        int mx = 0;
        int sq = sqrt(read);
        for (int j=2;j<=sq;j++){
            if (read % j == 0){
                checkMax(mx,dp[j]);
                checkMax(mx,dp[read / j]);
            }
        }
        checkMax(mx,dp[read]);
        mx ++;
        for (int j=2;j<=sq;j++){
            if (read % j == 0){
                dp[j] = mx;
                dp[read / j] = mx;
            }
        }
        dp[read] = mx;
    }
    int ans = 0;
    for (int i=2;i<N;i++){
        ans = max(ans,dp[i]);
    }
    cout<<ans<<endl;
    return 0;
}
