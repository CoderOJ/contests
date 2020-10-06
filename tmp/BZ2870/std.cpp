#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define register
using namespace std;
#define lowbit(x) ((x)&(-(x)))
#define REP(i,a,n) for(register int i=(a);i<=(n);++i)
#define PER(i,a,n) for(register int i=(a);i>=(n);--i)
#define FEC(i,x) for(register int i=head[x];i;i=g[i].ne)
#define dbg(...) fprintf(stderr,__VA_ARGS__)
namespace io{
	const int SIZE=(1<<21)+1;char ibuf[SIZE],*iS,*iT,obuf[SIZE],*oS=obuf,*oT=oS+SIZE-1,c,qu[55];int f,qr;
	#define gc() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),(iS==iT?EOF:*iS++)):*iS++)
	inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
	inline void putc(char x){*oS++=x;if(oS==oT)flush();}
	template<class I>inline void read(I &x){for(f=1,c=gc();c<'0'||c>'9';c=gc())if(c=='-')f=-1;for(x=0;c<='9'&&c>='0';c=gc())x=x*10+(c&15);x*=f;}
	template<class I>inline void write(I x){if(!x)putc('0');if(x<0)putc('-'),x=-x;while(x)qu[++qr]=x%10+'0',x/=10;while(qr)putc(qu[qr--]);}
	inline void print(const char *s){while(*s!='\0')putc(*s++);}
	struct Flusher_{~Flusher_(){flush();}}io_flusher_;
}//orz laofudasuan
using io::read;using io::putc;using io::write;using io::print;
typedef long long ll;typedef unsigned long long ull;
template<typename A,typename B>inline bool SMAX(A&x,const B&y){return x<y?x=y,1:0;}
template<typename A,typename B>inline bool SMIN(A&x,const B&y){return y<x?x=y,1:0;}

const int N=50000+7,LOG=18;
int n,x,y,lg[N<<1];ll ans=0;
int dfc,dfn[N],seq[N<<1],lca[N<<1][LOG],dep[N],vis[N];
struct Point{int val,id;inline bool operator<(const Point&a)const{return val>a.val;};}a[N];
struct Edge{int to,ne;}g[N<<1];int head[N],tot;
inline void Addedge(int x,int y){g[++tot].to=y;g[tot].ne=head[x];head[x]=tot;}

inline void DFS(int x,int fa=0){
	dep[x]=dep[fa]+1;seq[++dfc]=x;dfn[x]=dfc;
	for(register int i=head[x];i;i=g[i].ne)if(g[i].to!=fa)DFS(g[i].to,x),seq[++dfc]=x;
}
inline void RMQ_init(){
	for(register int i=1;i<=dfc;++i)lca[i][0]=seq[i];
	for(register int j=1;(1<<j)<=dfc;++j)
		for(register int i=1;i+(1<<j)-1<=dfc;++i){
			int a=lca[i][j-1],b=lca[i+(1<<(j-1))][j-1];
			lca[i][j]=dep[a]<dep[b]?a:b;
		}
}
inline int Qmin(int l,int r){int k=lg[r-l+1],a=lca[l][k],b=lca[r-(1<<k)+1][k];return dep[a]<dep[b]?a:b;}
inline int LCA(int x,int y){return dfn[x]<dfn[y]?Qmin(dfn[x],dfn[y]):Qmin(dfn[y],dfn[x]);}
inline int Dist(int x,int y){return dep[x]+dep[y]-(dep[LCA(x,y)]<<1)+1;}

int fa[N];
inline int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
inline void Union(int x,int y){x=Find(x),y=Find(y);fa[y]=x;}
struct Node{int x,y;}t[N];
inline Node Merge(Node a,Node b){
	int dist=Dist(a.x,a.y);Node p=a;
	if(SMAX(dist,Dist(b.x,b.y)))p=b;
	if(a.x!=b.y&&b.x!=a.y&&SMAX(dist,Dist(a.x,b.x)))p=Node{a.x,b.x};
	if(a.y!=b.y&&a.x!=b.x&&SMAX(dist,Dist(a.x,b.y)))p=Node{a.x,b.y};
	if(a.x!=b.x&&a.y!=b.y&&SMAX(dist,Dist(a.y,b.x)))p=Node{a.y,b.x};
	if(a.y!=b.x&&a.x!=b.y&&b.x!=b.y&&b.x!=a.y&&a.x!=a.y&&SMAX(dist,Dist(a.y,b.y)))p=Node{a.y,b.y};
	return p;
}

int main(){
	read(n);lg[1]=0;for(register int i=2;i<=(n<<1);++i)lg[i]=lg[i>>1]+1;
	for(register int i=1;i<=n;++i)read(a[i].val),a[i].id=i,fa[i]=i,t[i]=Node{i,i};
	for(register int i=1;i<n;++i)read(x),read(y),Addedge(x,y),Addedge(y,x);
	DFS(1);RMQ_init();
	sort(a+1,a+n+1);for(register int i=1;i<=n;++i){
		for(register int j=head[a[i].id];j;j=g[j].ne)if(vis[g[j].to]){//错误笔记：把g[j].to打成g[i].to      而且一定要判断是否vis过 
			int x=Find(a[i].id),y=Find(g[j].to);if(x==y)continue;
			t[x]=Merge(t[x],t[y]);Union(x,y);
		}vis[a[i].id]=1;
		SMAX(ans,(ll)Dist(t[Find(a[i].id)].x,t[Find(a[i].id)].y)*a[i].val);
	}
	write(ans),putc('\n');
}
