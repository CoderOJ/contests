/* This is sample grader for the contestant */
#include "worldline.h"
#include <stdio.h>
#include <assert.h>

#define maxN 20010

static int t,flag,tot_query,tot_addedge,father[maxN],height[maxN];
static int A[maxN],ans[12][maxN],turn,step,n,res[12][5],N[12];

void next_step(){
	if (step!=1) flag=0; step++;
}

int findfather(int k){
	if (father[k]==k) return k;
	father[k]=findfather(father[k]);
	return father[k];
}

void link(int u,int v){
	u=findfather(u); v=findfather(v);
	if (u!=v){
		if (height[u]<height[v]){
			int t=u; u=v; v=t;
		}
		father[v]=u; if (height[u]==height[v]) height[u]++;
	}
}

void addedge(int u,int v){
	if (step!=1) flag=0; tot_addedge++;
	if (u<=0||u>n||v<=0||v>n) return;
	link(u,v);
}

int query(int u,int v){
	if (step!=2) flag=0; tot_query++;
	if (u<=0||u>n||v<=0||v>n) return 0;
	u+=n; v+=n;
	u=findfather(u); v=findfather(v);
	return u==v;
}

void new_round(){
	if (turn==2||(step!=2&&turn>0)) flag=0;
	turn++; step=1;
	for (int i=1;i<=n+n;i++) father[i]=i,height[i]=1;
	for (int i=1;i<=n;i++) link(i,A[i]+n);
}

int main()
{
	assert(scanf("%d",&t)==1);
	for (int now=1;now<=t;now++){
		assert(scanf("%d",&n)==1); N[now]=n;
		for (int i=1;i<=n;i++) assert(scanf("%d",&A[i])==1);
		flag=1; tot_query=0; tot_addedge=0; turn=0; step=0;
		res[now][1]=query_permutation(n,ans[now]);
		res[now][0]=flag; res[now][2]=tot_query; res[now][3]=tot_addedge;
		if (res[now][1]==0) for (int i=1;i<=n;i++) ans[now][i]=0;
	}
	for (int i=1;i<=t;i++){
		printf("%d %d %d %d\n",res[i][0],res[i][1],res[i][2],res[i][3]);
		for (int j=1;j<=N[i];j++) printf("%d ",ans[i][j]); printf("\n");
	}
	return 0;
}
