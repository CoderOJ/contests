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

const int N = 100005;
int a[N];
int n,u;

void init(){
    scanf("%d%d",&n,&u);
    rep (i,n) scanf("%d",&a[i]);
}

void solve() {
    int rc = 0;
    double ans = -1.0;
    rep (i,n) {
        while (rc < n - 1 && a[rc + 1] - a[i] <= u) rc++;
        if (rc - i < 2) continue;
        ans = max(ans , (double)(1.0) * (a[rc] - a[i + 1]) / (a[rc] - a[i]));
    }
    printf("%.9lf\n",ans);
}

int main(){
    init();
    solve();
    return 0;
}
