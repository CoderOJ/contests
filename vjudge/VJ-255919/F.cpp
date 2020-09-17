#include <bits/stdc++.h>
using namespace std;

int main(){
    int T;
    scanf("%d",&T);
    for (int cs = 1;cs <= T;cs ++){
        int n;
        scanf("%d",&n);
        int sum = 0;
        int cnt = 0;
        for (int i=1;i<=n;i++){
            int tmp;
            scanf("%d",&tmp);
            if (tmp > 0){
                cnt ++;
                sum += tmp;
            }else{
                sum -= tmp;
            }
        }
        if (cnt == 0){
            printf("Case %d: inf\n",cs);
            continue;
        }
        int b,o;
        b = cnt;
        o = sum;
        int g = __gcd(b,o);
        b /= g;
        o /= g;
        printf("Case %d: %d/%d\n",cs,o,b);
    }
    return 0;
}
