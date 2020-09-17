#define ENABLE_LL
#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

void init();
void solve();
int main(){
try { 

#ifndef CUSTOM_MAIN
#ifdef MULTIPLE_TEST_CASES_WITH_T

int T; scanf("%d",&T); while(T--) {init(); solve();}

#else
#ifdef MULTIPLE_TEST_CASES_WITHOUT_T

while(1) {try{init(); } catch(bool t){return 0;} solve(); }

#else

init(); solve();

#endif
#endif
#endif

} catch (const char* s) { return 0; }
    return 0;
}

#ifdef ENABLE_LL
#define int long long
#endif

#ifdef ENABLE_LL
#define I "%lld"
#define II "%lld%lld"
#define III "%lld%lld%lld"
#define IIII "%lld%lld%lld%lld"
#define IN "%lld\n"
#define IIN "%lld%lld\n"
#define IIIN "%lld%lld%lld\n"
#define IIIIN "%lld%lld%lld%lld\n"
#else
#define I "%d"
#define II "%d%d"
#define III "%d%d%d"
#define IIII "%d%d%d%d"
#define IN "%d\n"
#define IIN "%d%d\n"
#define IIIN "%d%d%d\n"
#define IIIIN "%d%d%d%d\n"
#endif

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#define ses(a) std::cout << #a << "=" << a << " " 
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#define ses(a)
#endif
#define repe(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)
typedef pair < int , int > pr; typedef pair < pr  , int > prr;
#define L first
#define R second
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); }
class Scanner{ private: istream& ist;public: Scanner(istream& in):ist(in){} string next(){ string r; ist >> r; return r; } string nextLine(){ string r; getline(ist,r); return r; } int nextInt(){ int r; ist >> r; return r; } double nextDouble(){ double r; ist >> r; return r; } char nextChar(){ char r; ist>>r; return r;} }; Scanner sc(cin);
void ALERT(bool judgememt, const char* phrase) { if (judgememt) { puts(phrase); throw "ALERT"; } }
bool alert(bool judgememt, const char* phrase) { if (judgememt) puts(phrase); return judgememt; }

const int N=400005,INF=1e18+5;
struct Edge {int to,wei,nxt;};
Edge e[N];
int n,tot=0,cnt=0,ans1=0,ans2=INF,res;
int head[N],cir[N],vis[N],f[N],we[N];
inline void adde(int x,int y,int w) {e[++tot]=(Edge){y,w,head[x]},head[x]=tot;}
int fnd(int x,int fa=-1) {
	if(vis[x]) return x;else vis[x]=-1;
	for(int i=head[x];i;i=e[i].nxt) if(e[i].to!=fa) {
        res=fnd(e[i].to,x); 
        if(res) return cir[++cnt]=x,we[cnt]=e[i].wei,vis[x]=1,res==x?0:res; }
	return 0; }

void dfs(int x,int fa=-1) {
	for(int i=head[x];i;i=e[i].nxt) {
		if(vis[e[i].to]==1 || e[i].to==fa) continue;
    	dfs(e[i].to,x),ans1=max(ans1,f[x]+f[e[i].to]+e[i].wei),f[x]=max(f[x],f[e[i].to]+e[i].wei); } }

void init() {
	scanf(I,&n),memset(vis,0,sizeof(vis)),memset(f,0,sizeof(f)); }

int l[N],l0[N],r[N],r0[N];
void solve() {
	for(int i=1,u,v,w;i<=n;i++) scanf(III,&u,&v,&w),adde(u,v,w),adde(v,u,w);
	fnd(1),we[0]=0;for(int i=1;i<=cnt;i++) dfs(cir[i]),we[i]+=we[i-1];
	res=l[0]=l0[0]=-INF;
	repa (i,cnt) { l0[i]=max(l0[i-1],f[cir[i]]+we[i]+res); l[i]=max(l[i-1],f[cir[i]]+we[i]); res=max(res,f[cir[i]]-we[i]); }
	res=r[cnt+1]=r0[cnt+1]= -INF;
	repb(i,cnt,1) r0[i]=max(r0[i+1],f[cir[i]]-we[i]+res),r[i]=max(r[i+1],f[cir[i]]+we[cnt]-we[i]),res=max(res,f[cir[i]]+we[i]);
	repa(i,cnt)   ans2=min(ans2,max(l[i-1]+r[i],max(l0[i-1],r0[i])));
	printf(IN,max(ans1,ans2)); }
