#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <vector>
#include <queue>
#define setIO(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout)
#define closefile fclose(stdin),fclose(stdout)
#define see(x) cerr<<x<<" "
#define seeln(x) cerr<<x<<endl
#define out(x) cerr<<#x<<" = "<<x<<" "
#define outln(x) cerr<<#x<<" = "<<x<<endl
#define outarr(x,l,r) cerr<<#x"["<<l<<"-"<<r<<"] = "; for (int _i=l;_i<=r;++_i) cerr<<x[_i]<<" "; cerr<<endl;
#define m_p make_pair
#define sz(x) (int)x.size() 
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
template <class T> void read(T &x)
{
	x=0; char c=getchar(); int flag=0;
	while (c<'0'||c>'9') flag|=(c=='-'),c=getchar();
	while (c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	if (flag) x=-x;
}
template <class T> T _max(T a,T b){return b>a ? b : a;}
template <class T> T _min(T a,T b){return b<a ? b : a;}
template <class T> bool checkmax(T &a,T b){return b>a ? a=b,1 : 0;}
template <class T> bool checkmin(T &a,T b){return b<a ? a=b,1 : 0;}
const int N=1050000;
char s[N];
int csp[N],n;
int cnt[30];
int pre[N],suf[N],g[N];
ll f[N][27];
void init()
{
	scanf("%s",s);
	n=strlen(s);
	memset(cnt,0,sizeof cnt);
	int i=1,j=0;
	for (;i<n;++i)
	{
		while (j&&s[i]!=s[j]) j=csp[j-1];
		if (s[i]==s[j]) ++j,csp[i]=j;
		else csp[i]=0;
	}
	for (int i=0,tot=0;i<n;++i)
	{
		int d=s[i]-'a';
		if (cnt[d]) --tot;
		else ++tot;
		cnt[d]^=1;
		pre[i]=tot; 
	}
	memset(cnt,0,sizeof cnt);
	for (int i=n-1,tot=0;i>=0;--i)
	{
		int d=s[i]-'a';
		if (cnt[d]) --tot;
		else ++tot;
		cnt[d]^=1;
		suf[i]=tot; 
	}
	for (int i=0,l=1;i<n;++i,++l)
	{
		if (csp[i]==0||l%(l-csp[i])) g[i]=0;
		else g[i]=l-csp[i];
	}
	for (int i=0;i<n;++i)
	{
		for (int j=0;j<=26;++j)
		{
			f[i][j]=f[i-1][j];
		}
		f[i][pre[i]]++;
	}
	for (int i=0;i<n;++i)
	{
		for (int j=1;j<=26;++j) f[i][j]+=f[i][j-1];
	}
}

void solve()
{
	ll ans=0;
	for (int l=2;l<=n-1;++l)
	{
		for (int i=l;i<=n-1;i+=l)
		{
			int error=0;
			if (!g[i-1]) error=1;
			else if (l%g[i-1]) error=1;
			if (i==l) error=0;
			if (error) continue;
			int lim=suf[i];
			ans+=f[l-2][lim];
		}
	}
	printf("%lld\n",ans);
}

int main()
{
	int t; read(t); while (t--)
	{
		init();
		solve();
	}
	closefile;
	return 0;
}
