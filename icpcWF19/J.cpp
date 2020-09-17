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

#define int long long
#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
typedef pair < int , int > Point;

const int P = 505;
const int H = 55;
int par[P][H];
int b[P];
int f[P];
int s[P];
int p,h;
vector < int > taken;

void init(){
    scanf("%lld%lld",&p,&h);
    rep (i,p) rep (j,h) scanf("%lld",&par[i][j]);
    rep (i,p) sort(par[i] , par[i] + h);
    rep (i,p) rep (j,h) {
        taken.push_back(par[i][j]);
        if (par[i][j] != 1) taken.push_back(par[i][j] - 1);
        taken.push_back(par[i][j] + 1);
    }
    sort (taken.begin() , taken.end());
}

void query (int key) {
    rep (i,p) {
        while (f[i] < h && par[i][ f[i] ] <= key) {
            f[i]++;
            s[i] += par[i][f[i] - 1];
        }
    }
    vector < Point > e;
    rep (i,p){
        int foo = s[i] + (h - f[i]) * key;
        e.push_back( Point ( foo , i ) );
    }
    sort (e.begin() , e.end());
    int foo ;
    for (int i = p - 1;i>=0;i--) {
        if (i == p - 1 || e[i].first != e[i + 1].first) foo = i + 1;
        b[ e[i].second ] = min(b[ e[i].second ],foo);
    }
}

void solve() {
    memset (b , 0x3f  ,sizeof(b));
    rep (i,p * h * 3) if (!i || taken[i] != taken[i - 1]) query(taken[i]);
    rep (i,p) printf("%lld\n",b[i]);
}

#undef int
int main(){
    init();
    solve(); 
    return 0;
}
