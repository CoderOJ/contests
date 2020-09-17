#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <ctime>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
using namespace std;
typedef long long ll;
//#define enable_ll
#ifdef enable_ll
    #define int long long
#endif
#ifdef DEBUG
    #define out(u) cout<<u<<" "
    #define outln(u) cout<<u<<endl
    #define see(u) cout<<#u<<"="<<u<<" "
    #define seeln(u) cout<<#u<<"="<<u<<endl
    #define line cout<<"---------------------\n"
#else
    #define out(u)
    #define outln(u)
    #define see(u)
    #define seeln(u)
    #define line
#endif
#define m_p make_pair
#define pii pair<int,int>
#define pil pair<int,long long>
#define piii pair<pii,int>
#define sz(x) (int)x.size()
#define fastio ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
template <class T> void read(T &u)
{
    u=0; char c=getchar(); int flag=0;
    while (c<'0'||c>'9') flag|=(c=='-'),c=getchar();
    while (c>='0'&&c<='9') u=(u<<3)+(u<<1)+(c^48),c=getchar();
    if (flag) u=-u;
}
template <class T> void write(T u)
{
    if (u<0) printf("-"),u=-u;
    if (u<10) putchar(48+u);
    else write(u/10),putchar(48+u%10);
}
void write(char u){putchar(u);}
template <class T> bool checkmin(T &a,T b){return (b<a ? a=b,1 : 0);}
template <class T> bool checkmax(T &a,T b){return (b>a ? a=b,1 : 0);}
template <class T> T _min(T a,T b){return (a<b ? a : b);}
template <class T> T _max(T a,T b){return (a>b ? a : b);}
const int N=10005;
const long long inf=1e16;
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};
int n,m,p;  
long long dist[12][12],h[N];
int a[12],b[12];
struct edge
{
    int to;
    long long val;
    edge(){}
    edge(int to,long long v):to(to),val(v){}
};
vector <edge> G[N];
long long dis[N];
void init()
{
    read(n); read(m);
    int cnt=0;
    for (int i=0;i<n;++i)
    {
        for (int j=0;j<m;++j)
        {
            read(h[cnt]); cnt++;
        }
    }  
    read(p);
    for (int i=1,x,y;i<=p;++i)
    {
        read(x); read(y); --x,--y;
        a[i]=x*m+y;
    }
}
 
void add_edge(int x,int y,long long z)
{
    G[x].push_back(edge(y,z));
}
 
void dijkstra(int x)
{
    for (int i=0;i<n*m;++i) G[i].clear();
    for (int i=0;i<n;++i)
    {
        for (int j=0;j<m;++j)
        {  
            for (int dir=0;dir<4;++dir)
            {
                int X=dx[dir]+i,Y=dy[dir]+j;
                if (X>=0&&X<n&&Y>=0&&Y<m)
                {
                    int p=i*m+j,q=X*m+Y;
                    add_edge(p,q,(h[p]-h[q])*(h[p]-h[q])+1);
                    add_edge(q,p,(h[p]-h[q])*(h[p]-h[q])+1);
                }
            }
        }
    }
    priority_queue <pil,vector<pil>,greater<pil> > q;
    for (int i=0;i<n*m;++i) dis[i]=(i==a[x] ? 0 : inf);
    q.push(m_p(dis[a[x]],a[x]));
    while (!q.empty())
    {
        pii now=q.top(); q.pop();
        int u=now.second; long long value=now.first;
        if (dis[u]>value) continue;
        for (int i=0;i<sz(G[u]);++i)
        {
            edge &e=G[u][i];
            if (checkmin(dis[e.to],dis[u]+e.val))
            {
                q.push(m_p(dis[e.to],e.to));
            }
        }
    }
    for (int i=0;i<=p;++i)
    {
        if (i==x) continue;
        dist[x][i]=dis[a[i]];
    }
}
 
void solve()
{
    a[0]=0;
    for (int i=0;i<=p;++i)
    {
        dijkstra(i);
    }
    long long Ans=-1;
    for (int i=1;i<=p;++i) b[i]=i;
    do
    {
        long long ans=dist[0][b[1]];
        for (int i=2;i<=p;++i)
        {
            ans+=dist[b[i-1]][b[i]];
        }
        if (Ans==-1) Ans=ans;
        else checkmin(Ans,ans);
    }
    while(next_permutation(b+1,b+p+1));
    printf("%lld\n",Ans);
}
 
#undef int
int main()
{
    int T=1;
    while (T--)
    {
        init();
        solve();
    }
    return 0;
}
