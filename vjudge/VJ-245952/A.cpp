#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
char a[N][N];

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++){
        a[i][0] = 'a';
        for (int j=1;j<=m;j++){
            cin >> a[i][j];
        }
    }
    int ans = 0;
    set <int> bk,rp;
    for (int i=1;i<=m;i++){
       // cout << i << ' ' << ans << endl;
        bool flag = 1;
        rp.clear();
        for (int j=1;j<n;j++){
            if (a[j][i] > a[j+1][i] && !bk.count(j)){
                ans++;
                flag = 0;
                break;
            }else if (a[j][i] < a[j+1][i]){
                rp.insert(j);
            }
        }
        if (flag){
            for (int j=1;j<n;j++){
                if (rp.count(j)){
                    bk.insert(j);
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}

