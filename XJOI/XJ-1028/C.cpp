#include <bits/stdc++.h>
using namespace std;

int toPrice(char a){
    if (a >= '0' && a <= '9'){
        return a - '0';
    }else if (a >= 'A' && a <= 'Z'){
        return a - 'A' + 10;
    }else{
        return a - 'a' + 36;
    }
}

const int N = 55;
int price[N][N];

bool check(int n,int m,int day,int bud){
    int ans = 0;
    for (int i=1;i<=7;i++){
        int mn = 0x3f3f3f3f;
        for (int j=1;j<=m;j++){
            int sum = 0;
            for (int k=i;k<=day;k+=7){
                sum += price[k][j];
            }
            mn = min(mn,sum);
        }
        ans += mn;
    }
    return ans <= bud;
}

int main(){
    int n,m,bud;
    cin >> n >> m >> bud;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            char r;
            cin >> r;
            price[i][j] = toPrice(r);
        }
    }
    for (int i=n;i>=0;i--){
        if (check(n,m,i,bud)){
            cout << i << endl;
            return 0;
        }
    }
    return 0;
}
