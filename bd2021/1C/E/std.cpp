#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#define N 10000
#define M 300010
using namespace std;
int deg[N];
vector<int>g[N],h[N];
void add(int ux,int uy,int vx,int vy)
{
    int u=ux*100+uy,v=vx*100+vy;
    g[u].push_back(v);h[v].push_back(u);deg[u]++;
}
bool win[N],vis[N];
void init()
{
    for(int s=0;s<100;s++)
        for(int t=0;t<100;t++)
        {
            int x1=s%10,x2=s/10,y1=t%10,y2=t/10;
            if(x1==0 || x2==0 || y1==0 || y2==0) continue;
            add(s,t,y1*10+y2,(x2+x1)%10*10+x1);
            add(s,t,y1*10+y2,(x2+y1)%10*10+x1);
            add(s,t,y1*10+y2,(x2+y2)%10*10+x1);
            add(s,t,y1*10+y2,(x1+x2)%10*10+x2);
            add(s,t,y1*10+y2,(x1+y1)%10*10+x2);
            add(s,t,y1*10+y2,(x1+y2)%10*10+x2);
        }
    queue<int>q;
    for(int s=0;s<100;s++)
        for(int t=0;t<100;t++)
        {
            int x1=s%10,x2=s/10,y1=t%10,y2=t/10;
            int u=s*100+t;
            if(x1==0 || x2==0) win[u]=vis[u]=true,q.push(u);
            else if(y1==0 || y2==0) win[u]=false,vis[u]=true,q.push(u);
        }
    for(int i=0;i<N;i++) if(!deg[i] && !vis[i]) q.push(i),vis[i]=true;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        if(!win[u])
        {
            for(int v:h[u]) if(!vis[v]) win[v]=vis[v]=true,q.push(v);
        }
        else for(int v:h[u])
        {
            if(vis[v]) continue;
            deg[v]--;
            if(!deg[v]) q.push(v),vis[v]=true;
        }
    }
}
int main()
{
    init();
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int a,b,c,d;scanf("%d%d%d%d",&a,&b,&c,&d);
        int t=a*1000+b*100+c*10+d;
        if(!vis[t]) puts("Tie");
        else if(win[t]) puts("Alice");
        else puts("Bob");
    }
    return 0;
}
