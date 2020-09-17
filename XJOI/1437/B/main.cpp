#pragma GCC optimize(2)
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
#define repe(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)
typedef pair < int , int > pr; typedef pair < pr  , int > prr;
#define L first
#define R second
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); }
class Scanner{ private: istream& ist;public: Scanner(istream& in):ist(in){} string next(){ string r; ist >> r; return r; } string nextLine(){ string r; getline(ist,r); return r; } int nextInt(){ int r; ist >> r; return r; } double nextDouble(){ double r; ist >> r; return r; } char nextChar(){ char r; ist>>r; return r;} }; Scanner sc(cin);
void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } }
bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }

const int N=105;
int altitude[N][N];
int n, m, p;
int spots[N];
vector < pr > e[N*N];

inline int code (int a, int b) {
    return a*N + b;
}

const int Move[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
void genE() {
    rep (i,n) rep (j,m) {
        int u = code(i, j);
        rep (c, 4) {
            int vx = i + Move[c][0]; 
            int vy = j + Move[c][1]; 
            if (vx < 0 || vx >= n || vy < 0 || vy >= m) continue;
            int v = code(vx, vy);
            int delta = altitude[i][j] - altitude[vx][vy];
            int w = delta * delta + 1;
            e[u].push_back( pr(v,w) );
            e[v].push_back( pr(u,w) );
        }
    } 
}

void init() {
    scanf(II,&n,&m);
    rep (i,n) rep (j,m) scanf(I,&altitude[i][j]);
    scanf(I,&p); 
    rep (i,p) {
        int a, b; scanf(II,&a,&b);
        spots[i] = code(a-1, b-1);
    }
    genE();
}

int dis[11][N*N];
void Dis(int* res, int st) {
    rep (i,N*N) res[i] = 0x3f3f3f3f3f3f3f3f;
    res[st] = 0;
    priority_queue < pr , vector <pr> , greater <pr> > que;
    que.push( pr(0, st) );
    while (!que.empty()) {
        pr pos = que.top(); que.pop();
        int u=pos.R , w=pos.L;
        if (w != res[u]) continue;
        repe (i, e[u]) {
            pr _v = e[u][i];
            int v = _v.L, vw = _v.R;
            if (checkMin(res[v], w+vw)) {
                ses(u);ses(v);see(res[v]);
                que.push( pr(res[v], v) );
            }
        }
    } 
}

inline int calc(int* v) {
    int res = 0;
    rep (i,p-1) {
        res += dis[ v[i] ][ spots[v[i+1]] ];
    }
    ses(dis[10][ spots[v[0]] ]);see(res);
    return res + dis[10][ spots[v[0]] ];
}

void solve() {
    rep (i,p) Dis(dis[i], spots[i]);
    Dis(dis[10], code(0,0));
    int t[10];
    rep (i,p) t[i] = i;
    int res = 0x3f3f3f3f3f3f3f3f;
    do {
        checkMin(res, calc(t)); 
    } while (next_permutation(t , t+p));
    printf(IN,res);
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
try { 

#ifndef CUSTOM_MAIN
#ifdef MULTIPLE_TEST_CASES_WITH_T

int T; scanf("%d",&T); while(T--) {init(); solve();}

#else
#ifdef MULTIPLE_TEST_CASES_WITHOUT_T

while(1) {try{init(); } catch(bool t){return 0;} solve(); }

#else

init(); solve();

#endif
#endif
#endif

} catch (const char* s) { return 0; }
    return 0;
}

