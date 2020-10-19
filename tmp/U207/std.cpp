//Wan Hong 3.1
//home
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
typedef long long ll; typedef unsigned un; typedef std::pair<ll,ll> pll; typedef std::string str;
ll read() { ll x=0,f=1; char c; do { c=getchar(); if(c=='-')f=-1; }while(c<'0'||c>'9'); do { x=x*10+c-'0'; c=getchar(); }while(c>='0'&&c<='9'); return f*x; } ll min(ll a,ll b) { return a<b?a:b; } ll max(ll a,ll b) { return a>b?a:b; } bool umin(ll &a,ll b) { if(b<a)return a=b,1; return 0; } bool umax(ll &a,ll b) { if(b>a)return a=b,1; return 0; }
#define INF (1ll<<58)
/**********/
#define MAXN 100011
struct LCT
{
    ll fa[MAXN],son[MAXN][2],tag[MAXN],ans[MAXN],val[MAXN];
    void pushup(ll x)
    {
        ans[x]=ans[son[x][0]]^ans[son[x][1]]^val[x];
    }
    void pushdown(ll x)
    {
        if(tag[x])
        {
            std::swap(son[x][0],son[x][1]);
            tag[son[x][0]]^=1,tag[son[x][1]]^=1;
            tag[x]=0;
        }
    }
    bool not_root(ll x){return son[fa[x]][0]==x||son[fa[x]][1]==x;}
    void rotate(ll x)
    {
        ll y=fa[x],z=fa[y],k=(son[y][1]==x);
        if(not_root(y))son[z][son[z][1]==y]=x;
        fa[x]=z;
        son[y][k]=son[x][!k],fa[son[x][!k]]=y;
        son[x][!k]=y,fa[y]=x;
        pushup(y),pushup(x);
    }
    ll s[MAXN];
    void splay(ll x)
    {
        ll top=0;
        s[++top]=x;
        for(ll y=x;not_root(y);y=fa[y])s[++top]=fa[y];
        while(top)pushdown(s[top--]);
        while(not_root(x))
        {
            ll y=fa[x];
            if(not_root(y))
                rotate((son[y][1]==x)==(son[fa[y]][1]==y)?y:x);
            rotate(x);
        }
        pushup(x);
    }
    void access(ll x)
    {
        for(ll y=0;x;y=x,x=fa[x])
            splay(x),val[x]=val[x]^ans[son[x][1]]^ans[y],son[x][1]=y,pushup(x);
    }
    void make_root(ll x){access(x),splay(x),tag[x]^=1;}
    void modify(ll x,ll k)
    {
        make_root(x),val[x]^=k;
    }
    void link(ll x,ll y)
    {
        make_root(x),make_root(y);
        fa[x]=y,val[y]^=ans[x],pushup(y);
    }
    ll split(ll x,ll y)
    {
        make_root(x),access(y),splay(y);
        std::cout << ans[x] << ' ' << val[x] << std::endl;
        return ans[x];
    }
    void cut(ll x,ll y){split(x,y),son[y][0]=fa[x]=0,pushup(y);}
}t;
struct Query
{
    ll x,y,f;
}a[MAXN*3];
int main()
{
    ll cnt=0,tot=0;
    srand(19260817);
    ll id=read(),n=read(),m=read();
    for(ll i=1;i<n;++i)t.link(read(),read());
    while(m--)
    {
        ll op=read();
        if(op==1)t.cut(read(),read()),t.link(read(),read());
        else if(op==2)
        {
            ll f=rand(),x=read(),y=read();
            //printf("rand=%lld\n",f);
            t.modify(x,f),t.modify(y,f);
            tot^=f;
            a[++cnt]={x,y,f};
        }
        else if(op==3)
        {
            ll x=read();
            t.modify(a[x].x,a[x].f),t.modify(a[x].y,a[x].f);
            tot^=a[x].f;
        }
        else puts(t.split(read(),read())==tot?"YES":"NO");
    }
    return 0;
}

