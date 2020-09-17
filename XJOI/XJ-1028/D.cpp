#include <bits/stdc++.h>
#define debug(s) std::cout << #s << "=" << s << std::endl
using std::sort;

const int N = 55;
const int M = 100005;

struct Problem{
    long long point,less,solveTime;
};

bool cmp(Problem A,Problem B){
    return A.less * B.solveTime > B.less * A.solveTime;
}

Problem p[N];
long long dp[M];

template <class T>
inline void checkMax(T& a,T b){
    if (a < b){
	a = b;
    }
}

int main(){
    int n,t;
    scanf("%d%d",&n,&t);
    for (int i=1;i<=n;i++){
	scanf("%lld",&p[i].point);
    }
    for (int i=1;i<=n;i++){
	scanf("%lld",&p[i].less);
    }
    for (int i=1;i<=n;i++){
	scanf("%lld",&p[i].solveTime);
    }
    sort(p + 1,p + n + 1,cmp);
    for (int i=1;i<=n;i++){
	for (int j=t;j>=p[i].solveTime;j--){
	    checkMax(dp[j],dp[j - p[i].solveTime] + p[i].point - p[i].less * j);
	}
    }
    long long ans = 0;
    for (int i=0;i<=t;i++){
	checkMax(ans,dp[i]);
    }
    printf("%lld\n",ans);
    return 0;
}
