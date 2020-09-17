#define ENABLE_LL
#include <bitset>
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
#define L first
#define R second
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); }

int pr[35] = {
	2,3,5,7,11,
	13,17,19,23,29,
	31,37,41,43,47,
	53,59,61,67,71,
	73,79,83,89,97,
	101,103,107,109,113,
	127,131,137,139,149
};

void init() {
     
}
int times[40];
void solve() {
    int n; cin >> n;
    vector < int > ans;
    ans.push_back(3); ans.push_back(4);ans.push_back(1);ans.push_back(4);
    int len = 4;
    while (n--) {
        rep (i,len ) ans.push_back(ans[i]);
        rep (i,len * 2) ans[i] *= 4;
        rep (i,len-1) ans[i]       += ((i % 2 == 0) ? 1 : 2);
        rep (i,len-1) ans[i+len] += ((i % 2 != 0) ? 1 : 2);
        rep (i,len * 2) ans[i] *= 4;
        ans[0]+=2; ans[len-1]+=2; ans[len*2-2]+=2;
        ans[len*2-1]+=1; ans[len]+=1; ans[len-2] += 1;
        len <<= 1;
    }
    rep (i,len) cout << bitset < 50 > ( ans[i] ) << endl;
    rep (i,len-1) if ((ans[i] & ans[i + 1]) != 0) { puts("NO"); return; }
    rep (i,len) repi (j,i+2,len-1) if ((i != 0 || j != len-1) && (ans[i] & ans[j]) == 0) { 
        cout << i << ' ' << j << endl;
        puts("NO"); }
    puts("YES");
    rep (i,len) rep (b,31) times[b] += ( (ans[i] >> b) & 1 );
    int id[40]; rep (i,31) id[i] = i;
    sort( id, id + 31, [](int a, int b) { return times[a] < times[b]; } );
    rep (i,len) {
        int res = 1, cnt = 0;
        repb (b,30,0) if ( (ans[i] >> b) & 1 ) { res *= pr[ id[b] ]; cnt++;}
        cout << res << ' ' << cnt << ' ';
        cout << (res <= (int)(1e18)) << endl;
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
