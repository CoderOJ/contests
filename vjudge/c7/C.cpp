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

const int N = 3005;
struct Point {
    int x,y;
    int idx;

    bool operator < (const Point B) {
        return x <  B.x;
    }
};
Point pt[N];
int n;

void init(){
    scanf("%d",&n);
    repa (i,3 * n) {
        int x,y;
        scanf("%d%d",&x,&y);
        pt[i].x = x;
        pt[i].y = y;
        pt[i].idx = i;   
    }
}

void solve() {
    sort(pt + 1,pt + n * 3 + 1);
    repa(i,n) {
        printf("%d %d %d\n",pt[i * 3 - 2].idx,pt[i * 3 - 1].idx,pt[i * 3].idx);
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while (T-- ) {
        init();
        solve();
    }
    return 0;
}
