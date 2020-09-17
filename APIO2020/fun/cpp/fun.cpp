#include "fun.h"

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
#define ses(a) std::cout << #a << "=" << a << " " 


const int NN=505;
vector <int> e[NN];
int N;

int dep[NN]; int fa[NN];
int dis[NN][NN];

void dfs(int u, int f) {
    dep[u] = dep[f]+1;
    fa[u]=f;
    for (int v:e[u]) {
        if (v==f) continue;
        dfs(v,u); } }

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u,v);
    while (dep[u]>dep[v]) u=fa[u];
    while (u!=v) { u=fa[u]; v=fa[v]; }
    return u; }

void initDis() {
    rep (i,N) rep (j,N) dis[i][j] = dep[i]+dep[j] - dep[lca(i,j)]*2; }

bool vis[NN]; 
vector <int> ans;

std::vector<int> createFunTour(int _N, int Q) {
    N=_N;
    rep (i,N) rep (j,i) {
        int h = hoursRequired(i,j);
        if (h==1) { e[i].push_back(j); e[j].push_back(i); } }
    dfs(0,N);
    initDis();
    int st=0;
    rep (i,N) if (dep[i]>dep[st]) st=i;
    vis[st]=1; ans.push_back(st);
    rep (i,N-1) {
        int nx=0, nxd=-1;
        rep (j,N) {
            if (vis[j]) continue;
            if (checkMax(nxd, dis[j][st])) nx=j; }
        vis[nx]=1; ans.push_back(nx); st=nx; }
    return ans;
}
