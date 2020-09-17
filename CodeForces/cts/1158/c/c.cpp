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
#define repe(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)
typedef pair < int , int > pr;
typedef pair < pr  , int > prr;
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); }
class Scanner{ private: istream& ist;public: Scanner(istream& in):ist(in){} string next(){ string r; ist >> r; return r; } string nextLine(){ string r; getline(ist,r); return r; } int nextInt(){ int r; ist >> r; return r; } double nextDouble(){ double r; ist >> r; return r; }};
Scanner sc(cin);

struct Node {
    Node *l, *r;
    int v;
    int t;

    Node() { l = r = NULL; t=0; v=0;}

    void pushUp() {
        if (l == NULL || r == NULL) return;
        v = min(l->v, r->v);
    }

    void pushDown() {
        if (l == NULL || r == NULL) return;
        if (t != 0) {
            l->v += t; l->t += t;
            r->v += t; r->t += t;
            t = 0;
        }
    }

    ~Node () {
        if (l != NULL) delete l;
        if (r != NULL) delete r;
    }
};

struct STree {
    Node* R;

    STree () { R = new Node(); }

    void build(int l, int r, Node* u = NULL) {
        if (u == NULL) u = R;
        if (l == r) return;
        int m = (l + r) >> 1;
        build(l, m, u->l = new Node());
        build(m+1,r,u->r = new Node());
    }

    void modify(int ml, int mr, int l, int r, int v, Node* u = NULL) {
        ses(ml);ses(mr);ses(l);see(r);
        if (u == NULL) u = R;
        u->pushDown();
        if (ml <= l && mr >= r) {
            u->v += v;
            u->t += v;
            return ;
        }
        int m = (l + r) >> 1;
        if (ml <= m) modify(ml, mr, l, m, v, u->l);
        if (mr >  m) modify(ml, mr,m+1,r, v, u->r);
        u->pushUp();
    }
    
    int query(int l, int r, Node* u = NULL) {
        if (u == NULL) u = R;
        ses(l);ses(r);see(u->v);
        if (l == r) return l;
        u->pushDown();
        if (u->v > 0) throw (int)(-1);
        int m = (l + r) >> 1;
        if (u->l->v == 0) return query(l, m, u->l);
        else return query(m+1, r, u->r);
    }

    ~STree () { delete R; }
};

const int N = 500005;
vector < int > e[N];
int a[N];
int ans[N];
STree* de;
int n;

void init() {
    scanf(I,&n);
    rep (i,n) e[i].clear();
}

void solve() {
    de = new STree();
    de->build(0,n-1);
    rep (i,n) {
        int u = a[i] = sc.nextInt();
        if (u == -1) continue;
        u--; a[i]--;
        if (i+1 != a[i]) de->modify(i+1,u-1,0,n-1,1);
        if (a[i] != n) de->modify(i,i,0,n-1,1);
        e[u].push_back(i);
    }
    rep (i,n) {
        try {
            int u = de->query(0,n-1);
            see(u);
            ans[u] = n-i;
            de->modify(u,u,0,n-1,N);
            if (a[u] != -1 && u+1 != a[u]) de->modify(u+1,a[u]-1,0,n-1,-1);
            repe (j,e[u]) de->modify(e[u][j],e[u][j],0,n-1,-1);
        } catch (int x) {
            puts("-1"); 
            return;
        }
    }
    rep (i,n) printf("%d ",ans[i]);
    puts("");
    delete de;
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
    int T; scanf(I,&T);
    while (T--) {
        init();
        solve();
    }
    return 0;
}
