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
#include <stack>
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
const int M = 1000005;

struct Edge {
    int v , w;
    Edge () {}
    Edge (int v , int w) : v(v) , w(w) {}
};

class Graph {
public: 
    vector < Edge > e[N];

    void addEdge(int u , Edge v) {
        e[u].push_back(v);
    }
};

class GraphWithScc : public Graph{
private:
    int low[N] , dfn[N] , ins[N];
    stack < int > tar;
    int cnt;

public:
    int bel[N];
    vector < vector < int > > scc;
    GraphWithScc() { cnt=0; }

    void tarjan(int u) {
        dfn[u] = low[u] = cnt++;
        tar.push(u); ins[u] = 1;
        foreach (i,e[u]) {
            int v = e[u][i].v;
            if ( !dfn[v] ) {
                tarjan(v);
                checkMin (low[u], low[v]);
            } else if ( ins[v] ){
                checkMin (low[u], low[v]);
            }
        }
        if (dfn[u] == low[u]) {
            vector < int > pos;
            int uu;
            do {
                uu = tar.top(); tar.pop(); ins[uu] = 0;
                bel[uu] = scc.size();
                pos.push_back(uu);
            } while (uu != u);
            scc.push_back(pos);
        }
    }
};

class GraphWithSp : public Graph{
private:
    priority_queue < pr , vector < pr > , greater < pr > > que;
public:
    int dis[N];
    
    GraphWithSp() { memset(dis,0x3f,sizeof(dis)); }

    void sp(int s) {
        dis[s] = 0;
        que.push( pr(0,s) );
        while (!que.empty()) {
            pr pos = que.top(); que.pop();
            int u = pos.R, d = pos.L;
            if (d != dis[u]) continue;
            foreach (i,e[u]) {
                int v = e[u][i].v , w = e[u][i].w;
				if (checkMin(dis[v], d + w)) {
                    que.push( pr(dis[v], v) );
                }
            }
        }
    }
};

int n , m;
GraphWithScc ori;
GraphWithSp  lac;
void init() {
    scanf(II,&n,&m);
    rep (i,m) {
        int u, v, w; scanf(III,&u,&v,&w);
        ori.addEdge(u, Edge(v,w));
    }
    ori.tarjan(1);
    repa (u,n) foreach(i,ori.e[u]) {
        int v = ori.e[u][i].v;
        if (ori.bel[u] != ori.bel[v]) lac.addEdge(ori.bel[u], Edge(ori.bel[v], ori.e[u][i].w) );
    }
}

void solve() {
    lac.sp( ori.bel[1] );
    printf(IN, lac.dis[ ori.bel[n] ]);
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    return 0;
}
