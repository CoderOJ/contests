#include<bits/stdc++.h>
using namespace std;
 
const int N=2e5+5;
 
inline int read()
{
    int x=0,f=1;
    char c=getchar();
    while(c<'0' || c>'9')
    {
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0' && c<='9')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
 
int n;
bool vis[N];
int mother[N],siz[N],ans[N];
inline int Find(int x)
{
    if(mother[x]==x) return x;
    return mother[x]=Find(mother[x]);
}
struct node{
    int id,val;
};
inline bool operator < (node x,node y)
{
    if(x.val!=y.val) return x.val<y.val;
    return x.id<y.id;
}
set<node> s1,s2;
set<node>::iterator it;
set<int> q[N];
 
inline void Merge(int x,int y,int c)
{
    int k1=Find(x),k2=Find(y);
    if(k1==k2) return;
    if(q[k1].size()>q[k2].size()) swap(k1,k2);
    mother[k1]=k2;
//  cout<<k1<<" "<<*q[k1].begin()<<" "<<"Yes"<<endl;
    if(q[k1].size())
    {
        s1.erase((node){k1,*q[k1].begin()});
        if(siz[k1]>1) s2.erase((node){k1,*q[k1].begin()});  
    }
    if(q[k2].size())
    {
        s1.erase((node){k2,*q[k2].begin()});
        if(siz[k2]>1) s2.erase((node){k2,*q[k2].begin()});  
    }
    siz[k2]=siz[k2]+siz[k1]+c;
    while(q[k1].size())
        q[k2].insert(*q[k1].begin()), q[k1].erase(q[k1].begin());
    if(c==-2) q[k2].erase(x),q[k2].erase(y);
    if(q[k2].size())
    {
        s1.insert((node){k2,*q[k2].begin()});
        if(siz[k2]>1) s2.insert((node){k2,*q[k2].begin()}); 
    }
}
 
int main()
{
    n=read();
    for(int i=1;i<=2*n;i++) mother[i]=i,siz[i]=1;
    for(int i=n+1;i<=2*n;i++) q[i].insert(i),s1.insert((node){i,i});
    int u,v;
    for(int i=1;i<=n-1;i++)
    {
        u=read(); v=read();
        Merge(u,v,0);
    }
    for(int x=n;x>=2;x--)
    {
        int k1=Find(x);
        if(siz[k1]==1)
        {
            it=s2.begin();
            if((*it).id==k1) it++;
            int y=(*it).val;
            vis[y]=true; ans[2*n-x+1]=y;
            Merge(x,y,-2);
        }
        else
        {
            it=s1.begin();
            if((*it).id==k1) it++;
            int y=(*it).val;
        //  cout<<(*it).id<<" "<<(*it).val<<endl;
            vis[y]=true; ans[2*n-x+1]=y;
            Merge(x,y,-2);
        }
    }
    for(int i=n+1;i<=2*n;i++)
        if(!vis[i])
        {
            ans[2*n]=i;
            break;
        }
    for(int i=1;i<=n;i++) ans[i]=i;
    for(int i=1;i<=2*n;i++) printf("%d\n",ans[i]);
    return 0;
}
