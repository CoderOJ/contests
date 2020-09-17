#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,cnt = 0;
    double x,tot = 0;
    cin >> n;
    for (int i=1;i<=n * 2;i++){
        cin >> x;
        x -= floor(x);
        cnt += (x == 0);
        tot -= x;
    }
    double ans = 1e5;
    for (int i=n - cnt;i<=min(n * 2 - cnt,n);i++){
        ans = min(ans,fabs(tot + i));
        //ocout << fabs(tot + i) << endl;
    }
    printf("%.3lf",ans);
    return 0;
}
