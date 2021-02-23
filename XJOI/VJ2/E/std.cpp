#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
#define ll long long
#define maxn 200005
int n,m;
vector<int>e[maxn];
inline void adde(int u,int v){e[u].push_back(v);}
 
ll k[maxn],b[maxn];
int mx,tot,tag[maxn<<2];
inline int ins(ll K,ll B){tot++,k[tot]=K,b[tot]=B;return tot;}
inline ll f(int i,ll j){return k[i]*j+b[i];}
void modify(int p,int l,int r,int x)
{
	if(!tag[p])return tag[p]=x,void();
	if(l==r){
		if(f(x,l)>f(tag[p],l))tag[p]=x;
		return;
	}
	int mid=l+r>>1;
	if(f(x,mid)>f(tag[p],mid))swap(tag[p],x);
	if(k[tag[p]]>k[x]) modify(p<<1,l,mid,x);
	else modify(p<<1|1,mid+1,r,x);
}
ll ask(int p,int l,int r,int x)
{
	if(l==r)return f(tag[p],x);
	int mid=l+r>>1;ll res=f(tag[p],x);
	if(x<=mid)res=max(res,ask(p<<1,l,mid,x));
	else res=max(res,ask(p<<1|1,mid+1,r,x));
	return res;
}
inline void clr(int qaq){
	mx=qaq,tot=0;
	For(i,1,mx*4)tag[i]=0;
}
 
int sz[maxn],mxp[maxn],rt,allsum;
bool vis[maxn];
ll res,a[maxn];
void getrt(int u,int pa)
{
	sz[u]=1,mxp[u]=0;
	for(auto v:e[u]){
		if(vis[v]||v==pa)continue;
		getrt(v,u);
		sz[u]+=sz[v];
		mxp[u]=max(mxp[u],sz[v]);
	}mxp[u]=max(mxp[u],allsum-sz[u]);
	if(mxp[u]<mxp[rt])rt=u;
}
 
void query(int u,int pa,ll s,ll ss,ll d){
	++d,s+=a[u],ss+=s;
	for(auto v:e[u])if(!vis[v]&&v!=pa)query(v,u,s,ss,d);
	if(e[u].size()==1)res=max(res,ss+ask(1,1,mx,d));
}
void mdf(int u,int pa,ll s,ll ss,ll d){
	++d,s+=a[u],ss+=d*a[u];
	for(auto v:e[u])if(!vis[v]&&v!=pa)mdf(v,u,s,ss,d);
	if(e[u].size()==1) modify(1,1,mx,ins(s,ss));
}
 
void solve(int u)
{
	vis[u]=1;
	
	clr(sz[u]);
	for(auto v:e[u]){
		if(vis[v])continue;
		query(v,u,a[u],a[u],1),mdf(v,u,0,0,0);
	}
	res=max(res,a[u]+ask(1,1,mx,1));
	clr(sz[u]);
	for(int i=e[u].size()-1;i>=0;--i){
		int v=e[u][i];
		if(vis[v])continue;
		query(v,u,a[u],a[u],1),mdf(v,u,0,0,0);
	}
	
	for(auto v:e[u]){
		if(vis[v])continue;
		allsum=sz[v],mxp[rt=0]=n+1;
		getrt(v,0),getrt(rt,0),solve(rt);
	}
}
 
signed main()
{
	n=read();
	For(i,2,n){
		int u=read(),v=read();
		adde(u,v),adde(v,u);
	}
	For(i,1,n)a[i]=read();
	mxp[rt]=allsum=n;
	getrt(1,0),getrt(rt,0),solve(rt);
	cout<<res;
	return 0;
}
