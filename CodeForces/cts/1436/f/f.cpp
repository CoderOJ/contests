#include <iostream>
#include <cstdio>
using namespace std; 
#ifndef _LIB_STREE
#define _LIB_STREE 1

#include <algorithm>

namespace STree {

// Template Node for maintain sums
struct NodeSum {
    int val; int tg;
    NodeSum (int val=0, int tg=0) : val(val), tg(tg) {}
    void update(int _val) {
        val += _val; tg += _val; }
    void pushUp (NodeSum a, NodeSum b) {
        val = a.val + b.val; }
    void pushDown (NodeSum &a, NodeSum &b) {
        a.val += tg; b.val += tg;
        a.tg += tg; b.tg += tg;
        tg = 0; }
};

// Template Node for maintain maxs
struct NodeMax {
    int val; int tg;
    NodeMax (int val=0, int tg=0) : val(val), tg(tg) {}
    void update(int _val) {
        val += _val; tg += _val; }
    void pushUp (NodeMax a, NodeMax b) {
        val = std::max(a.val, b.val); }
    void pushDown (NodeMax &a, NodeMax &b) {
        a.val += tg; b.val += tg;
        a.tg += tg; b.tg += tg;
        tg = 0; }
};

//Default STree for maintain maxs
template <int N, class Item=NodeMax> class STree {
protected:
    Item a[N*4];
    int g_l, g_r;

    template <class T> 
    void _modify(int l, int r, int sl, int sr, T val, int u) {
        if (sl <= l && r <= sr) {
            a[u].update(val); 
            return; }
        a[u].pushDown(a[u+u],a[u+u+1]); 
        int mid = (l+r)/2;
        if (sl <= mid)   _modify(l,mid,  sl,sr,val,u+u);
        if (sr > mid)    _modify(mid+1,r,sl,sr,val,u+u+1);
        a[u].pushUp(a[u+u],a[u+u+1]); }

    Item _query(int l, int r, int sl, int sr, int u) {
        if (sl <= l && r <= sr) {
            return a[u]; }
        a[u].pushDown(a[u+u],a[u+u+1]); 
        int mid = (l+r)/2;
        if (sl > mid)        return _query(mid+1,r,sl,sr,u+u+1); 
        else if (sr <= mid)  return _query(l,mid,sl,sr,u+u);
        else {   
            Item res; 
            res.pushUp( _query(l,mid,sl,sr,u+u), _query(mid+1,r,sl,sr,u+u+1) );
            return res; } }
public:
    void setLR(int _l, int _r) {
        g_l = _l, g_r = _r; }
    template <class T> 
    void modify(int l, int r, T val) {
        if (r > g_r) { r = g_r; }
        _modify(g_l,g_r,l,r,val,1); }
    Item query(int l, int r) {
        return _query(g_l,g_r,l,r,1); }
};

} /* namespace STree */ 

#endif /* _LIB_STREE */
#ifndef _LIB_GRAPH
#define _LIB_GRAPH

#include <cstring>
#include <vector>
#include <stack>
#include <cstring>
#include <queue>
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)

namespace Graph {

struct GraphNodeRangeException {} ;
template <int N> class Graph {
protected: 
    std::vector <int> e[N+1];
    int n;

public:
    void setNum(int _n) {
        if (n > N) throw GraphNodeRangeException();
        n = _n; }
    void clear() {
        repa (i,n) e[i].clear(); }
    void addEdge(int u, int v) {
        if (u>n || v>n || u<=0 || v<=0) throw GraphNodeRangeException();
        e[u].push_back(v); }
    std::vector <int> & getEdge(int u) {
        if (u>n || u<=0) throw GraphNodeRangeException();
        return e[u]; }
};

template <int N> class GraphScc: public Graph <N> {
private:
    std::stack <int> inNode;
    int low[N], ins[N];
    int dfnCnt, colCnt;

public:    
    int col[N], dfn[N];

    void tarjan(int u) { 
        low[u] = dfn[u] = dfnCnt++;
        ins[u] = 1; inNode.push(u);
        for (int v: this->e[u]) {
            if (dfn[v] == 0) {
                tarjan(v); if(low[v]<low[u]) {low[u]=low[v];} }
            if (ins[v]) {
                if(low[v]<low[u]) {low[u]=low[v];} } }
        if (low[u] == dfn[u]) {
            int t;
            do {
                t = inNode.top(); inNode.pop(); ins[t]=0;
                col[t] = colCnt; }
            while (t != u);
            colCnt++; } 
    }

    template <class Graph_T> void assign(Graph_T& G) {
        dfnCnt=1; colCnt=1;
        while (!inNode.empty()) inNode.pop();
        memset(low,0,sizeof(low)); memset(ins,0,sizeof(ins));
        memset(col,0,sizeof(col)); memset(dfn,0,sizeof(dfn));
        
        repa (i,this->n) if (dfn[i] == 0) tarjan(i);
        G.setNum( colCnt-1 ); G.clear();
        repa (u,this->n) for (int v: this->e[u]) {
            int ru=col[u], rv=col[v];
            if (ru != rv) G.addEdge(ru,rv); }
    }
};

struct Graph2_Edge {
    int v;
    Graph2_Edge(int v) : v(v) {} };
template <int N, class Item = Graph2_Edge> class Graph2 {
protected: 
    std::vector <int> ei[N+1];
    std::vector <Item> e;
    int n;

public:
    void setNum(int _n) {
        n = _n; }
    void clear() {
        e.clear();
        repa (i,n) ei[i].clear(); }
    void addEdge(int u, Item v) {
        ei[u].push_back(e.size());
        e.push_back(v); }    
    std::vector <int> & getEdge(int u) {
        return ei[u]; }
};

struct GraphFlow_Edge {
    int v, w; 
    GraphFlow_Edge (int v, int w) : v(v), w(w) {} };
template <int N> class GraphFlow: public Graph2 <N,GraphFlow_Edge> {
protected:

public:
    int S,T;

    void setST (int _S, int _T) { S=_S; T=_T; }
    void addEdge (int u, int v, int w) {
        this->Graph2<N,GraphFlow_Edge> :: addEdge(u,(GraphFlow_Edge){v,w}); 
        this->Graph2<N,GraphFlow_Edge> :: addEdge(v,(GraphFlow_Edge){u,0}); }
    
    class Dinic {
    private:
        int &S, &T;
        std::vector <int> *ei;
        std::vector <GraphFlow_Edge> &e;
        int dep[N], vis[N], ef[N];

        bool bfs() {
            memset(dep,0,sizeof(dep)); memset(vis,0,sizeof(vis));
            vis[S] = 1; dep[S] = 0;
            std::queue <int> que; que.push(S);
            while (!que.empty()) {
                int u=que.front(); que.pop();
                for (auto p: ei[u]) {
                    int v=e[p].v, w=e[p].w;
                    if (w==0 || vis[v]) continue;
                    dep[v] = dep[u]+1; vis[v]=1;
                    que.push(v); } }
            return vis[T]; }
        int dfs(int u, int delta=0x3f3f3f3f) {
            if (u==T || delta==0) return delta;
            int res = delta;
            for (int& _p=ef[u]; _p<(int)ei[u].size();_p++) {
                if (res == 0) { break; }
                int p = ei[u][_p]; int v=e[p].v , w=e[p].w;
                if (w==0 || dep[v]!=dep[u]+1) continue;
                int rem = dfs(v,std::min(res,w));
                e[p].w -= rem; e[p^1].w += rem;
                res -= rem; }
            return delta - res; }

    public:
        Dinic (int &S, int &T, std::vector <int> *ei, std::vector <GraphFlow_Edge> &e) :
            S(S) , T(T) , ei(ei) , e(e) {}
        int main() {
            int res = 0;
            while (bfs()) {
                int add=0;
                memset(ef,0,sizeof(ef));
                while ((add=dfs(S))) {
                    res += add;
                    memset(ef,0,sizeof(ef)); } }
            return res; }
    };

    int maxFlow() {
        Dinic *Func = new Dinic(S,T,this->ei, this->e);
        int res = Func->main();
        delete Func;
        return res; }
};

}

#undef rep
#undef repa

#endif /* _LIB_GRAPH */
#ifndef _LIB_ARRAY
#define _LIB_ARRAY 1
namespace Array {

template <int N, class T, T Zero> class Array {
protected:
    T a[N]; int upt[N];
    int t;

public:
    Array () {
        t=0; for (int i=0;i<N;i++) upt[i]=0; }
    T& operator [] (const int i) {
        if (upt[i] < t) {
            a[i] = Zero; upt[i] = t; }
        return a[i]; }
    void clear() {
        t++; }
};

}
#endif /* _LIB_ARRAY */
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <cstring>
#include <bitset>
#include <sstream>

#ifdef ENABLE_LL
#define int long long
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
#define repe(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)

typedef pair < int , int > pr; 
typedef pair < pr  , int > prr; 
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); } 
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); } 
void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } } 
bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }
#define L first
#define R second

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#define ses(a) std::cout << #a << "=" << a << " " 
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#define ses(a)
#endif

#ifndef CUSTOM_MAIN

void preInit();
void init(); 
void solve(); 

int32_t main(){ 
preInit();

#ifdef MULTIPLE_TEST_CASES_WITH_T
int T; 

#ifdef _LIB_SCANNER
T = sc.nextInt();
#else
scanf("%d",&T); 
#endif /* _LIB_SCANNER */

while(T--) {init(); solve();} 
#else

#ifdef MULTIPLE_TEST_CASES_WITHOUT_T 
while(1) {
    try {init(); } 
    catch(bool t) {return 0;} 
    solve();
}
#else
init(); solve(); 
#endif /* MULTIPLE_TEST_CASES_WITHOUT_T  */

#endif /* MULTIPLE_TEST_CASES_WITH_T */
    return 0;
}

#endif /* CUSTOM_MAIN */

// my code begins here








void preInit() {

}

void init() {
     
}

void solve() {

}
