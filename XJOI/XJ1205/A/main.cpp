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
typedef pair < int , int > pr;
typedef pair < pr  , int > prr;
#define L first
#define R second

const int N = 50005;
const int INF = 0x3f3f3f3f;
vector < int > ei[N];
int ev[N] , ec[N] , ew[N];
int n;
int a[N];
int cntV , cntE;
int S = 0 , T = 1;

void addEdge(int u , int v , int w , int c) {
    ev[cntE] = v ; ec[cntE] = c ; ew[cntE] = w;
    ei[u].push_back( cntE++ );
}

void init() {
    scanf(I,&n);
    rep (i,n) scanf(I,&a[i]);
    cntV = 2;
}

void makeGraph() {
    rep (i,n) {
        addEdge(S , i + 2 , a[i] , 0);
        addEdge(i + 2 , S , 0    , 0);
    }
    rep (i,n) {
        addEdge(2 + i , T , 1 , 0);
        addEdge(T , 2 + i , 0 , 0);
    }
    rep (i,n) {
        int p = (i - 1 + n) % n;
        int s = (i + 1) % n;
        addEdge(2 + i , 2 + p , INF , 1);
        addEdge(2 + p , 2 + i , 0 ,-1);
        addEdge(2 + i , 2 + s , INF , 1);
        addEdge(2 + s , 2 + i , 0 ,-1);
    }
}

int dis[N] , inf[N] , pre[N] , inq[N];
bool SPFA() {
    memset (dis , INF , sizeof(dis));
    memset (inq , 0 , sizeof(inq));
    memset (inf , INF , sizeof(inf));
    queue < int > que;
    que.push(S);
    dis[S] = 0;
    inf[S] = INF;
    inq[S] = 1;
    while (!que.empty()) {
        int u = que.front() ; que.pop();
        inq[u] = 0;
        see(u);
        foreach (_i,ei[u]) {
            int i = ei[u][_i];
            int v = ev[i] , w = ew[i] , c = ec[i];
            if (w == 0) continue;
            ses(v) ; ses(w) ; see(c);
            if (dis[v] > dis[u] + c) {
                dis[v] = dis[u] + c;
                inf[v] = min(inf[v] , min(inf[u] , w));
                pre[v] = i;
                if (!inq[v]) {
                    que.push(v);
                    inq[v] = 1;
                }
            }
        }
    }
    return dis[T] != INF ;
}

void solve() {
    int ans = 0;
    while ( SPFA() ) { 
        ans += dis[T] * inf[T]; 
        int u = T;
        while (u != S) {
            int i = pre[u];
            ew[i    ] -= inf[T];
            ew[i ^ 1] += inf[T];
            u = ev[i ^ 1];
        }
    }
    printf(IN,ans);
}

#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    makeGraph();
    solve();
    return 0;
}
