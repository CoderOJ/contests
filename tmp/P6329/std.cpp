#include <iostream>
#include <cstdio>
#include <vector>
#define REP(u) for(int i = H[u], v; i, v = E[i].v; i = E[i].n)
using namespace std;
const int maxn = 2e5 + 111, inf = 1e9 + 7;
int N, M, tot, ans, rt, sum, minn, cnt, ss;
int val[maxn], H[maxn], sz[maxn], fa[maxn], dep[maxn], pos[maxn], ol[maxn<<1][21], lg[maxn<<1];
//val表示该城市的价值，sz表示该点子树的大小，fa表示该点点分树上的父亲节点，dep表示该点的深度 
bool vis[maxn];
vector<int>C[2][maxn];
//C[0][i]表示i子树内节点对i的贡献
//C[1][i]表示i子树内节点对i父亲的贡献 
struct edge {
	int n, v;
}E[maxn<<1];
void add(int u, int v)
{
	E[++tot] = (edge) {H[u], v};
	H[u] = tot;
}
void dfs0(int u, int f)
{
	ol[++cnt][0] = u, pos[u] = cnt;
	REP(u) if(v ^ f) dep[v] = dep[u] + 1, dfs0(v, u), ol[++cnt][0] = u;
}
int get_min(int a, int b)
{
	return dep[a] < dep[b] ? a : b;
}
void get_ol() 
{
	for(int i = 1; i <= cnt; ++i) lg[i] = 31 - __builtin_clz(i);
	for(int t = 1; 1 << t <= cnt; ++t)
		for(int i = 1; i + (1 <<t) <= cnt; ++i)
			ol[i][t] = get_min(ol[i][t - 1], ol[i + (1 << (t - 1))][t - 1]);
}
int get_dis(int u, int v)
{
	if(pos[u] > pos[v]) swap(u, v);
	int uu = pos[u], vv = pos[v], len = vv - uu + 1;
	int lca = get_min(ol[uu][lg[len]], ol[vv - (1 << lg[len]) + 1][lg[len]]);
	return dep[u] + dep[v] - 2 * dep[lca];
}
#define lowbit(x) (x & -x)
void upd(int u, int opt, int x, int addv)
{
	x++;
	for(int i = x; i <= sz[u]; i += lowbit(i)) C[opt][u][i] += addv;
}
int qry(int u, int opt, int x)
{
	x++;
	int res = 0;
	x = min(x, sz[u]);
	for(int i = x; i; i -= lowbit(i)) res += C[opt][u][i];
	return res;
}
void find_rt(int u, int f) //找重心 
{
	++ss;
	sz[u] = 1;
	int res = 0;
	REP(u) if(f ^ v && !vis[v]) find_rt(v, u), sz[u] += sz[v], res = max(res, sz[v]);
	res = max(res, sum - sz[u]);
	if(res < minn) minn = res, rt = u; 
}
void dfs(int u) //建立点分树 
{
	vis[u] = 1;
	sz[u] = ss + 1;
	C[0][u].resize(sz[u] + 2);
	C[1][u].resize(sz[u] + 2);
	REP(u) if(!vis[v]) 
	{
		sum = sz[v], rt = 0, minn = inf;
		ss = 0;
		find_rt(v, 0);
		fa[rt] = u;
		dfs(rt);
	}
}
void modify(int u, int w)
{
	for(int i = u; i; i = fa[i]) upd(i, 0, get_dis(u, i), w); 
	for(int i = u; fa[i]; i = fa[i]) upd(i, 1, get_dis(u, fa[i]), w);	
}
int main()
{
	int opt, x, y;
	scanf("%d%d", &N, &M);
	for(int i = 1; i <= N; ++i) scanf("%d", &val[i]);
	for(int i = 1; i <  N; ++i) scanf("%d%d", &x, &y), add(x, y), add(y, x);
	dfs0(1, 0);
	get_ol();
	sum = N, minn = inf;
	find_rt(1, 0);
	dfs(rt);
	for(int i = 1; i <= N; ++i) modify(i, val[i]); 
	while(M--)
	{
		scanf("%d%d%d", &opt, &x, &y);
		x ^= ans, y ^= ans; 
		if(!opt) 
		{
			ans = 0;
			ans += qry(x, 0, y); //x子树内到其距离为y的点对x的贡献 
			for(int i = x; fa[i]; i = fa[i])
			{
				int dis = get_dis(x, fa[i]);  
				if(y >= dis) ans += qry(fa[i], 0, y - dis) - qry(i, 1, y - dis); //x子树外到其距离为y的点 
				//fa[i]子树中除x所在子树对x的贡献 即为 fa[i]子树对它的总贡献 减去 x所在子树对fa[i]的贡献 
			}
			printf("%d\n", ans);
		}
		else modify(x, y - val[x]), val[x] = y; //利用差分的办法修改其对点分树上祖先的贡献 
	}
	return 0;
}
