#include <bits/stdc++.h>
#define int long long
using namespace std;
  
#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 

const int N = 20005;
const int INF = (int)(1e14);
int a[N];
int n,s,m,k;

int gcd(int a,int b) {
    return b == 0 ? a : gcd(b,a % b);
}

void init() {
    scanf("%lld%lld%lld%lld",&n,&s,&m,&k);
    for (int i=0;i<n;i++) {
        scanf("%lld",&a[i]);
    }
}

inline int getSum(int st , int step) {
    int res = 0;
    for (int i = st;i < n;i += step) res += a[i];
    return res;
}

int sum[N] , dp[N];
inline int maxSub(int st, int l,int ml) {
    if (ml == 0) return 0;
    vector < int > vt;
    for (int i=0;i<l;i++) vt.push_back( a[(st + k * i) % n] );
    for (int i=0;i<l;i++) vt.push_back( vt[i] );
    sum[0] = vt[0];
    for (int i=1;i<2 * l;i++) sum[i] = sum[i - 1] + vt[i];
    deque < pair < int , int > > ms;
    dp[0] = vt[0];
    ms.push_front( pair < int , int > (sum[0],0) );
    int res = dp[0];
    for (int i=1;i<l * 2;i++) {
        if (ms.back().second + ml < i) ms.pop_back();
        dp[i] = sum[i] - ms.back().first;
        res = max(res,dp[i]);
        while (!ms.empty() && ms.front().first > sum[i]) ms.pop_front();
        ms.push_front( pair < int , int > (sum[i],i) );
    }
    return res;
}

void solve(int idx) {
    int g = gcd(n,k);
    int l = n / g;
    int ans = -INF;
    for (int st = 0;st < g;st++) {
        int sum = getSum(st,g);
        ans = max(ans , max (sum * (m / l),0LL) + maxSub (st,l,m % l) );
        if (m >= l) ans = max(ans , max(sum * (m / l - 1) , 0LL) + maxSub(st,l,m % l + l) );
    }
    printf("Case #%lld: %lld\n", idx , max(0LL,s - ans) );
}

#undef int 
int main() {
#define int long long
    int T;
    scanf("%lld",&T) ;
    for (int i=1;i<=T;i++) {
        init();
        solve(i);
    }
    return 0;
}
