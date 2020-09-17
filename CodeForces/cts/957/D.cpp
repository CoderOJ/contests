#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

#define int long long

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
typedef pair < int , int > pr;
typedef pair < pr  , int > prr;
#define L first
#define R second

const int N = 500005;
int a[N],o[N];
int n;

void init(){
    scanf("%lld",&n);
    repa (i,n) {
        scanf("%lld",&a[i]);
        o[i] = a[i];
    }
}

void solve() {
    repa (i,n) a[i] = max(a[i - 1] , a[i] + 1);
    for (int i=n;i>0;i--) a[i] = max(a[i] , a[i + 1] - 1);
    int ans = 0;
    repa (i,n) ans += a[i] - o[i] - 1;
    printf("%lld\n",ans);
}

#undef int
int main(){
    init();
    solve(); 
    return 0;
}
