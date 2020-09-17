include <iostream>
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

#ifdef ENABLE_LL
#define int long long
#endif

#ifdef ENABLE_LL
#define I "%lld"
#define II "%lld%lld"
#define III "%lld%lld%lld"
#define IIII "%lld%lld%lld%lld"
#define IN "%lld\n"
#define IIN "%lld%lld\n"
#define IIIN "%lld%lld%lld\n"
#define IIIIN "%lld%lld%lld%lld\n"
#else
#define I "%d"
#define II "%d%d"
#define III "%d%d%d"
#define IIII "%d%d%d%d"
#define IN "%d\n"
#define IIN "%d%d\n"
#define IIIN "%d%d%d\n"
#define IIIIN "%d%d%d%d\n"
#endif

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#define ses(a) std::cout << #a << "=" << a << " " 
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#define ses(a)
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)
typedef pair < int , int > pr;
typedef pair < pr  , int > prr;
#define L first
#define R second
template <class T> inline bool checkMin(T& a , T b) { return (a < b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a > b ? a=b,1 : 0); }

const int N = 1000005;
const int M = 2000005;
const int INF = 0x3f3f3f3f;
int k[3];

struct Node {
    int vl;
    int lz[3];

    Node() { memset(lz,INF,sizeof(lz)); }
};

struct SegTree{
    Node tr[M];

    inline int Ls(int u , int l , int mid) {
        return u + 1;
    }

    inline int Rs(int u , int l , int mid) {
        return u + (mid - l + 1) * 2;
    }

    void pushUp(int u , int l , int r) {
        int m = (l + r) >> 1;
        tr[u].vl = min( tr[Ls(u,l,m)].vl , tr[Rs(u,l,m)].vl );
    }

    void pushDown(int u , int l , int r) {
        int m = (l + r) >> 1;
        int ls = Ls(u , l , m) , rs = Rs(u , l , m);
        rep (b,3) {
            if (tr[u].lz[b] == INF) continue;
            checkMin( tr[ls].vl , max(0 , min(k[b] * l       + tr[u].lz[b] , k[b] * m + tr[u].lz[b]) ) );
            checkMin( tr[rs].vl , max(0 , min(k[b] * (m + 1) + tr[u].lz[b] , k[b] * r + tr[u].lz[b]) ) );
            checkMin( tr[ls].lz[b] , tr[u].lz[b]);
            checkMin( tr[rs].lz[b] , tr[u].lz[b]);
            tr[u].lz[b] = INF;
        }
    }

    void build(int a[] , int l , int r , int pos = 0) {
        tr[pos] = Node();
        if (l == r) { tr[pos].vl = a[l]; return; }
        int m = (l + r) >> 1;
        int ls = Ls(pos,l,m) , rs = Rs(pos,l,m);
        build(a , l   , m , ls);
        build(a , m+1 , r , rs);
        pushUp(pos,l,r);
    }

    void modify(int ll , int rr , int l , int r , int kd , int vvl , int pos = 0) {
        if (ll >= l && rr <= r) {
            if (checkMin(tr[pos].lz[kd] , vvl)) {
                checkMin(tr[pos].vl , max(0, min(k[kd] * ll , k[kd] * rr) + vvl));
            }
            return ;
        }
        pushDown(pos,ll,rr);
        int m = (ll + rr) / 2;
        int ls = Ls(pos,l,m) , rs = Rs(pos,l,m);
        if (l <= m) modify(ll,rr,l  ,m,kd,vvl,ls);
        if (r >  m) modify(ll,rr,m+1,r,kd,vvl,rs);
        pushUp(pos,l,r);
    }

    int query(int ll , int rr , int l , int r , int pos = 0) {
        if (ll >= l && rr <= r) return tr[pos].vl;
        pushDown(pos , l , r);
        int m = (l + r) >> 1;
        int ls = Ls(pos,l,m) , rs = Rs(pos,l,m);
        int ans = INF;
        if (ll <= m) checkMin(ans,query(ll,rr,l  ,m,ls));
        if (rr >  m) checkMin(ans,query(ll,rr,m+1,r,rs));
        return ans; 
    }
};

SegTree st;
int tree[N];
int n , m , q;

void init() {
    rep (i,3) scanf(I,&k[i]);
    scanf(I,&n); repa(i,n) scanf(I,&tree[i]);
    st.build(tree,1,n);
    scanf(I,&m);
    rep (i,m) {
        int l , r , p , d; scanf(IIII,&l,&r,&p,&d);
        st.modify(l,r,1,n,p-1,d);
    }
}

void solve() {
    scanf(I,&q);
    rep (i,q) {
        int l , r; scanf(II,&l,&r);
        printf(IN,st.query(l,r,1,n));
    }
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    return 0;
}
