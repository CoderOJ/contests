#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 100;
char a[N];
int dp[N][N];
int n;

void init(){
    scanf("%s",a + 1);
    n = strlen(a + 1);
    memset(dp,0xff,sizeof(dp));
}

int solve(int f,int t){
    if (f == 1 || t == n){
	return 1;
    }
    if (dp[f][t] != -1){
	return dp[f][t];
    }
    if (a[f - 1] == a[t + 1]){
	return dp[f][t] = solve(f - 1,t) + solve(f,t + 1);
    }else{
	return dp[f][t] = solve(f - 1,t) + solve(f,t + 1) - solve(f - 1,t + 1);
    }
}
	

#undef int
int main(){
#define int long long
    int T;
    scanf("%lld",&T);
    for (int cs = 1;cs <= T;cs++){
	init();
	int ans = 0;
	for (int i=1;i<=n;i++){
	    for (int j=i;j<=n;j++){
		if (a[i] == a[j]){
		    ans += solve(i,j);
		}
	    }
	}
	printf("Case %lld: %lld\n",cs,ans);
    }
    return 0;
}

