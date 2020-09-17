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

#define long long long
#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 

#define le first
#define ri second

const int N = 100005;
typedef pair < int , int > Inter;
Inter a[N];
int ans[N];
int n,m;
priority_queue < int , vector < int > , greater < int > > que;

void clearQue() {
    while (!que.empty()) que.pop();
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--) {
        clearQue();
        scanf("%d%d",&n,&m);
        rep (i,m) scanf("%d%d",&a[i].le,&a[i].ri);
        a[m] = Inter(0x3f3f3f3f,0x3f3f3f3f);
        sort (a , a + m + 1);
        repa (i,n) que.push(i);
        int r = 1 , l = 1 , i = 0;
        while (r <= n) {
            ans[r] = que.top();
            que.pop();
            r++;
            while (a[i].ri < r) i++;
            while (l < r && l < a[i].le) {
                que.push(ans[l]);
                l++;
            }
        }
        repa (i,n - 1) printf("%d ",ans[i]);
        printf("%d\n",ans[n]);
    }
    return 0;
}
