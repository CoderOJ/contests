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

const int N = 200005;
vector < int > ei[N];
int ev[N] , ew[N] , eb[N];
int n;
int cnt;

void addEdge(int u , int v , int w) {
    ew[cnt] = w; ev[cnt] = v; eb[cnt] = 0;
    ei[u].push_back(cnt++);
}

void init() {
    scanf(I,&n);
    rep (i,n) {
        int u , v , w; scanf(III,&u,&v,&w); u--;v--;
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
}

int ind[N];

int find(int u) {
    rep (i,(int)ei[u].size()) if (!eb[ei[u][i]]) return ei[u][i];
    return -1;
}

int ans = 0x3f3f3f3f;

void solve() {
    rep (i,n) ind[i] = ei[i].size();
    set < int > st; rep (i,n) if (ind[i] == 1) { st.insert(i); see(i); }
    while (!st.empty()) {
        int u = *st.begin() ; st.erase(u);
        int fid = find(u) , v = ev[fid];
        see(u);
        st.erase(v);
        ans = min(ans , ew[fid]);
        eb[fid] = 1; eb[fid ^ 1] = 1;
        ind[v] = ind[u] = 0;
        foreach (_i,ei[v]) {
            int i = ei[v][_i]; 
            if (eb[i]) continue;
            int nv = ev[i];
            eb[i] = 1; eb[i ^ 1] = 1;
            ind[nv]--;
            if (ind[nv] == 0) { puts("no answer"); exit(0); }
            if (ind[nv] == 1) st.insert(nv);
        }
    }
}

int findB(int u , int  v) {
    foreach(i,ei[u]) if (!eb[ ei[u][i] ] && ev[ ei[u][i] ] == v) return ei[u][i];
    return -1;
}

bool use[N];
void solve2() {
    int n2 = 0; rep (i,n) if (ind[i] == 2) n2++;
    if (n2 % 2 == 1) { puts("no answer"); exit(0); }
    if (n2 == 0) return ;
    vector < int > nv;

    int u; rep (i,n) if (ind[i] == 2) u = i; use[u] = 1; nv.push_back(u);
    rep (i,n2 - 1) {
        int id; while (use[ ev[id=find(u)] ]) { eb[id] = 1; eb[id ^ 1] = 1; }
        use[ ev[id] ] = 1;
        nv.push_back(ev[id]);
        u = ev[id];;
    }   

    see(ans);
    see(n2);
    rep (i,n2) { ses(nv[i]); see(ind[nv[i]]); }

    vector < int > ne;
    rep (i,n2) ne.push_back( ew[ findB(nv[i] , nv[ (i+1)%(int)nv.size() ]) ] );
    rep (i,n2) see(ne[i]);
    int ans1 = 0x3f3f3f3f , ans2 = 0x3f3f3f3f;
    rep (i,n2) {
        int& tans = (i % 2 == 0) ? ans1 : ans2;
        tans = min(tans , ne[i]);
    }
    ses(ans1);see(ans2);
    ans = min(ans , max(ans1,ans2) );
}

#ifdef ENABLE_LL
undef int
#endif
int main(){
    init();
    solve();
    solve2();
    printf(IN,ans);
    return 0;
}
