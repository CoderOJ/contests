//P5203
#include <bits/stdc++.h>
#define y1 y1_
#define index index_
#define pipe pipe_
#define next next_
#define rgi int
#define ll long long
#define Pi acos(-1.0)
#define lowbit(x) ((x&(-x)))
#define pb push_back
#define mk make_pair
#define pii pair<int,int>
#define fst first
#define scd second
using namespace std;
inline int read() {
	int f=1,x=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN=2e5+5;
int n,m;
struct EDGE{
	int next,to;
}edge[MAXN<<1];
int head[MAXN],tot;
inline void addEdge(int u,int v) {
	edge[++tot].next=head[u];
	edge[tot].to=v;
	head[u]=tot;
}
int fa[MAXN][30],dep[MAXN];
void dfs1(int u) {
	for(rgi i=1;i<=20;++i) {
		fa[u][i]=fa[fa[u][i-1]][i-1];
	}
	dep[u]=dep[fa[u][0]]+1;
	for(rgi i=head[u];i;i=edge[i].next) {
		int v=edge[i].to;
		if(v==fa[u][0]) continue;
		fa[v][0]=u; dfs1(v);
	}
}
int lca(int u,int v) {
	if(dep[u]<dep[v]) swap(u,v);
	for(rgi i=20;i>=0;--i) {
		if(dep[fa[u][i]]>=dep[v]) u=fa[u][i];
	}
	if(u==v) return u;
	for(rgi i=20;i>=0;--i) {
		if(fa[u][i]!=fa[v][i]) {
			u=fa[u][i];
			v=fa[v][i];
		}
	}
	return fa[u][0];
}
int gettop(int bot,int top) {
	if(top==bot) return -1926;
	for(rgi i=20;i>=0;--i) {
		if(dep[fa[bot][i]]>dep[top]) bot=fa[bot][i];
	}
	return bot;
}
pii node[MAXN];
map<pii,int> Tpi;
int T[MAXN],num[MAXN],anc[MAXN];
/*T是一个桶,存某个点重复算的数量*/
void dfs2(int u,int curNum) {
	num[u]=curNum;
	for(rgi i=head[u];i;i=edge[i].next) {
		int v=edge[i].to;
		if(v!=fa[u][0]) dfs2(v,curNum+T[v]);
	}
}
int main() {
//	freopen("","r",stdin);
//	freopen("","w",stdout);
	ios::sync_with_stdio(0);cin.tie(0);/*syn加速*/
	n=read(); m=read();
	for(rgi i=1;i<=n-1;++i) {
		int u,v; u=read(); v=read();
		addEdge(u,v); addEdge(v,u);
	}
	dfs1(1);
	ll ans=0;
	for(rgi i=1;i<=(m-(n-1));++i) {
		int u,v;
		u=node[i].fst=read();
		v=node[i].scd=read();
		anc[i]=lca(u,v);
		int uu=gettop(u,anc[i]);
		if(uu!=-1926) {
			ans-=T[uu]+1;
			T[uu]++;
		}
		int vv=gettop(v,anc[i]);
		if(vv!=-1926) {
			ans-=T[vv]+1;
			T[vv]++;
		}
		if(uu!=-1926 && vv!=-1926) {
			if(uu>vv) swap(uu,vv);
			ans-=Tpi[mk(uu,vv)];
			Tpi[mk(uu,vv)]++;
		}
	}
	dfs2(1,0);/*树上前缀和*/
	for(rgi i=1;i<=(m-(n-1));++i) {
		ans+=num[node[i].fst]+num[node[i].scd]-2*num[anc[i]];
	}
	cout<<ans<<endl;
	return 0;
}
