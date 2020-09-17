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
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); }

const int N = 200005;
int n , m;

struct Node {
    int vl , mk;
    Node* l; 
    Node* r;
    Node() {}
    Node(int vl , Node* l , Node* r) : vl(vl) , l(l) , r(r) { mk = 0; }
};
Node a[N];

void init() {
    scanf(II,&n,&m);
    rep (i,n) {
        int r; scanf(I,&r);
        a[i] = Node(r , a + (i+n-1)%n , a + (i+1)%n);
    }
    if (m > n / 2) { puts("Error!"); exit(0); }
}

struct cmp{
    bool operator ()(const int x, const int y) const {
        return a[x].vl < a[y].vl;
    }
};

void solve() {
    priority_queue < int , vector < int > , cmp > que;
    rep (i,n) que.push(i);
    int ans = 0;
    rep (_,m) {
        while ( a[que.top()].mk ) que.pop();
        int u = que.top(); que.pop();
        ses(u);ses(a[u].l->vl);see(a[u].r->vl);
        ans += a[u].vl;
        see(ans);
        a[u].vl = a[u].l->vl + a[u].r->vl - a[u].vl;
        a[u].l->mk = 1; a[u].r->mk = 1;
        a[u].l = a[u].l->l; a[u].r = a[u].r->r;
        a[u].l->r = &a[u]; a[u].r->l = &a[u];
        que.push(u);
    }
    printf(IN,ans);
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    return 0;
}
