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

struct CSeg {
    static const int N = 10000005;
    int root[N];
    int ls[N] , rs[N];
    int num[N];
    int sz ;

    CSeg () {
        memset(root , 0 , sizeof(root));
        memset(ls , 0 , sizeof(ls));
        memset(rs, 0 , sizeof(rs));
        memset(num , 0 , sizeof(num));
        sz = 0;
        root[0] = sz;
    }

    void build (int l , int r , int& id) {
        id = sz++;
        num[id] = 0;
        if (l == r) return ;
        int mid = (l + r) >> 1;
        build(l       , mid , ls[id] );
        build(mid + 1 , r   , rs[id] );
    }

    void update (int l , int r , int& id , int pr , int cr) {
        id = sz++;
        ls[id] = ls[pr] ; rs[id] = rs[pr];
        num[id] = num[pr] + 1;
        if (l == r) return;
        int mid = (l + r) >> 1;
        if (cr <= mid) update(l       , mid , ls[id] , ls[pr] , cr);
        else           update(mid + 1 , r   , rs[id] , rs[pr] , cr);
    }

    int query (int l ,int r , int id , int ql , int qr) {
        if (ql > qr) return 0;
        if (ql <= l && qr >= r) return num[id];
        int mid = (l + r) >> 1;
        int res = 0;
        if (ql <= mid) res += query(l       , mid , ls[id] , ql , qr);
        if (qr >  mid) res += query(mid + 1 , r   , rs[id] , ql , qr);
        return res;
    }
};

const int N = 200005;
int a[N];
int ans[N];
int n;

void init(){
    scanf("%d",&n);
    rep (i,n) scanf("%d",&a[i]);
}

CSeg Data;
int shuf[N];
int nShuf;

inline int get(int x) {
    return lower_bound(shuf , shuf + nShuf , x) - shuf + 1;
}

void init_Data() {
    rep (i,n) shuf[i] = a[i];
    sort (shuf , shuf + n );
    nShuf = unique ( shuf , shuf + n ) - shuf;
    Data.build(1 , nShuf , Data.root[0]);
    rep (i,n) Data.update(1 , nShuf , Data.root[i +  1] , Data.root[i] , get(a[i]));
}

void solve(int idx) {
    repa (ary , n) {
        if (idx * ary + 1 >= n) return ;
        int l = idx * ary + 1;
        int r = min ( idx * ary + ary , n - 1 );
        int g = get(a[idx]) - 1;
        ans[ary] += Data.query( 1 , nShuf , Data.root[r + 1] , 1 , g )
                  - Data.query( 1 , nShuf , Data.root[l    ] , 1 , g );
    }
}

int main(){
    init();
    init_Data();
    rep (i,n - 1) solve(i) ; 
    repa (i,n - 1) printf("%d ",ans[i]);
    puts("");
    return 0;
}
