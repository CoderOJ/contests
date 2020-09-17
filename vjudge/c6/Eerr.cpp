#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int mod = 1e8 + 7;

int T;
int n, k, s;
int f[2][15001]; //前i个，和为j
int sum[2][15001];

void add(int &x, int y) {
    x += y;
    if(x >= mod) {
        x -= mod;
    }
}

void sub(int &x, int y) {
    x -= y;
    if(x < 0) 
        x += mod;
}
int main(){
    cin >> T;
    for (int ti = 1; ti <= T; ti ++){
        cin >> n >> k >> s;
        memset(sum, 0, sizeof(sum)); 
        memset(f, 0, sizeof(f)); 


        for (int i = 1; i <= k; i ++){
            f[1][i] = 1;
        }

        for (int i=1;i<=s;i++) {
            sum[1][i] = sum[1][i - 1] + f[1][i];
        }

        for(int i = 2; i <= n; i ++){   
            sum[i % 2][0] = 0;
            for (int j = 1; j <= s; j ++){
                f[i % 2][j] = 0;
                if(j <= k) 
                    add(f[i % 2][j],sum[(i - 1) % 2][j - 1]);
                else {
                    add(f[i % 2][j], sum[(i-1) % 2][j-1] );
                    sub(f[i % 2][j],sum[(i-1) % 2][j-k-1]);
                }

                sum[i % 2][j] = (sum[i % 2][j - 1] + f[i % 2][j]) % mod; 
            }
            memset(f[(i -1) % 2],0,sizeof(f[(i - 1) % 2]));
        }

        cout << "Case " << ti << ": " << f[n % 2][s] << endl;
    }
    return 0;
}
