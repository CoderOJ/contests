#include <bits/stdc++.h>
using namespace std;

template <class T>
static void loopRead(T* f,T* t,string type = "~"){
    for (T* idx = f;idx < t;idx++){
        if (type == "~"){
            cin >> *idx;
        }else{
            scanf(type.c_str(),idx);
        }
    }
}

const int INF = 0x3f3f3f3f;
const int N = 100;
const int M = 10005;
int a[N];
int b[N];
int c[N];
int s[N];
int dp[N * M];

int solve(int num[] , int k , int n){
    fill (dp + 1,dp + N * M,INF);
    dp[0] = 0;
    for (int i=1;i<=n;i++){
	for (int j=N * M;j >= num[i];j--){
	    if (dp[j] > dp[j - num[i]] + c[i]){
		dp[j] = dp[j - num[i]] + c[i];
	    }
	}
    }
    int ans = INF;
    for (int i=k;i<N * M;i++){
	ans = min(ans,dp[i]);
    }
    return ans;
}

int main(){
    int n,k;
    cin >> n >> k;
    loopRead(a + 1,a + n + 1);
    loopRead(b + 1,b + n + 1);
    loopRead(c + 1,c + n + 1);
    for (int i=1;i<=n;i++){
	s[i] = a[i] + b[i];
	a[i] --;
	b[i] --;
    }
    int a1 = solve(a,k,n);
    int a2 = solve(b,k,n);
    int a3 = solve(s,k + k - 1,n);
    int aans = min ( min ( a1 , a2 ) , a3 );
    cout << (aans == INF?-1:aans) << endl;
    return 0;
}
