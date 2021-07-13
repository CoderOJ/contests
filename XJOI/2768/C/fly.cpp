#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 200010
#define ll long long
using namespace std;
int nxt[N<<1],to[N<<1],w[N<<1],head[N],cnt;
void adde(int u,int v,int w1)
{
    nxt[++cnt]=head[u];to[cnt]=v;w[cnt]=w1;
    head[u]=cnt;
}
int dfn[N],id[N],siz[N],son[N],fa[N],idc;
int top[N],dep[N];
int wr[N];
void dfs1(int u,int p)
{
    fa[u]=p;siz[u]=1;dep[u]=dep[p]+1;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];if(v==p) continue;
        dfs1(v,u);wr[v]=w[i];
        if(siz[son[u]]<siz[v]) son[u]=v;
    }
}
void dfs2(int u,int topp)
{
    top[u]=topp;id[dfn[u]=++idc]=u;
    if(son[u]) dfs2(son[u],topp);
    for(int i=head[u];i;i=nxt[i]) if(to[i]!=son[u] && to[i]!=fa[u]) dfs2(to[i],to[i]);
}
int lca(int x,int y)
{
    for(;top[x]!=top[y];x=fa[top[x]]) if(dep[top[x]]<dep[top[y]]) swap(x,y);
    return dep[x]<dep[y]?x:y;
}
int dist(int x,int y){return dep[x]+dep[y]-2*dep[lca(x,y)];}
vector<int>g[N];
int st[N],tt;
int q[N],qt;
bool bq[N];
void build()
{
    for(int i=1;i<=qt;i++) bq[q[i]]=true;
    sort(q+1,q+qt+1,[&](int x,int y){return dfn[x]<dfn[y];});
    tt=0;
    st[++tt]=1;
    for(int i=1;i<=qt;i++)
    if(q[i]!=1)
    {
        int x=lca(st[tt],q[i]);
        if(x!=st[tt])
        {
            for(;dep[x]<dep[st[tt-1]];tt--)
                g[st[tt-1]].push_back(st[tt])/*,printf("link %d %d\n",st[tt-1],st[tt])*/;
            g[x].push_back(st[tt--])/*,printf("link %d %d\n",x,st[tt+1])*/;
            if(x!=st[tt]) st[++tt]=x;
        }
        st[++tt]=q[i];
    }
    while(--tt) g[st[tt]].push_back(st[tt+1])/*,printf("link %d %d\n",st[tt],st[tt+1])*/;
}
int n;
namespace segt{
    ll val[N<<2],tag[N<<2];
    void setg(int u,int l,int r,ll t){val[u]+=(r-l+1)*t;tag[u]+=t;}
    void build(int u,int l,int r)
    {
        if(l==r){val[u]=wr[id[l]];return;}
        int mid=(l+r)>>1;build(u<<1,l,mid);build(u<<1|1,mid+1,r);
        val[u]=val[u<<1]+val[u<<1|1];
    }
    void push(int u,int l,int r)
    {
        if(!tag[u]) return;
        int mid=(l+r)>>1;setg(u<<1,l,mid,tag[u]);setg(u<<1|1,mid+1,r,tag[u]);
        tag[u]=0;
    }
    void insert(int u,int l,int r,int L,int R,ll v)
    {
        if(L<=l && r<=R){setg(u,l,r,v);return;}
        push(u,l,r);int mid=(l+r)>>1;
        if(L<=mid) insert(u<<1,l,mid,L,R,v);
        if(R>mid) insert(u<<1|1,mid+1,r,L,R,v);
        val[u]=val[u<<1]+val[u<<1|1];
    }
    ll answer(int u,int l,int r,int L,int R)
    {
        if(L<=l && r<=R) return val[u];
        push(u,l,r);int mid=(l+r)>>1;ll w=0;
        if(L<=mid) w+=answer(u<<1,l,mid,L,R);
        if(R>mid) w+=answer(u<<1|1,mid+1,r,L,R);
        return w;
    }
    void add(int l,int r,ll v){insert(1,1,n,l,r,v);}
    ll qry(int l,int r){return answer(1,1,n,l,r);}
}
void add_line(int x,int y,ll v)
{
    for(;top[x]!=top[y];segt::add(dfn[top[x]],dfn[x],v),x=fa[top[x]]) if(dep[top[x]]<dep[top[y]]) swap(x,y);
    if(dep[x]>dep[y]) swap(x,y);
    segt::add(dfn[x]+1,dfn[y],v);
}
ll qry(int x,int y)
{
    ll v=0;
    for(;top[x]!=top[y];v+=segt::qry(dfn[top[x]],dfn[x]),x=fa[top[x]]) if(dep[top[x]]<dep[top[y]]) swap(x,y);
    if(dep[x]>dep[y]) swap(x,y);
    v+=segt::qry(dfn[x]+1,dfn[y]);return v;
}
ll ans=0;
namespace xu{
    int siz[N],son[N];
    void dfs0(int u)
    {
        siz[u]=bq[u];son[u]=0;
        for(int v:g[u]){dfs0(v);siz[u]+=siz[v];if(siz[son[u]]<siz[v]) son[u]=v;}
    }
    struct node{
        ll c,v;
        node(ll C=0,ll V=0):c(C),v(V){}
    };
    node operator +(const node a,const node b){return node(a.c+b.c,a.v+b.v);}
    node val[N*20];int ls[N*20],rs[N*20],tot;
    int ton[N],top;
    int newnode(){return top?ton[top--]:++tot;}
    void del(int &u){val[u]=node();ton[++top]=u;u=0;}
    void insert(int &u,int l,int r,int p,node v)
    {
        if(!u) u=newnode();val[u]=val[u]+v;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(p<=mid) insert(ls[u],l,mid,p,v);
        else insert(rs[u],mid+1,r,p,v);
    }
    node qry(int u,int l,int r,int L,int R)
    {
        if(!u || L>R || l>R || L>r) return node();
        if(L<=l && r<=R) return val[u];
        int mid=(l+r)>>1;
        if(R<=mid) return qry(ls[u],l,mid,L,R);
        if(L>mid) return qry(rs[u],mid+1,r,L,R);
        return qry(ls[u],l,mid,L,R)+qry(rs[u],mid+1,r,L,R);
    }
    node dd[N];int dp[N],dt;
    void get(int &u,int l,int r)
    {
        if(!u) return;
        if(l==r){++dt;dd[dt]=val[u];dp[dt]=l;return ;}
        int mid=(l+r)>>1;
        get(ls[u],l,mid);get(rs[u],mid+1,r);
    }
    void erase(int &u){if(!u) return;erase(ls[u]);erase(rs[u]);del(u);}
    int ql,qr;
    void dfs(int u,int &rt)
    {
        if(son[u]) dfs(son[u],rt);
        ll wp=::qry(1,u);
        int L=ql+dep[u]*2,R=qr+dep[u]*2;
        for(int v:g[u])
        if(v!=son[u])
        {
            int rt1=0;
            dfs(v,rt1);
            dt=0;get(rt1,1,n);
            erase(rt1);
            node w;
            for(int i=1;i<=dt;i++)
            {
                node v=qry(rt,1,n,max(L-dp[i],1),R-dp[i]);
                w=w+node(v.c*dd[i].c,v.v*dd[i].c+dd[i].v*v.c);
            }
            for(int i=1;i<=dt;i++) insert(rt,1,n,dp[i],dd[i]);
            ans+=w.v-2*w.c*wp;
        }
        if(bq[u])
        {
            node w;
            node v=qry(rt,1,n,max(L-dep[u],1),R-dep[u]);
            ans+=v.v-v.c*wp;
            insert(rt,1,n,dep[u],node(1,wp));
        }
    }
}
void solve(int l,int r)
{
    int rt=0;xu::ql=l;xu::qr=r;
    xu::dfs0(1);
    xu::dfs(1,rt);xu::erase(rt);
    printf("%lld\n",ans);
}
void dfs_clear(int u){for(int v:g[u]) dfs_clear(v);g[u].clear();}
void clear()
{
    for(int i=1;i<=qt;i++) bq[q[i]]=false;
    dfs_clear(1);ans=0;
}
int main()
{
    int m;
    scanf("%d%d",&n,&m);
    for(int i=1,u,v,w;i<n;i++) scanf("%d%d%d",&u,&v,&w),adde(u,v,w),adde(v,u,w);
    dfs1(1,0);dfs2(1,1);
    segt::build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int op,x,y,z;
        scanf("%d%d%d%d",&op,&x,&y,&z);
        if(op==1) add_line(x,y,z);
        else
        {
            qt=z;
            for(int i=1;i<=qt;i++) scanf("%d",&q[i]);
            build();
            solve(x,y);
            clear();
        }
    }
    return 0;
}