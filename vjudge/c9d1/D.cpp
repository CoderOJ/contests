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

#define X first
#define Y second
typedef pair < int , int > Point;

const int N = 100050;
struct Saler {
    Point pos;
    int earn;

    Saler (Point pos = Point(0,0) , int earn = 0) : pos(pos) , earn(earn) {}
};

bool PointRCmp (const Point& A , const Point& B) {
    return (A.Y == B.Y) ? A.X < B.X : A.Y < B.Y;
}

int px[N] , py[N] , earn[N];
Saler p[N];
int n;

Point tmp[N];
int tmpV[N];
void disc(int a[]) {
    rep (i,n) tmp[i] = Point ( a[i],i );
    sort (tmp,tmp + n);
    rep (i,n) tmpV[i] = (i != 0 && tmp[i].first == tmp[i - 1].first) ? tmpV[i - 1] : i ;
    rep (i,n) tmp[i].first = tmpV[i];
    sort (tmp,tmp + n,PointRCmp);
    rep (i,n) a[i] = tmp[i].first;
}   

void init(){
    scanf("%d",&n);
    rep (i,n) scanf("%d%d%d",&px[i],&py[i],&earn[i]);
    disc(px) ; disc(py);
    rep (i,n) p[i] = Saler ( Point(px[i],py[i]) , earn[i] );
}

void test_Disc_SalerInit() {
    puts("Test of : Disc & SalerInit");
    rep (i,n) cout << p[i].pos.X << ' ' << p[i].pos.Y << ' '<< p[i].earn << endl;
    puts("Test END");
    puts("");
}

int bna[N];

bool cmp_dp(const Saler& A , const Saler& B) {
    return (A.pos.X == B.pos.X) ? A.pos.Y > B.pos.Y : A.pos.X < B.pos.X;
}

inline void modify (int pos , int val) {
    pos += 5;
    while (pos <= n + 10) {
        bna[pos] = max(bna[pos] , val);
        pos += (pos & (-pos));
    }
}

inline int query (int pos) {
    pos += 5;
    int res = 0;
    while (pos) {
        res = max(res,bna[pos]);
        pos -= (pos & (-pos));
    }
    return res;
}

void solve() {
    //test_Disc_SalerInit();
    memset (bna,0,sizeof(bna));
    sort (p,p + n,cmp_dp);
    rep (i,n) {
        see(i);
        modify ( p[i].pos.Y , query(p[i].pos.Y - 1) + p[i].earn );
    }
    printf("%d\n",query(n));
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--) {
        init() ;
        solve() ;   
    }
    return 0;
}
