#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 998244353
#define N 5010
using namespace std;
int x[N],y[N],fac[N],inv[N];
int ksm(int a,int b=mod-2) { int r=1; for(;b;b>>=1) { if(b&1) r=1ll*r*a%mod; a=1ll*a*a%mod; } return r; }
int C(int a,int b){return b>a?0:1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;}
int nxt[N<<2],to[N<<2],head[N*2],cnt;
void add(int u,int v) { nxt[++cnt]=head[u]; to[cnt]=v; head[u]=cnt; }
namespace c2{
    #define M 3010
    int f[N*2][M],g[N*2][M],sw[2][N*2];
    int h[N*2];
    int id[N*2],tt,siz[N*2];
    void dfs(int u,int p)
    {
        siz[u]=1;
        f[u][0]=1;
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i];
            if(v==p) continue;
            dfs(v,u);
            for(int j=0;j<=(siz[u]+siz[v])/2;j++) sw[0][j]=sw[1][j]=0;
            for(int j=0;j<=siz[u]/2;j++)
                for(int k=0;k<=siz[v]/2;k++)
                {
                    sw[0][j+k]=(sw[0][j+k]+1ll*f[u][j]*g[v][k]%mod)%mod;
                    sw[1][j+k]=(sw[1][j+k]+1ll*g[u][j]*g[v][k]%mod)%mod;
                    sw[1][j+k+1]=(sw[1][j+k+1]+1ll*f[u][j]*f[v][k])%mod;
                }
            for(int j=0;j<=(siz[u]+siz[v])/2;j++) f[u][j]=sw[0][j],g[u][j]=sw[1][j];
            siz[u]+=siz[v];
        }
        for(int j=0;j<=siz[u]/2;j++) g[u][j]=(g[u][j]+f[u][j])%mod;
    }
    void main(int n)
    {
        for(int i=1;i<=n*2;i++)
        if(!siz[i]) dfs(i,0),id[++tt]=i;
        h[0]=1;
        for(int i=1;i<=tt;i++)
        {
            for(int j=0;j<=n;j++) sw[0][j]=0;
            for(int j=0;j<=n;j++)
                for(int k=0;k<=siz[id[i]]/2;k++)
                    sw[0][j+k]=(sw[0][j+k]+1ll*h[j]*g[id[i]][k])%mod;
            for(int j=0;j<=n;j++) h[j]=sw[0][j];
        }
        int ans=0;
        for(int i=0;i<n;i++) ans=(ans+(i%2?-1ll:1ll)*fac[n-i]*h[i]%mod+mod)%mod;
        printf("%d\n",ans);
    }
    #undef M
}
int main()
{
    int n;
    scanf("%d",&n);
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
    for(int i=1;i<n;i++) scanf("%d%d",&x[i],&y[i]);
    for(int i=1;i<n;i++)
    add(x[i]*2-1,y[i]*2),add(y[i]*2,x[i]*2-1);
    c2::main(n);
    return 0;
}
