#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=10000;
int ans[2*MAXN+5],f[1000+5][1000+5];
int n,num,now=1,k=1;
struct node
{
	int id,num;
}cnt[5+5];
bool cmp(node a,node b)
{
	if(a.num==b.num)
		return a.id<b.id;
	return a.num<b.num;
}
void Put(int x,int y)
{
	sort(cnt+1,cnt+5+1,cmp);
	bool vis[10];
	memset(vis,false,sizeof(vis));
	vis[f[x-1][y-1]]=vis[f[x+1][y+1]]=vis[f[x][y-1]]=vis[f[x][y+1]]=vis[f[x-1][y]]=vis[f[x+1][y]]=true;
	for(int i=1;i<=5;i++)
		if(!vis[cnt[i].id])
		{
			cnt[i].num++;
			f[x][y]=cnt[i].id;
			ans[now]=cnt[i].id;
			break;
		}
}
void Solve()
{
	int x=250,y=250;
	for(int i=1;i<=5;i++)
		cnt[i].id=i;
	f[x][y]=1;
	ans[1]=1;
	cnt[1].num++;
	while(now<10005)
	{
		x++;
		y++;
		for(int i=1;i<=k;i++) now++,x--,Put(x,y);
		for(int i=1;i<=k;i++) now++,x--,y--,Put(x,y);
		for(int i=1;i<=k;i++) now++,y--,Put(x,y);
		for(int i=1;i<=k;i++) now++,x++,Put(x,y);
		for(int i=1;i<=k;i++) now++,x++,y++,Put(x,y);
		for(int i=1;i<=k;i++) now++,y++,Put(x,y);
		k++;
	}
}
int main()
{
	Solve();
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		printf("%d\n",ans[n]);
	}
	return 0;
}
