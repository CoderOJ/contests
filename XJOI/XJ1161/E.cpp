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
#define X  first
#define Y second
typedef pair < double , double > Point;
 
const double INF = 1e15;
const int N = 50005;
Point p[N];
int n;
 
void init(){
    scanf("%d",&n);
    rep (i,n) scanf("%lf%lf" , &p[i].X , &p[i].Y);
    sort(p , p + n);
}
 
inline double dist (Point a , Point b) {
    return sqrt ( (a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y) );
}
 
inline bool rcmp (Point a , Point b) {
    return a.Y == b.Y ? a.X < b.X : a.Y < b.Y;
}

double resp (int l , int r , int mid , double s) {
    vector < Point > v;
    for (int i=l;i<=r;i++) if ( abs(p[mid].X - p[i].X) < s ) v.push_back(p[i]);
    sort (v.begin() , v.end() , rcmp);
    double ans = INF;
    foreach (i,v) {
        for (int j=i + 1;j<(int)v.size() && v[j].Y - v[i].Y < s;j++) {
            ans = min(ans , dist(v[i] , v[j]) );
        }
    }
    return ans;
}

double solve (int l , int r) {
    if (l > r) return INF;
    if (r - l == 0) return INF;
    if (r - l == 1) return dist(p[l] , p[r]);
    int mid = (l + r) / 2;
    double ans =    solve(l , mid - 1);
    ans = min(ans , solve(mid + 1 , r) );
    return min (ans , resp(l , r , mid , ans) );
}
 
int main(){
    init();
    printf("%.2lf\n" , solve(0 , n - 1));
    return 0;
}
