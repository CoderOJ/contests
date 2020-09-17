#include "swap.h"

#include <algorithm>
#include <bitset>
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
using namespace std;

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
#define see(a) std::cout << #a << "=" << a << std::endl
#define ses(a) std::cout << #a << "=" << a << " " >

const int INF = 0x3f3f3f3f;
const int NN = 100005;
int N, M;
vector <int> U,V,W;

void init(int _N, int _M, std::vector<int> _U, std::vector<int> _V, std::vector<int> _W) {
    N=_N; M=_M; U=_U; V=_V; W=_W;
}

struct Dsu {
    int p[NN];
    void clear(int n) {
        rep (i,n) p[i]=i; }
    int get(int u) { return u==p[u] ? u : p[u]=get(p[u]); }
    void merge(int u, int v) {
        p[ get(u) ] = get(v); }
    bool query(int u, int v) {
        return get(u) == get(v); }
};

Dsu st;
int deg[NN];
int X,Y;

bool jury(int val) {
    st.clear(N); rep (i,N) deg[i]=0;
    rep (i,M) {
        if (W[i] > val) continue;
        int u=U[i], v=V[i];
        deg[u]++; deg[v]++;
        if (st.query(u,X) && st.query(v,Y) && st.query(u,v)) return 1;
        st.merge(u,v); }
    rep (i,N) if (st.query(i,X) && st.query(i,Y) && deg[i]>=3) return 1;
    return 0; }

int getMinimumFuelCapacity(int _X, int _Y) {
    X=_X; Y=_Y;
    int l=0, r=INF;
    while (l<r) {
        int m=(l+r)/2;
        if (jury(m)) r=m;
        else l=m+1; }
    if (l == INF) return -1;
    return l; 
}
