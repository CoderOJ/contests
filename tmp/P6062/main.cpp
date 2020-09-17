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
#include <bitset>
#include <sstream>
using namespace std; 
#ifndef CUSTOM_MAIN
void init(); void solve(); int main(){ 
#ifdef MULTIPLE_TEST_CASES_WITH_T
int T; scanf("%d",&T); while(T--) {init(); solve();} 
#else
#ifdef MULTIPLE_TEST_CASES_WITHOUT_T 
while(1) {try{init(); } catch(bool t){return 0;} solve(); } 
#else
init(); solve(); 
#endif
#endif
return 0; }
#endif
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
#define L first
#define R second
typedef pair < int , int > pr; typedef pair < pr  , int > prr; template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); } template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); } void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } } bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }
class Scanner { private: static const int BUFFER_SIZE = 10000; char buff[BUFFER_SIZE]; int buffPos, buffLim; public: Scanner () { buffLim = fread(buff, 1, BUFFER_SIZE, stdin); buffPos = 0; } private: inline void flushBuff() { buffLim = fread(buff, 1, BUFFER_SIZE, stdin); if (buffLim==0) { buff[buffLim++] = '\n'; } buffPos = 0; } inline bool isWS(char t) { return t==' ' || t=='\n'; } inline bool isDig(char t) { return t>='0' && t<='9'; } void nextPos() { buffPos++; if (buffPos == buffLim) { flushBuff(); } } 
#define getChar() buff[buffPos]
public: inline char getchar() { char ch=getChar(); nextPos(); return ch; } inline void next(char* s) { while ( isWS(getChar()) ) { nextPos(); } while ( !isWS(getChar()) ) { *s = getChar(); s++; nextPos(); } *s = '\0'; } inline void nextLine(char* s) { while ( getChar()!='\n' ) { nextPos(); } if ( getChar()=='\n' ) { nextPos(); } while ( getChar() != '\n' ) { *s = getChar(); s++; buffPos++; } *s = '\0'; } inline int nextInt() { while ( !isDig(getChar()) ) { nextPos(); } int sign = (getChar() == '-') ? nextPos(),-1 : 1; int res = 0; while (isDig(getChar())) { res = res*10 + getChar()-'0'; nextPos(); } return res * sign; } inline double nextDouble() { while ( isWS(getChar()) ) { nextPos(); } int sign = (getChar() == '-') ? nextPos(),-1 : 1; double res = 0; while (isDig(getChar())) { res = res * 10 + getChar()-'0'; nextPos(); } if (getChar() == '.') { nextPos(); double ep = 1; while (isDig(getChar())) { ep *= 0.1; res += ep * (getChar()-'0'); nextPos(); } } return sign * res; } inline char nextChar() { while (isWS(getChar())) nextPos(); char res = getChar(); nextPos(); return res; } 
#undef getChar
}; 

struct Graph_Edge {
    int v;
    Graph_Edge(int v) : v(v) {} };
template <int N, class Item = Graph_Edge> class Graph {
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
template <int N> class GraphFlow: public Graph <N,GraphFlow_Edge> {
protected:

public:
    int S,T;

    void setST (int _S, int _T) { S=_S; T=_T; }
    void addEdge (int u, int v, int w) {
        ses(u);ses(v);see(w);
        this->Graph<N,GraphFlow_Edge> :: addEdge(u,(GraphFlow_Edge){v,w}); 
        this->Graph<N,GraphFlow_Edge> :: addEdge(v,(GraphFlow_Edge){u,0}); }
    
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

const int N = 5505;
const int R = 55;
GraphFlow <N> e;
char s[R][R];
int n,m;

void init() {
    scanf(II,&n,&m);
    rep (i,n) scanf("%s",s[i]);
}

const int INF = 0x3f3f3f3f;
const int S = 1;
const int T = 2;

int rInd[R][R], cInd[R][R];

void solve() {
    e.setNum(2*n*m+n+m+2);
    e.setST(S,T);
    int nCnt = T;
    rep (i,n) rep (j,m) {
        if (j==0 || (s[i][j]=='*' && s[i][j-1] == '.')) { 
            nCnt++;
            e.addEdge(S,nCnt,1); }
        if (s[i][j] == '*') rInd[i][j] = nCnt; }
    rep (i,m) rep (j,n) {
        if (j==0 || (s[j][i]=='*' && s[j-1][i] == '.')) { 
            nCnt++;
            e.addEdge(nCnt,T,1); }
        if (s[j][i] == '*') cInd[j][i] = nCnt; }
    rep (i,n) rep (j,m) if (s[i][j] == '*') e.addEdge( rInd[i][j], cInd[i][j], INF );
    printf(IN,e.maxFlow());
}

