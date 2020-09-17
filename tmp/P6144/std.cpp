#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int mod=1000000007,N=1e6;
struct P{int l,r;}w[N];
int s[20][20],n,K,f[11],tmp[11];
struct Seg
{
	int a[N][11],tag[N];
	void upd(int rot,int w)
	{
		for(int i=0;i<=K;i++)a[rot][i]=(1ll*w*a[rot][i])%mod;tag[rot]=1ll*tag[rot]*w%mod;
	}
	void pushdown(int rot)
	{
		if(tag[rot]!=1)
		{
			int t=tag[rot];tag[rot]=1;
			upd(rot<<1,t),upd(rot<<1|1,t);
		}
	}
	void update(int rot,int lt,int rt,int lq,int rq)
	{
		if(lt>=lq&&rt<=rq){upd(rot,2);return;}
		int mid=(lt+rt)>>1;pushdown(rot);
		if(lq<=mid)update(rot<<1,lt,mid,lq,rq);
		if(rq>mid)update(rot<<1|1,mid+1,rt,lq,rq);
		for(int i=0;i<=K;i++)a[rot][i]=(a[rot<<1][i]+a[rot<<1|1][i])%mod;
	}
	void ins(int rot,int lt,int rt,int q,int w[])
	{
		for(int i=0;i<=K;i++)a[rot][i]=(a[rot][i]+w[i])%mod;
		if(lt==rt)return;
		int mid=(lt+rt)>>1;pushdown(rot);
		if(q<=mid)ins(rot<<1,lt,mid,q,w);
		else ins(rot<<1|1,mid+1,rt,q,w);
	}
	void query(int rot,int lt,int rt,int lq,int rq,int w[])
	{
		if(lt>=lq&&rt<=rq){for(int i=0;i<=K;i++)w[i]=(w[i]+a[rot][i])%mod;return;}
		pushdown(rot);
		int mid=(lt+rt)>>1;
		if(lq<=mid)query(rot<<1,lt,mid,lq,rq,w);
		if(rq>mid)query(rot<<1|1,mid+1,rt,lq,rq,w);
	}
	void build(int rot,int lt,int rt)
	{
		tag[rot]=1;if(lt==rt)return;
		int mid=(lt+rt)>>1;build(rot<<1,lt,mid),build(rot<<1|1,mid+1,rt);
	}
}a;
void clear(int w[]){for(int i=0;i<=K;i++)w[i]=0;}
int cmp(const P &a,const P &b){return a.l<b.l;}
int main()
{
	scanf("%d%d",&n,&K);
	s[0][0]=1;
	for(int i=1;i<=K;i++)
	{
		s[i][0]=0,s[i][i]=1;
		for(int j=1;j<i;j++)s[i][j]=(s[i-1][j-1]+1ll*j*s[i-1][j])%mod;
	}
	for(int i=1;i<=n;i++)scanf("%d%d",&w[i].l,&w[i].r);
	sort(w+1,w+n+1,cmp);
	tmp[0]=1;a.ins(1,0,2*n,0,tmp);
	for(int i=1;i<=n;i++)
	{
    for (int i=0;i<=K;i++) { printf("%d ",a.a[1][i]); }
    puts("");
		clear(tmp);a.query(1,0,2*n,0,w[i].l-1,tmp);
		f[0]=tmp[0];for(int k=1;k<=K;k++)f[k]=(tmp[k-1]+tmp[k])%mod;
		clear(tmp);a.query(1,0,2*n,w[i].l,w[i].r,tmp);
		for(int k=0;k<=K;k++)f[k]=(f[k]+tmp[k])%mod;
    for (int i=0;i<=K;i++) { printf("%d ",f[i]); }
    puts("");
		a.update(1,0,2*n,w[i].r+1,2*n);
		a.ins(1,0,2*n,w[i].r,f);
	}
	int ans=0;
    for (int i=0;i<=K;i++) { printf("%d ",a.a[1][i]); }
    puts("");
	for(int i=0,fac=1;i<=K;i++,fac*=i)ans=(ans+1ll*fac*s[K][i]%mod*a.a[1][i])%mod;
	cout<<ans<<endl;
}
