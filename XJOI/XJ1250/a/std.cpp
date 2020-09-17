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
#define piii pair<int,pii>
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
template <class T> void write(T u,char c) {write(u); putchar(c);}
template <class T> bool checkmin(T &a,T b){return (b<a ? a=b,1 : 0);}
template <class T> bool checkmax(T &a,T b){return (b>a ? a=b,1 : 0);}
template <class T> T _min(T a,T b){return (a<b ? a : b);}
template <class T> T _max(T a,T b){return (a>b ? a : b);}
const int maxn=2005,mod=1000000000+7;
int n,m;
char s[205];
int dp[maxn][maxn];
int cnt[maxn][maxn];
namespace Trie
{
    const int MAX=400015;
    int sz,root,ch[MAX][26],end[MAX];
    int dfs_clock=1,L[MAX],R[MAX];
    int new_node()
    {
        memset(ch[sz],-1,sizeof ch[sz]);
        ++sz;
        return sz-1;
    }
 
    void init()
    {
        sz=0;   dfs_clock=1;
        root=new_node();
    }
 
    void insert(char *s)
    {
        int l=strlen(s),now=root;
        for (int i=0;i<l;++i)
        {
            int dir=s[i]-'a';
            if (ch[now][dir]==-1)
            {
                ch[now][dir]=new_node();
            }
            now=ch[now][dir];
        }
        end[now]=1;
    }
 
    void dfs(int x)
    {
        L[x]=dfs_clock;
        if (end[x]) ++dfs_clock;
        for (int i=0;i<26;++i)
        {
            if (ch[x][i]!=-1)
            {
                dfs(ch[x][i]);
            }
        }
        R[x]=dfs_clock-1;
        if (x) ++cnt[L[x]][R[x]];
    }
 
    void solver()
    {
        dfs(0);
        dp[0][0]=1;
        for (int i=1;i<=n;++i)
        {
            for (int j=1;j<=i;++j)
            {
                if (cnt[j][i])
                {
                    for (int rnd=1;rnd<=m;++rnd)
                    {
                        dp[rnd][i]=(dp[rnd][i]+1LL*dp[rnd-1][j-1]*cnt[j][i]%mod)%mod;
                    }
                }
            }
        }
        write(dp[m][n],'\n');
    }
}
 
void init()
{
    read(n); read(m);
    Trie::init();
    for (int i=1;i<=n;++i)
    {
        scanf("%s",s);
        Trie::insert(s);
    }
}
  
void solve()
{
    Trie::solver();
}
        
#undef int
int main()
{
    init();
    solve();
    return 0;
}
