#include <bits/stdc++.h>
using namespace std;

const int N = 5005;
double dp[N];
double gd[N];

template <class T>
void loopRead(T* f,T* t,string type = "~"){
    for (T* idx = f;idx < t;idx++){
        if (type == "~"){
            cin >> *idx;
        }else{
            scanf(type.c_str(),idx);
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    int cs = 0;
    while (T--){
        int n;
        scanf("%d",&n);
        loopRead(gd + 1,gd + n + 1);
        for (int i=1,j=n;i<j;i++,j--){
            swap(gd[i],gd[j]);
        }
        dp[1] = gd[1];
        for (int i=2;i<=n;i++){
            int ft = max (1,i - 6);
            double sum = 0;
            int len = i - ft;
            for (int j=ft;j<i;j++){
                sum += dp[j];
            }
            dp[i] = gd[i] + sum / len;
        }
        cs++;
        printf("Case %d: %lf\n",cs,dp[n]);
    }
    return 0;
}
