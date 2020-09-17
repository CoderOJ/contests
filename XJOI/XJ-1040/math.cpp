#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#endif
#ifndef __LOCALE__
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif

const int A = 8;
const int N = 155;
int n;
int a[N];
int dp[A][N][N];

inline int fun(int a,int b){
    return ((a & b) + (a | b)) >> 1;
}

void init(){
    memset(dp,-1,sizeof(dp));
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
}

bool check(int r,int f,int t){
    if (f == t){
        return r == a[f];
    }
    if (dp[r][f][t] != -1){
        return dp[r][f][t];
    }
    for (int i=0;i<A;i++){
        for (int j=0;j<A;j++){
            if (fun(i,j) == r){
                for (int k=f;k<t;k++){
                    if (check(i,f,k) && check(j,k + 1,t)){
                        return (bool) (dp[r][f][t] = 1);
                    }
                }
            }
        }
    }
    return (bool) (dp[r][f][t] = 0);
}

int main(){
    init();
    for (int i=0;i<A;i++){
        if (check(i,1,n)){
            cout << i << ' ';
        }   
    }
    puts("");
    return 0;
}
