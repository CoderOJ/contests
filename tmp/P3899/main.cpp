#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
template <class T> bool checkMax(T& a, T b) { return a<b ? a=b,1 : 0; }
template <class T> bool checkMin(T& a, T b) { return b<a ? a=b,1 : 0; }
#define long long long
#ifdef __LOCALE__
#define ses(a) cout << #a << "=" << a << ' '
#define see(a) cout << #a << "=" << a << endl
#else
#define ses(a)
#define see(a)
#endif

const int N = 300005;
vector <int> e[N];
int n,q;

int dep[N], ls[N], d[N], sz[N];
void dfs1(int u, int f) {
	dep[u]=1; d[u] = d[f]+1; sz[u]=1;
	for (int v: e[u]) if (v!=f) {
		dfs1(v,u); sz[u] += sz[v];
		if (checkMax(dep[u], dep[v]+1)) { ls[u] = v; } } }

struct Query { int k, id; };
vector <Query> qs[N];

struct Vec {
	vector <long> a;
	long del;
	Vec () { del = 0; }

	void push(long u) { u -= del; a.push_back(u); }
	void add(long u) { del += u; }
	int size() { return a.size(); }
	long at(int p) { 
		if (p==0 && size()==0) { return 0; }
		return a[p] + del; }
};

Vec* p[N];
long ans[N];

void dfs2(int u, int f) {
	for (int v: e[u]) if (v!=f) { dfs2(v,u); }
	if (ls[u] != 0) { p[u] = p[ls[u]]; p[ls[u]] = NULL; }
	else { p[u] = new Vec(); }
	for (int v: e[u]) if (v!=f && v!=ls[u]) {
		long base = p[v]->at(0);
		p[u]->add(base);
		int margin = p[u]->size() - p[v]->size();
		rep (i,p[v]->size()) p[u]->a[margin+i] += p[v]->at(i) - base; }
	for (Query q: qs[u]) {
		ans[q.id] = 1ll * min(d[u]-1,q.k) * (sz[u]-1) + p[u]->at( max(0, p[u]->size()-q.k) ); } 
	p[u]->push(0); 
	p[u]->add( sz[u]-1 ); }

int main() {
	scanf("%d%d", &n,&q);
	rep (i,n-1) { int u,v; scanf("%d%d",&u,&v); e[u].push_back(v); e[v].push_back(u); }
	rep (i,q) { int p,k; scanf("%d%d",&p,&k); qs[p].push_back({k,i}); }
	dfs1(1,0);
	dfs2(1,0);
	rep (i,q) { printf("%lld\n", ans[i]); }
	repa (i,n) if (p[i] != NULL) delete p[i];
	return 0;
}
