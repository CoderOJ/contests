#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
typedef long long ll;
const int N=1000010;
int n;int m;
struct data{int v;int nxt;}edge[2*N];
int alist[N];int cnt;
inline void add(int u,int v){edge[++cnt].v=v;edge[cnt].nxt=alist[u];alist[u]=cnt;}
int dfin[N];int dfou[N];int dfu;int fa[22][N];bool book[N];ll dep[N];
void dfs(int x)
{
    for(int i=0;fa[i][x];i++){fa[i+1][x]=fa[i][fa[i][x]];}//倍增预处理 
    dfin[x]=++dfu;book[x]=true;int nxt=alist[x];//记录入栈顺序 
    while(nxt)
    {
        int v=edge[nxt].v;
        if(!book[v]){dep[v]=dep[x]+1;fa[0][v]=x;dfs(v);}
        nxt=edge[nxt].nxt;
    }dfou[x]=++dfu;return;//记录出栈顺序 
}
inline int lca(int x,int y)//倍增求lca 
{
    if(dep[x]<dep[y])swap(x,y);int del=dep[x]-dep[y];
    for(int i=0;del;del>>=1,i++){if(del&1)x=fa[i][x];}if(x==y){return x;}
    for(int i=21;i>=0;i--){if(fa[i][x]!=fa[i][y]){x=fa[i][x],y=fa[i][y];}}
    return fa[0][x];
}
inline bool cmp(int x,int y)//按欧拉序排序的比较函数 
{
    int key1=(x>0)?dfin[x]:dfou[-x];
    int key2=(y>0)?dfin[y]:dfou[-y];
    return key1<key2;
}
int tp[4*N];ll sum[N];ll siz[N];ll mi[N];ll ma[N];bool vis[N];
ll tot[N];stack <int> s;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u;int v;scanf("%d%d",&u,&v);add(u,v);add(v,u);}
    dfs(1);//先预处理 
    scanf("%d",&m);
    for(int i=1;i<=n;i++){mi[i]=0x7f7f7f7f7f;}
    for(int i=1;i<=m;i++)
    {
        ll ans1=0;ll ans2=0x7f7f7f7f7f;ll ans3=0;
        int k;scanf("%d",&k);int cnt=k;
        for(int i=1;i<=k;i++)
        {scanf("%d",&tp[i]);mi[tp[i]]=0;siz[tp[i]]=1;vis[tp[i]]=true;}//处理dp的边界条件 
        sort(tp+1,tp+k+1,cmp);tp[++cnt]=-tp[1];//这里先按dfs序排一波 
        for(int i=2;i<=k;i++)
        {
            int lc=lca(tp[i],tp[i-1]);tp[++cnt]=-tp[i];//计算lca，每一个点正负各插一遍 
            if(!vis[lc]){tp[++cnt]=lc;tp[++cnt]=-lc;vis[lc]=true;}
        }
        sort(tp+1,tp+cnt+1,cmp);//强行求出欧拉序 
        for(int i=1;i<=cnt;i++)
        {
            if(tp[i]>0){s.push(tp[i]);continue;}//无脑入栈 
            if(tp[i]<0)
            {
                int now=s.top();s.pop();//出栈的话，这个点和当前栈顶肯定是父子关系，开始dp 
                if(!s.empty())//特判下pop根的情况 
                {
                    int to=s.top();ll dis=(dep[now]-dep[to]);//计算dis 
                    sum[now]+=siz[now]*dis;//所有路径拔高 
                    ans1+=siz[to]*sum[now]+siz[now]*sum[to];//更新答案 
                    siz[to]+=siz[now];sum[to]+=sum[now];//更新sum 
                    mi[now]+=dis;ans2=min(ans2,mi[to]+mi[now]);mi[to]=min(mi[to],mi[now]);//更新min 
                    ma[now]+=dis;ans3=max(ans3,ma[to]+ma[now]);ma[to]=max(ma[to],ma[now]);//更新max 
                }
                siz[now]=0;sum[now]=0;mi[now]=0x7f7f7f7f7f;ma[now]=0;vis[now]=false;//出栈的时候记得清空信息 
            }
        }
        printf("%lld %lld %lld\n",ans1,ans2,ans3);//输出答案 
    }return 0;//拜拜程序~ 
}
