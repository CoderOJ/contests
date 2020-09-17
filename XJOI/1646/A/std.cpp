#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+5;
int n,m,E,ans=0;
int pnt[N*2],nxt[N*2],head[N],far[N][20],dep[N],cnt[N];
void add(int u,int v) {pnt[++E]=v,nxt[E]=head[u],head[u]=E;}
void prp(int u,int fa) {
    far[u][0] = fa;
    dep[u] = dep[fa] + 1;
    for(int i=head[u];i;i=nxt[i]) {
        int v = pnt[i];
        if(v == fa) continue;
        prp(v,u);
    }
}
int LCA(int u,int v) {
    if(dep[u] < dep[v]) swap(u,v);
    int dlt = dep[u] - dep[v];
    for(int i=19;i>=0;i--) {
        if(dlt & (1<<i)) u = far[u][i];
    }
    if(u == v) return v;
    for(int i=19;i>=0;i--) {
        if(far[u][i] != far[v][i]) {
            u = far[u][i];
            v = far[v][i];
        }
    }
    return far[u][0];
}
void dfs(int u,int fa) {
    for(int i=head[u];i;i=nxt[i]) {
        int v = pnt[i];
        if(v == fa) continue;
        dfs(v,u);
        cnt[u] += cnt[v];
    }
    if(u == 1) return ;
    if(cnt[u] > 1) ans += 0;
    if(cnt[u] == 0) ans += m;
    if(cnt[u] == 1) ans += 1;
}
signed main() {
    scanf("%lld%lld",&n,&m);
    for(int i=1,u,v;i<n;i++) {
        scanf("%lld%lld",&u,&v);
        add(u,v),add(v,u);
    }
    prp(1,0);
    for(int j=1;j<20;j++) for(int i=1;i<=n;i++) far[i][j] = far[far[i][j-1]][j-1];
    for(int u,v,i=1;i<=m;i++) {
        scanf("%lld%lld",&u,&v);
        cnt[u]++;cnt[v]++;
        cnt[LCA(u,v)]-=2;
    }
    dfs(1,0);
    printf("%lld\n",ans);
    return 0;
}

