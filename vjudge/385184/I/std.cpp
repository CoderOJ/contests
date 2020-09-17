#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
using namespace std;

long long ans=0;
int tot=0,h[100005];
int n,m,x,y,S,T,k[100005],siz[100005];
int s[100005],top;
bool odd;
struct Edge{
	int x,next;
}e[200005];

inline void add_edge(int x,int y){
	e[++tot].x=y;
	e[tot].next=h[x],h[x]=tot;
}

void dfs1(int x,int fa){
	for(int i=h[x];i;i=e[i].next){
		if(e[i].x==fa)continue;
		if(siz[e[i].x]){
			if(siz[x]==siz[e[i].x])odd=true;
			S=x,T=e[i].x;
		}else{
			siz[e[i].x]=-siz[x];
			dfs1(e[i].x,x);
		}
	}
}

void dfs2(int x,int fa){
	for(int i=h[x];i;i=e[i].next){
		if(e[i].x==fa||(x==S&&e[i].x==T)||(x==T&&e[i].x==S))continue;
		dfs2(e[i].x,x);
		siz[x]+=siz[e[i].x];
		k[x]+=k[e[i].x];
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	siz[1]=1,dfs1(1,0);
	int sum=0;
	for(int i=1;i<=n;i++)sum+=siz[i];
	if(m==n-1){
		if(sum)return printf("-1"),0;
	}else{
		if(odd){
			if(sum&1)return printf("-1"),0;
			ans+=abs(sum>>1);
			siz[S]-=sum>>1,siz[T]-=sum>>1;
		}else{
			if(sum)return printf("-1"),0;
			else k[S]=1,k[T]=-1;
		}
	}
	dfs2(1,0);
	for(int i=1;i<=n;i++){
		if(k[i])s[++top]=k[i]*siz[i];
		else ans+=abs(siz[i]);
	}
	s[++top]=0;
	sort(s+1,s+top+1);
	int mid=s[top+1>>1];
	for(int i=1;i<=top;i++)ans+=abs(s[i]-mid);
	printf("%lld",ans);
}
