#include<bits/stdc++.h>
template <class T>
inline void read(T &a)
{
   T s = 0, w = 1;
   char c = getchar();
   while(c < '0' || c > '9')
   {
       if(c == '-') w = -1;
       c = getchar();
   }
   while(c >= '0' && c <= '9')
   {
       s = (s << 1) + (s << 3) + (c ^ 48);
       c = getchar();
   }
   a = s*w;
}
template<class T> void chkmax(T &a, T b) { if (a<b) { a=b; } }
template<class T> void chkmin(T &a, T b) { if (a>b) { a=b; } }
template<class T> T min(T a, T b) {return a > b ? b : a;}
template<class T> T max(T a, T b) {return a < b ? b : a;}

int n,m;
int S;
int size[10101];
struct edge{
   int from,to,cost,net;
   edge(int f = 0, int t = 0, int cost = 0, int nex = 0)
   {
       from = f;
       to = t;
       this->cost = cost;
       net = nex;
   }
}edges[1010101];
int tot,head[101001],mx[101011],minn =0x3f3f3f3f,root;
int vis[1010110];
void add(int x, int y, int z)
{
   edges[++tot] = edge(x,y,z,head[x]);
   head[x] = tot;
}
void find(int x,int fa)
{
   size[x] = 1;mx[x] = 0;
   for (int i = head[x];i; i =edges[i].net)
   {
       edge v = edges[i];
       if(v.to == fa || vis[v.to]) continue;
       find(v.to,x);
       size[x] += size[v.to];
       chkmax(mx[x],size[v.to]);
   }
   chkmax(mx[x], S - size[x]);
   if(mx[x] < mx[root])
   {
       root = x;
   }
  
}
int que[1010110],ans[102210101];
int dis[1010101],hhd,a[10101101];
void get_dis(int x, int len, int fa)
{
   dis[++hhd] = a[x];
   for (int i = head[x]; i; i = edges[i].net)
   {
       edge v = edges[i];
       if(vis[v.to]||v.to == fa) continue;
       a[v.to] = len + edges[i].cost;
       get_dis(v.to,len + edges[i].cost,x);
   }
}
void solve(int s, int len, int w)
{
   hhd = 0;
   a[s] = len;
   get_dis(s,len,0);
       for (int i1 = 1; i1 <= hhd; i1++)
           for (int i2 = 1; i2 <= hhd; i2++)
           {
           	if(i1 != i2)
           	{
                	if (dis[i1] + dis[i2] < 10221010) ans[dis[i1] + dis[i2]] += w;
               }
           }
}
void Divide(int x)
{   
   solve(x,0,1);
   vis[x] = 1;
   for (int i = head[x]; i; i = edges[i].net)
   {
       edge v = edges[i];
       if(vis[v.to]) continue;
       solve(v.to,edges[i].cost,-1);
       S = size[x];root = 0; mx[0] = n;
       find(v.to,x);
       Divide(root);
   }
}
int main()
{
   read(n); read(m);
   for (int i = 1; i < n; i++)
   {
       int x,y,z;
       read(x); read(y); read(z);
       add(x,y,z);
       add(y,x,z);
   }
   S = n;mx[0] = n;root = 0;
// minn = 0x3f3f3f3f;
   find(1,0);    
  // printf("%d\n",mx[root]);
   Divide(root);
   for (int i = 1; i <= m; i++)
   {
       int k;
       read(k);
       printf("%s\n",(ans[k]) ? "AYE" : "NAY");
       //printf("%d\n",ans[k]);
   }
   return 0;
}
