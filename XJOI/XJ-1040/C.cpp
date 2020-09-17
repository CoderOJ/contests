#include <bits/stdc++.h>
using namespace std;
  
#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a)
#endif

const int N = 35;
const int M = 5005;
int vl[M],tj[M],p[N];
int n,sum,mxp;
int n_w;
int flash_time = 0;
   
void init(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        scanf("%d",&p[i]);
        sum += p[i];
        mxp = max(mxp,p[i]);
    }
    mxp ++;
    for (int i=0;i<=mxp;i++){
        int flag = 0;
        for (int j=1;j<=n;j++){
            if (p[j] + 1 == i){
                flag = 1;
                break;
            }
        }
        if (flag == 0){
            continue;
        }
        n_w++;
        tj[n_w] = i;
        for (int j=1;j<=n;j++){
            if (p[j] < i){
                vl[n_w]++;
            }
        }
    }
}
   
int dp[N * M][N];
int cs[N * M][N];
   
void solve(){
    for (int i=0;i<=n_w;i++){
        for (int j=tj[i];j<=sum;j++){
            for (int k=1;k<=n;k++){
                if (dp[j][k] < dp[j - tj[i]][k - 1] + vl[i]){
                    flash_time++;
                    dp[j][k] = dp[j - tj[i]][k - 1] + vl[i];
                    cs[j][k] = tj[i];
                }
            }
        }
    }
}
   
void put(){
    int x = sum;
    int y = n;
    for (int i=sum;i>=0;i--){
        if (dp[i][y] >= dp[x][y]){
            x = i;
        }
    }
    int cpx = x;
    for (int i=1;i<n;i++){
        int foo = cs[x][y];
        cout << foo << ' ';
        x -= foo;
        y -= 1;
    }
    cout << cs[x][y] + sum - cpx << endl;
    puts("");
}
   
int main(){
    init();
    see("init_over");
    solve();
    see(dp[sum][n]);
    see(flash_time);
    put();
    return 0;
}
