#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
char a[N];
char b[N];
int dp[N][20][20];
//dp[i][j][k] means the minium total of changes that coudl let a[0~i-1] equl b[0~i-1] and a[i] equl j and a[i+1] equl k
//so the ans is dp[l][0][0] (l is the length of the input string (we cannot change a[l] and a[l+1] so the ans only is a[l][0][0])

void checkMin(int& a,int b){
    if (b < a){
        a = b;
    }
}

int main(){
    while (scanf("%s%s",a,b) != EOF){
        int len = strlen(a);
        for (int i=0;i<len;i++){
            a[i] -= '0';
            b[i] -= '0';
        }
        memset(dp,0x3f,sizeof(dp));
        dp[0][0][0] = 0; // 0 means it haven't changed
        for (int i=0;i<len;i++){
            for (int j=0;j<10;j++){
                for (int k=0;k<10;k++){
                    int change1 = (b[i] - a[i] - j + 20) % 10;
                    int change2 = 10 - change1;
                    // from dp[i][j][k] to dp[i+1][j+x][k+y] (y <= x <= change)
                    for (int cx=0;cx<=change1;cx++){
                        for (int cy=0;cy<=cx;cy++){
                            int x = (k + cx) % 10;
                            int y = cy;
                            checkMin(dp[i + 1][x][y],dp[i][j][k] + change1);
                        }
                    }
                    for (int cx=0;cx<=change2;cx++){
                        for (int cy=0;cy<=cx;cy++){
                            int x = (10 + k - cx) % 10;
                            int y = (10 - cy) % 10;
                            checkMin(dp[i + 1][x][y],dp[i][j][k] + change2);
                        }
                    }
                }
            }
        }
        printf("%d\n",dp[len][0][0]);
    }
    return 0;
}
