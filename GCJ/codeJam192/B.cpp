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
#define X first
#define Y second

const int N = 105;
pr a[N];
int n;
void solve(){
    scanf("%d",&n);
    rep (i,n) scanf("%d%d",&a[i].X,&a[i].Y);

    repa (i,1000) {
        repa (j,1000) {
            rep (k,n - 1) {
                if (a[k].X * i + a[k].Y * j >= a[k + 1].X * i + a[k + 1].Y * j) {
                    goto nxt;
                }
            }
            printf("%d %d\n",i,j);
            return ;
            nxt:;
        }
    }
    puts("IMPOSSIBLE");
}

int main(){
    int T;
    scanf("%d",&T);
    repa (kas , T) {
        printf("Case #%d: ",kas);
        solve();   
    } 
    return 0;
}
