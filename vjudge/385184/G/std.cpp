#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200005,INF=1e18+5;
struct edge{int to,wei,nxt;}e[N<<1];//笔者就是菜，边数组又忘记开两倍了
int n,tot=0,cnt=0,ans1=0,ans2=INF,res,head[N],cir[N],vis[N],f[N],we[N],l[N],l0[N],r[N],r0[N];
inline void adde(int x,int y,int w) {e[++tot]=(edge){y,w,head[x]},head[x]=tot;}//加边
inline int fnd(int x,int fa=-1)//这个是暴力dfs找环
{
	if(vis[x]) return x;else vis[x]=-1;//vis为-1表示不在环里，vis为0表示未访问过，vis为1表示在环里
	for(int i=head[x];i;i=e[i].nxt) if(e[i].to!=fa) {res=fnd(e[i].to,x);if(res) return cir[++cnt]=x,we[cnt]=e[i].wei,vis[x]=1,res==x?0:res;}
	return 0;
}
inline void dfs(int x,int fa=-1)//dfs，求一棵树的直径
{
	for(int i=head[x];i;i=e[i].nxt)
		if(vis[e[i].to]!=1&&e[i].to!=fa)
			dfs(e[i].to,x),ans1=max(ans1,f[x]+f[e[i].to]+e[i].wei),f[x]=max(f[x],f[e[i].to]+e[i].wei);
}
signed main()
{
//l和r之和就是Case 3的答案，l0是Case 1的答案，r0是Case 2的答案。
	scanf("%lld",&n),memset(vis,0,sizeof(vis)),memset(f,0,sizeof(f));
	for(int i=1,x,y,w;i<=n;i++) scanf("%lld%lld%lld",&x,&y,&w),adde(x,y,w),adde(y,x,w);
	fnd(1),we[0]=0;for(int i=1;i<=cnt;i++) dfs(cir[i]),we[i]+=we[i-1];//这里其实可以考虑用前缀和，处理起来更加方便一点。
	res=l[0]=l0[0]=-INF;//初始值赋极小值，res就是之前说的那个递推的东西
	for(int i=1;i<=cnt;i++) l0[i]=max(l0[i-1],f[cir[i]]+we[i]+res),l[i]=max(l[i-1],f[cir[i]]+we[i]),res=max(res,f[cir[i]]-we[i]);
	res=r[cnt+1]=r0[cnt+1]=-INF;//反着递推
	for(int i=cnt;i>=1;i--) r0[i]=max(r0[i+1],f[cir[i]]-we[i]+res),r[i]=max(r[i+1],f[cir[i]]+we[cnt]-we[i]),res=max(res,f[cir[i]]+we[i]);
	for(int i=1;i<=cnt;i++) ans2=min(ans2,max(l[i-1]+r[i],max(l0[i-1],r0[i])));//最后统计链上答案
	return printf("%lld\n",max(ans1,ans2)),0;//这里千万要注意，如果不和ans2取max就会WA
}
