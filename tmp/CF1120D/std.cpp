#include<bits/stdc++.h>
#define ll long long
#define now edge[i].v
#define rep(i,l,r) for(int i=l;i<=r;i++)
using namespace std;
const int SZ=2e5+7;
ll ans;
int cnt;
int L,R;
int u,v;
int n,T;
int w[SZ];
int fa[SZ];
int sz[SZ];
bool vis[SZ];
int head[SZ];
bool f[SZ];
int l[SZ],r[SZ];
struct wxp{
    int v,nxt;
}edge[SZ<<1];
struct pb{
    int u,v,w,o;
}E[SZ];
bool cmp(pb p1,pb p2){
    return p1.w<p2.w;
}
int getfa(int x){
    return fa[x]==x?x:fa[x]=getfa(fa[x]);
}
void add(int u,int v){
    edge[++cnt]=(wxp){v,head[u]};
    head[u]=cnt;
}
void dfs(int x){
    sz[x]=1;
    vis[x]=1;
    for(int i=head[x];i;i=edge[i].nxt)
    if(!vis[now]){
        dfs(now);
        sz[x]+=sz[now];
        l[x]=min(l[x],l[now]);
        r[x]=max(r[x],r[now]);
    }
    if(sz[x]==1) l[x]=r[x]=++T;
    E[x]=(pb){l[x],r[x]+1,w[x],x};
}
int main(){
    scanf("%d",&n);
    rep(i,1,n) scanf("%d",&w[i]);
    rep(i,1,n-1){
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    memset(l,0x3f,sizeof(l));
    dfs(1);
    sort(E+1,E+n+1,cmp);
    rep(i,1,T+1) fa[i]=i;
    int sum=0;
    for(L=1;L<=n;L=R+1){
        R=L;
        while(E[R+1].w==E[L].w&&R<n) R++;
        rep(i,L,R){
            u=E[i].u,v=E[i].v;
            if(getfa(u)!=getfa(v)) f[E[i].o]=1,sum++;
        }
        rep(i,L,R){
            u=E[i].u,v=E[i].v;
            if(getfa(u)!=getfa(v)){
                ans+=1ll*E[i].w;
                fa[fa[u]]=fa[v];
            }
        }
    }
    printf("%lld %d\n",ans,sum);
    rep(i,1,n) if(f[i]) printf("%d ",i);
}
