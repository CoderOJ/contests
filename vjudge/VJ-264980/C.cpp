#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;
#define FORMAP(a,b) for(int a=0;a<(int)b.size();a++)

const int N = 205;
vector < int > e[N];
int dp[N][N][2];
int vl[N];
int n,m;

template <class T>
inline void checkMax(T& a,T b){
    a = max(a,b);
}

void dfs(int root,int pre){
    FORMAP(i,e[root]){
        int v = e[root][i];
        if (v != pre){
            dfs(v,root);
            for (int j=m;j>=1;j--){
                for (int k=0;k < j;k++){
                    checkMax(dp[root][j][1],dp[root][j - k - 1][0] + dp[v][k][1] + vl[v]);
                    if (j - k - 2 >= 0){
                        checkMax(dp[root][j][1],dp[v][k][0] + dp[root][j - k - 2][1] + vl[v]);
                        checkMax(dp[root][j][0],dp[v][k][0] + dp[root][j - k - 2][0] + vl[v]);
                    }
                }
            }
        }
    }
}

int main(){
    while (scanf("%d%d",&n,&m)== 2){
        memset(dp,0,sizeof(dp));
        for(int i = 0; i <= n; i++){
            e[i].clear();
        }
        for (int i=1;i<=n;i++){
            scanf("%d",&vl[i]);
        }
        for (int i=1;i<n;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            e[u].push_back(v);
            e[v].push_back(u);
        }
        dfs(1,0);
        printf("%d\n",dp[1][m][1] + vl[1]);
    }
    return 0;
}
