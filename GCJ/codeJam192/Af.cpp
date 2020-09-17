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
#define X first
#define Y second

const int N = 305;
pr a[N];
int n;

void init(){
    scanf("%lld",&n);
    rep (i,n) scanf("%lld%lld",&a[i].X,&a[i].Y) ;
}

void cmp(pr a , pr b , int& tp , int& ra , int& rb) {
    if (a.X <= b.X && a.Y <= b.Y) { 
        tp = 1 ; 
        return ; 
    }
    if (a.X >= b.X && a.Y >= b.Y) {
        tp = 0;
        return ;
    }
    ra = a.X - b.X;
    rb = a.Y - b.Y;
    if (ra < 0) {
        tp = 2; ra = -ra;
        return;
    }else {
        tp = 3; rb = -rb;
        return;
    }
}

bool cmp (int a, int b , int c , int d) {
    return (a * d - c * b) < 0;
}

void solve() {
    int ans = 0;
    sort (a , a + n);
    do {
        int la = 0 , lb = 1 , ra = 1 , rb = 0;
        rep (i,n - 1) {
            int ty , ta , tb;
            cmp(a[i] , a[i + 1] , ty , tb , ta);
            if (ty == 0) goto nxt;
            if (ty == 1) continue;
            if (ty == 2) {
                if (!cmp(ta , tb , ra , rb)) goto nxt;
                else la = ta , lb = tb;
            }
            if (ty == 3) {
                if (!cmp(la , lb , ta , tb)) goto nxt;
                else ra = ta , rb = tb;
            }
        }
        ans++;
        nxt:;
    }while (next_permutation(a , a + n)) ;
    printf("%lld\n",ans);
}

#undef int
int main() {
#define int long long
    int T;
    scanf("%lld",&T);
    repa (kas,T) {
        init();
        printf("Case #%lld: ",kas);
        solve();
    } 
    return 0;
}
