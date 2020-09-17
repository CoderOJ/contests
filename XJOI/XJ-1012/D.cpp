#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 3005;
char a[N];
int dp[N][N];
int n;
const int MOD = 1000000007;

int solve(int f,int t){
	if (f == 1 || t == n){
		return 1;
	}
	if (dp[f][t] != -1){
		return dp[f][t];
	}
	
	int ans = 0;
	if (a[f - 1] == a[t + 1]){
		ans = (solve(f - 1,t) + solve(f,t + 1)) % MOD;
	}else{
		ans = (solve(f - 1,t) + solve(f,t + 1) - solve(f - 1,t + 1) + MOD) % MOD;
	}
	return dp[f][t] = ans;
}

#undef int
int main(){
#define int long long
	
	memset(dp,-1,sizeof(dp));
	scanf("%s",a + 1);
	n = strlen(a + 1);
	int ans = 0;
	for (int i=1;i<=n;i++){
		int tmp = solve(i,i) * i % MOD;
		//cout << tmp << endl;
		ans ^= tmp;
	}
	printf("%lld\n",ans);
	return 0;
}