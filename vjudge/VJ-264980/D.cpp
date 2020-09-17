#include <bits/stdc++.h>
#define int long long
using std::vector;
using std::cin;
using std::cout;
using std::endl;

typedef vector < int > Edge;

const int N = 50005;
const int K = 505;
Edge preE[N];
Edge e[N];
bool vis[N];
int dp[N][K];

void preDfs(int root){
    for (int i=0;i<(int)preE[root].size();i++){
        int u = preE[root][i];
        if (!vis[u]){
            e[root].push_back(u);
            vis[u] = 1;
            preDfs(u);
            vis[u] = 0;
        }
    }
}

void initGraph(int n){
    int ROOT  = 1;
    vis[ROOT] = 1;
    preDfs(ROOT);
}

int solve(int root,int k){
    if (dp[root][k] != -1){
        return dp[root][k];
    }
    if (k == 0){
        return 1;
    }
    int sum = 0;
    for (int i=0;i<(int)e[root].size();i++){
        sum += solve(e[root][i],k - 1);
    }
    return dp[root][k] = sum;
}

int calc(int root,int k){
    int res = 0;
    for (int i=0;i + i <= k;i++){
        int ans = 0;
        int left = i;
        int right = k - i;
        int l = solve(root,left);
        int r = solve(root,right);
        ans += l * r;
        if (left != 0){
            for (int j=0;j<(int)e[root].size();j++){
                int v = e[root][j];
                ans -= solve(v,left - 1) * solve(v,right - 1);
            }
        }
        res += (left == right) ? (ans / 2) : ans;
    }
    return res;
}

#undef int
int main(){
    #define int long long
    int n,k;
    cin >> n >> k;
    for (int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        preE[u].push_back(v);
        preE[v].push_back(u);
    }
    initGraph(n);
    memset(dp,-1,sizeof(dp));
    int ans = 0;
    for (int i=1;i<=n;i++){
        ans += calc(i,k);
    }
    cout << ans << endl;
    return 0;
}
