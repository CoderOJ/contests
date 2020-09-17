#define ENABLE_LL
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

const int N = 1000005;
const int MOD = 1e9 + 7;
char s[N];
int n, m;

int p2[N];
void initP2 () {
    p2[0] = 1;
    repa (i,N-1) p2[i] = (p2[i-1] * 2) % MOD;
}

inline int get(int u) {
    return (p2[u+1] - 1 + MOD) % MOD;
}

inline int geti(int u, int v) {
    return (get(v) - (u ? get(u-1) : 0) + MOD) % MOD;
}

struct STree {
    static const int R = 1;
    int t[N*4], s[N*4], c[N*4];

    void pushUp(int u) {
        s[u] = (s[u*2] + s[u*2+1]) % MOD;
        c[u] = (c[u*2] + c[u*2+1]) % MOD;
    }

    void rev(int u, int l, int r) {
        s[u] = (geti(l,r) - s[u] + MOD) % MOD;
        c[u] = (r-l+1 - c[u] + MOD) % MOD;
        ses(u);ses(l);ses(r);ses(s[u]);see(c[u]);
    }

    void pushDown(int u, int l, int r) {
        int m = (l + r) >> 1;
        if (t[u]) {
            t[u*2] ^= 1; rev(u*2,l,m);
            t[u*2+1] ^= 1; rev(u*2+1,m+1,r);
        }
        t[u] = 0;
    }

    void modify(int al, int ar, int l, int r, int u = R) {
        ses(al);ses(ar);ses(l);ses(r);see(u);
        if (l != r) pushDown(u, l, r);
        if (l >= al && r <= ar) {
            t[u] = 1; rev(u,l,r);
            return;
        }
        int m = (l + r) >> 1;
        if (al <= m) modify(al,ar,l,m,u*2);
        if (ar > m) modify(al,ar,m+1,r,u*2+1);
        pushUp(u);
    }

    int queryS(int al, int ar, int l, int r, int u=R) {
        if (l != r) pushDown(u,l,r);
        if (l >= al && r <= ar) return s[u];
        int m = (l + r) >> 1;
        int ans = 0;
        if (al <= m) (ans += queryS(al,ar,l,m,u*2)) %= MOD;
        if (ar > m) (ans += queryS(al,ar,m+1,r,u*2+1)) %= MOD;
        return ans;
    }

    int queryC(int al, int ar, int l, int r, int u = R) {
        if (l != r) pushDown(u,l,r);
        if (l >= al && r <= ar) return c[u];
        int m = (l + r) >> 1;
        int ans = 0;
        if (al <= m) (ans += queryC(al,ar,l,m,u*2)) %= MOD;
        if (ar > m) (ans += queryC(al,ar,m+1,r,u*2+1)) %= MOD;
        return ans;
    }
};

STree st;

int div2(int u) {
    if (u % 2 == 0) return u / 2;
    else return (u + MOD) / 2;
}

void init() {
    initP2();
    scanf("%s",s);
    n = strlen(s);
    reverse(s, s+n);
    rep (i,n) if (s[i] == '1') st.modify(i, i, 0, n-1);
    see("pass");
}

int getAns() {
    //return div2( st.queryS(1,n-1,0,n-1) ) + (st.queryC(0,n-1,0,n-1) % 2 == 0) ;
    return div2( st.queryS(1,n-1,0,n-1) ) + (st.queryC(0,0,0,n-1) ? 1 : (st.queryC(0,n-1,0,n-1) % 2 == 0));
}

void solve() {
    printf(IN,getAns());
    scanf(I,&m);
    rep (i,m) {
        int l, r; scanf(II,&l,&r); l--; r--;
        if (l > r) swap(l,r);
        int ll = n - r - 1, rr = n - l - 1;
        ses(ll);see(rr);
        st.modify(ll,rr,0,n-1);
        printf(IN,getAns());
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
