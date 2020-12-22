#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
double A=clock();
#define setIO(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout)
#define closefile fclose(stdin),fclose(stdout)
#define see(x) cerr<<x<<" "
#define seeln(x) cerr<<x<<endl
#define out(x) cerr<<#x<<" = "<<x<<" "
#define outln(x) cerr<<#x<<" = "<<x<<endl
#define outarr(x,l,r) {cerr<<#x"["<<l<<"-"<<r<<"] = "; for (int _i=l;_i<=r;++_i) cerr<<x[_i]<<" "; cerr<<endl;}
#define user_time cerr<<fixed<<setprecision(6)<<(clock()-A)*1.0/CLOCKS_PER_SEC<<endl
#define m_p make_pair
#define sz(x) (int)x.size()
template <class T> void read(T &x)
{
    x=0; char c=getchar(); int flag=0;
    while (c<'0'||c>'9') flag|=(c=='-'),c=getchar();
    while (c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    if (flag) x=-x;
}
template <class T> T _max(T a,T b){return b>a ? b : a;}
template <class T> T _min(T a,T b){return b<a ? b : a;}
template <class T> bool checkmax(T &a,T b){return b>a ? a=b,1 : 0;}
template <class T> bool checkmin(T &a,T b){return b<a ? a=b,1 : 0;}
const int mod=1000000000+7;
int Add(int a,int b){a+=b; return a>=mod ? a-mod : a;}
int Sub(int a,int b){a-=b; return a<0 ? a+mod : a;}
int Mul(int a,int b){return (ll)a*b%mod;}
void add(int &a,int b){a+=b; (a>=mod) && (a-=mod);}
void sub(int &a,int b){a-=b; (a<0) && (a+=mod);}
void mul(int &a,int b){a=(ll)a*b%mod;}
int qpow(int a,int b){int ans=1; while (b) {if (b&1) ans=(ll)ans*a%mod; a=(ll)a*a%mod; b>>=1;} return ans;}



const int N=200005,mod1=20201021,mod2=20201029,Base=2345678;
int n,m;
int gcd(int a,int b){return b ? gcd(b,a%b) : a;}
vector<int> G[N];
int fa[N],dfn[N],dep[N],dfs_clock=0;
int cycle[N],on_cyc[N],cyc_num=0;
pii Pow[N],str[N],H[N]; int sta[N],M[N];
pii operator * (pii a,int b){return m_p(a.first*b%mod,a.second*b%mod);}
pii operator << (pii a,int b){return m_p((ll)a.first*Pow[b].first%mod1,(ll)a.second*Pow[b].second%mod2);}
pii operator + (pii a,int b){return m_p((a.first+b)%mod1,(a.second+b)%mod2);}
pii operator + (pii a,pii b){return m_p((a.first+b.first)%mod1,(a.second+b.second)%mod2);}
int csp[N],dp[N],inv[N],f[N],siz[N];
void add_edge(int x,int y)
{
    G[x].push_back(y);
}
 
bool cmp(int x,int y){return dep[x]==dep[y] ? H[x]<H[y] : dep[x]<dep[y];}
void DFS(int x,int f)
{
    dep[x]=dep[f]+1; siz[x]=1;
    for (int i=0;i<sz(G[x]);++i)
    {
        int to=G[x][i];
        if (on_cyc[to]) continue;
        DFS(to,x); siz[x]+=siz[to];
    }
    sort(G[x].begin(),G[x].end(),cmp);
    int tot=0;
    H[x]=m_p(dep[x],dep[x]);
    for (int i=0;i<sz(G[x]);++i)
    {
        int to=G[x][i];
        if (on_cyc[to]) continue;
        H[x]=(H[x]<<siz[to])+H[to];
        sta[++tot]=to;
    }
    dp[x]=m;
    for (int i=1,j;i<=tot;)
    {
        j=i;
        while (j<tot&&H[sta[j+1]]==H[sta[i]]) ++j;
        int cnt=j-i+1,num=dp[sta[i]];
        for (int i=0;i<cnt;++i) mul(dp[x],Add(num,i));
        for (int i=1;i<=cnt;++i) mul(dp[x],inv[i]);
        i=j+1;
    }
}
 
int get_rep()
{
    for (int i=0;i<cyc_num;++i) str[i]=H[cycle[i+1]];
    int i=1,j=0;
    for (;i<cyc_num;++i)
    {
        while (j&&str[i]!=str[j]) j=csp[j-1];
        if (str[i]==str[j]) ++j,csp[i]=j;
    }
    int len=cyc_num-csp[cyc_num-1];
    if (csp[cyc_num-1]==cyc_num) return cyc_num;
    if (cyc_num%len==0) return len;
    else return cyc_num;
}
 
int Burnside(int n,int m)
{
    M[0]=1; for (int i=1;i<=n;++i) M[i]=Mul(M[i-1],m);
    int ans=0;
    for (int k=0;k<n;++k)
    {
        int d=gcd(n,k);
        add(ans,M[d]);
    }
    return Mul(ans,inv[n]);
}
 
void init()
{
    read(n); read(m);
    Pow[0]=m_p(1,1); for (int i=1;i<=n;++i) Pow[i]=Pow[i-1]*Base;
    inv[0]=inv[1]=1; for (int i=2;i<=n;++i) inv[i]=Mul(inv[mod%i],mod-mod/i);
    for (int i=1;i<=n;++i)
    {
        read(f[i]);
        add_edge(f[i],i);
    }
    int now=1;
    for (int i=1;i<=n;++i) now=f[now];
    int tmp=now;
    for (;;)
    {
        on_cyc[tmp]=1; cycle[++cyc_num]=tmp;
        tmp=f[tmp];
        if (tmp==now) break;
    }
}
 
void solve()
{
    for (int i=1;i<=cyc_num;++i) DFS(cycle[i],0);
    int len=get_rep(),total=1;
    outln(len);
    for (int i=1;i<=len;++i) mul(total,dp[cycle[i]]);
    int ans=Burnside(cyc_num/len,total);
    printf("%d\n",ans);
}
 
int main()
{
    //setIO("");
    init();
    solve();
    closefile;
    return 0;
}
