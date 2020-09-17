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
#include <sstream>
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
 
const int N = 1005;
struct Dsu{
    int p[N * N];
 
    void init(int n) {
        rep (i,n) p[i] = i;
    }
 
    int get(int u) {
        return (u == p[u]) ? u : p[u] = get(p[u]);
    }
 
    void merge(int u , int v){
        p[ get(u) ] = get(v);
    }
 
    bool query(int u , int v) {
        return get(u) == get(v);
    }
};
 
Dsu st;
int n , m;
 
void init() {
    st.init(N * N);
}
 
void solve() {
    scanf(II,&n,&m);
    string s;
    while (getline(cin,s)) {
        if (s == "" || s == "\r" || s == "\n") continue;
        stringstream ss; ss << s;
        int x , y , a , b;
        ss >> x >> y >> a >> b;
        x--; y--; a--; b--;
        ses(x);ses(y);ses(a);see(b);
        st.merge(x * N + y , a * N + b);
    }
    int ans = 0;
    rep (i,n-1) rep (j,m) {
        if (!st.query(i * N + j , (i + 1) * N + j)) {
            st.merge (i * N + j , (i + 1) * N + j);
            ans++;
            see(ans);
        }
    }
    rep (i,n) rep (j,m-1) {
        if (!st.query(i * N + j , i * N + j + 1)) {
            st.merge (i * N + j , i * N + j + 1);
            ans += 2;
            see(ans);
        }
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
