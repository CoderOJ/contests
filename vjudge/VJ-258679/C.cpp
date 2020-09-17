#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;
int a[N];

int pre[N];
int pos[N];

long long sum[N];

int lst[N];

long long dp[N];

int main(){

    int n;
    while (scanf("%d",&n) && n){
	for (int i=1;i<=n;i++){
	    scanf("%d",&a[i]);
	}

	memset(pre,0,sizeof(pre));
	memset(pos,0,sizeof(pos));
	for (int i=1;i<=n;i++){
	    if (pre[a[i]]){
		pos[i] = pre[a[i]];
	    }
	    pre[a[i]] = i;
	}

	memset(sum,0,sizeof(sum));
	for (int i=1;i<=n;i++){
	   if (pos[i]){
	       sum[i - pos[i]] ++;
	   }
	}
	for (int i=2;i<=n;i++){
	    if (pos[i]){
		sum[i] += sum[i - 1] - 1;
	    }else{
		sum[i] += sum[i - 1];
	    }
	}

	memset(lst,0,sizeof(lst));
	memset(dp,0,sizeof(dp));
	for (int i=n;i>=1;i--){
	    lst[i] = lst[i + 1];
	    if (!dp[a[i]]){
		lst[i] ++;
		dp[a[i]] = 1;
	    }
	}
	
	memset(dp,0,sizeof(dp));
	dp[1] = (long long)n;
	for (int i=2;i<=n;i++){
	    dp[i] = dp[i-1] + (long long)(n - i + 1) - sum[i - 1] - (long long)lst[n - i + 2];
	}

	int m;
	scanf("%d",&m);
	while (m--){
	    int x;
	    scanf("%d",&x);
	    printf("%lld\n",dp[x]);
	}
    }
    return 0;
}
