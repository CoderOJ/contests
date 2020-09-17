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

const int N = 305;
pr a[N];
bool vis[N];
int n;

void init(){
    scanf("%d",&n);
    a[0] = pr(0,0);
    repa (i,n) scanf("%d%d",&a[i].X , &a[i].Y);    
    n++;
    memset(vis,0,sizeof(vis));
    vis[0] = 1;
}

void cmp(pr a , pr b , int& tp , double& ray) {
    if (a.X <= b.X && a.Y <= b.Y) { 
        tp = 1 ; 
        return ; 
    }
    if (a.X >= b.X && a.Y >= b.Y) {
        tp = 0;
        return ;
    }
    int ca = a.X - b.X;
    int cb = a.Y - b.Y;
    if (ca < 0) {
        tp = 2; ray = -1.0 * cb / ca;
        return;
    }else {
        tp = 3; ray = -1.0 * cb / ca;
        return;
    }
}

const double eps = 1e-6;

int dfs(int pos , int cn , double l , double r) {
    if (l >= r - eps) return 0;
    if (cn == n) return 1;
    vis[pos] = 1;
    int ans = 0;
    rep (i,n) {
        if (vis[i]) continue;
        int tp ;
        double ray;
        cmp(a[pos] , a[i] , tp , ray);
        if (tp == 0) continue;
        if (tp == 1) ans += dfs(i , cn + 1 , l , r);
        if (tp == 2) ans += dfs(i , cn + 1 , max(l , ray) , r);
        if (tp == 3) ans += dfs(i , cn + 1 , l , min(ray , r));
    }
    vis[pos] = 0;
    see(pos);
    see(cn);
    see(l);
    see(r);
    see(ans);
    return ans;
}

int main(){
    int T;
    scanf("%d",&T);
    repa (kas , T) {
        init() ;
        printf("Case #%d: %d\n",kas,dfs(0,1,0.0 , 1e12));
    }
    return 0;
}
