#include<set>
#include<map>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define pb push_back
#define fi first
#define se second
#define mp make_pair
using namespace std;

typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pi;

const int N=400005;

char S[N];
int n,tot(1),la,ch[N][26],len[N],fa[N],pos[N],rt[N],cnt,rk[N],ar[N],dp[N],fr[N],Ans;

struct node {
	int lc,rc;
}t[N*20];

void Upd(int &u,int l,int r,int p)
{
	if(!u)
		u=++cnt;
	if(l!=r)
	{
		int m=(l+r)>>1;
		if(m>=p) Upd(t[u].lc,l,m,p);
		else Upd(t[u].rc,m+1,r,p);
	}
}

int Merge(int x,int y,int l,int r)
{
	if(!x||!y)
		return x+y;
	int o=++cnt;
	if(l!=r)
	{
		int m=(l+r)>>1;
		t[o].lc=Merge(t[x].lc,t[y].lc,l,m);
		t[o].rc=Merge(t[x].rc,t[y].rc,m+1,r);
	}
	return o;
}

int Query(int u,int l,int r,int L,int R)
{
	if(!u||l>R||r<L)
		return 0;
	if(l>=L&&r<=R)
		return 1;
	int m=(l+r)>>1;
	return Query(t[u].lc,l,m,L,R)||Query(t[u].rc,m+1,r,L,R);
}

void extend(int id,int where)
{
	int p=la;
	int np=++tot;
	len[np]=len[p]+1;
	pos[np]=where;
	while(p && !ch[p][id])
	{
		ch[p][id]=np;
		p=fa[p];
	}
	if(!p)
	{
		fa[np]=1;
	}
	else
	{
		int q=ch[p][id];
		if(len[p]+1==len[q])
		{
			fa[np]=q;
		}
		else
		{
			int nq=++tot;
			len[nq]=len[p]+1;
			fa[nq]=fa[q];
			pos[nq]=pos[q];
			for(int i=0; i<26; i++)
				ch[nq][i]=ch[q][i];
			fa[np]=fa[q]=nq;
			while(p && ch[p][id]==q)
			{
				ch[p][id]=nq;
				p=fa[p];
			}
		}
	}
	la=np;
	Upd(rt[la],1,n,where);
}

void Sort()
{
	for(int i=1; i<=tot; i++) ar[len[i]]++;
	for(int i=1; i<=n; i++) ar[i]+=ar[i-1];
	for(int i=1; i<=tot; i++) rk[ar[len[i]]--]=i;
}

int main()
{
	scanf("%d%s",&n,S+1);
	la=1;
	for(int i=1; i<=n; i++) extend(S[i]-'a',i);
	Sort();
	for(int i=tot; i!=1; i--)
	{
		int u=rk[i],v=fa[u];
		rt[v]=Merge(rt[v],rt[u],1,n);
	}
	for(int i=2; i<=tot; i++)
	{
		int u=rk[i],v=fa[u];
		if(v==1)
		{
			dp[u]=1;
			fr[u]=u;
		}
		else if(Query(rt[fr[v]],1,n,pos[u]-len[u]+len[fr[v]],pos[u]-1))
		{
			dp[u]=dp[v]+1;
			fr[u]=u;
		}
		else
		{
			dp[u]=dp[v];
			fr[u]=fr[v];
		}
		Ans=max(Ans,dp[u]);
	}
	printf("%d",Ans);
	return 0;
}
