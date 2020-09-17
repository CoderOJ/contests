#include <bits/stdc++.h>
using namespace std;

long long seed;
inline long long rand(long long l, long long r) {
    static long long mo=1e9+7, g=78125;
    return l+((seed*=g)%=mo)%(r-l+1);
}

int main(){
 int T;
 cin >> T;
 while (T--){
    long long n;
    cin >> n >> seed;
    long long mn0,mn1,mx0,mx1;
    mn0 = mn1 = 1LL << 60;
    mx0 = mx1 = - 1LL << 60;
    for (int i=1;i<=n;i++){
        long long x = rand(-1000000000, 1000000000);
        long long y = rand(-1000000000, 1000000000);
        mn0 = min(mn0,x + y);
        mx0 = max(mx0,x + y);
        mn1 = min(mn1,x - y);
        mx1 = max(mx1,x - y);
    }
    cout << max ( llabs(mx0 - mn0) , llabs(mx1 - mn1)  ) << endl ;
 }
 return 0;
}
