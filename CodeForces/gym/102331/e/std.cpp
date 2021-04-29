#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<bitset>
typedef long long ll;
typedef unsigned long long ull;
typedef std::bitset<128> bits;
typedef unsigned un;
typedef std::vector<int> P;
typedef std::pair<int,int> pii;
ull read(){ll x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9')x=x*10+(c-'0'),c=getchar();return f*x;}
ll max(ll a,ll b){return a>b?a:b;}
ll min(ll a,ll b){return a<b?a:b;}
template <typename T> bool umax(T& a,T t){if(t>a)return a=t,1;return 0;}
template <typename T> bool umin(T& a,T t){if(t<a)return a=t,1;return 0;}
/**********/
bits a[128];
int val[128];
ll ans=0;
void insert(bits& x,int k)
{
	for(int i=126;i>=0;--i)
		if(x[i])
		{
			if(a[i].none()){a[i]=x;val[i]=k;ans+=k; return;}
			else if(val[i]<k)ans+=k-val[i],std::swap(a[i],x) ,std::swap(val[i],k);
			x^=a[i];
		}
}
int main()
{
	int n=read(),q=read();
	while(q--)
	{
		int x=read()-1,y=read()-1;
		ull w=read();
		int k=read();
		bits a;
		a[x]=a[y]=1;
		for(int i=0;i<60;++i)
			if(w&(1ull<<i))a[n+i]=1;
		insert(a,k);
		printf("%lld\n",ans);
	}
	return 0;
}
