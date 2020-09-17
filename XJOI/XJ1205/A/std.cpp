#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
struct edge{
    int v,c,f;
}e[100010];
int fi[100010],ne[100010],la[100010],q[200020],d[100010],flow[100010],x,ansflow,anscost,tot,pe[100010],n,m,s,t,b[200010],pre[200010],u,v,w,f;
void add(int x,int y,int f,int c){
    e[++tot].v=y;e[tot].c=c;e[tot].f=f;
    !fi[x]?fi[x]=tot:ne[la[x]]=tot;la[x]=tot;
    e[++tot].v=x;e[tot].c=-c;e[tot].f=0;
    !fi[y]?fi[y]=tot:ne[la[y]]=tot;la[y]=tot;
}
bool spfa(int s,int t){
    int H=0,T=0;
    memset(d,0x3f,sizeof(d));
    memset(flow,0,sizeof(flow));
    q[++T]=s;b[s]=1;d[s]=0;pre[s]=0;flow[s]=0x7fffffff;
    while(H<T){
        int x=q[++H];
        for(int i=fi[x];i;i=ne[i]){
            int y=e[i].v,z=e[i].f,c=e[i].c;    
            if(z>0&&d[y]>d[x]+c){
                d[y]=d[x]+c;
                pre[y]=x;
                pe[y]=i;
                flow[y]=min(flow[x],z);
                if(!b[y])b[y]=1,q[++T]=y;
            }
        }
    
        b[x]=0;
    }
    return d[t]!=0x3f3f3f3f;
}
void maxflow(){
    while(spfa(s,t)){
        int k=t;
        while(k!=s){
            e[pe[k]].f-=flow[t];
            e[pe[k]^1].f+=flow[t];
            k=pre[k];
        }
        ansflow+=flow[t];
        anscost+=d[t]*flow[t];
    }
}
int main(){
    scanf("%d",&n);
    tot=1;
    for(int i=1;i<=n;i++){
        scanf("%d",&x);    
        int pr=i==1?n:i-1,nx=i==n?1:i+1;
        add(0,i,x,0);
        add(i,nx+n,0x3f3f3f3f,1);
        add(nx+n,i,0x3f3f3f3f,1);
        add(i,pr+n,0x3f3f3f3f,1);
        add(pr+n,i,0x3f3f3f3f,1);
        add(i,i+n,0x3f3f3f3f,0);
        add(i+n,i,0x3f3f3f3f,0);
        add(i+n,2*n+1,1,0);
    }
    s=0;t=2*n+1;
    maxflow();
    printf("%d",anscost);
}
