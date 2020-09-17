#include <bits/stdc++.h>
#define ll long long
#define inf 1e9
#define m_k make_pair
using namespace std;
int n,m,l,r,vi[1100];
long double V,v[1100],sum[1100];
long double a[1100];
long double ans,dp[1100][1100];
int main()
{
	scanf("%d%d%d%d%Lf",&n,&m,&l,&r,&V);
	for (int i=1;i<=n;i++)
	  scanf("%Lf",&v[i]);
	dp[0][0]=1.0;
	for (int i=1;i<=n;i++)
	{
		dp[i][m+1]=dp[i-1][m+1];
		for (int j=0;j<m;j++)
		{
			if (dp[i-1][j]==0)
			  continue;
			int L,R;
			L=j+l;R=j+r;
			if (l>=m)
			{
				dp[i][m+1]+=dp[i-1][j];
				continue;
			}
			if (R>=m)
			{
				long double g;
				g=(long double)(R-m+1)/((r-l+1)*1.0);
				dp[i][m+1]+=g*dp[i-1][j];
				R=m-1;
			}
			dp[i][L]+=dp[i-1][j]/((r-l+1)*1.0);
			dp[i][R+1]-=dp[i-1][j]/((r-l+1)*1.0);
		}
		for (int j=1;j<=m;j++)
		  dp[i][j]=dp[i][j]+dp[i][j-1];
	}
	for (int i=1;i<=n;i++)
	  a[i]=v[i];
	sort(a+1,a+1+n);
	for (int i=1;i<=n;i++)
	  sum[i]=sum[i-1]+v[i];
	ans=sum[n];
	long double cnt;
	cnt=dp[n][m+1]*V;
	for (int i=1;i<n;i++)
	  cnt+=dp[i][m+1]*(long double)(sum[n]-sum[i]);
    cout << cnt << endl;
	ans=max(ans,cnt);
	for (int i=n;i>=1;i--)
	{
		vector <long double> b;
		b.push_back(0);//convenient to write
		cnt=0.0;
		for (int j=1;j<=n;j++)
		{
			if (v[j]==a[i])
			{
				vi[j]=1;
				break;
			}
		}
		for (int j=1;j<=n;j++)
		{
			if (vi[j])
			  cnt+=v[j];
			else
			  b.push_back(v[j]);
		}
		for (int j=1;j<(int)b.size();j++)
		  sum[j]=sum[j-1]+b[j];
		cnt+=dp[(int)b.size()-1][m+1]*V;
		for (int j=1;j<(int)b.size()-1;j++)
	  	  cnt+=dp[j][m+1]*(long double)(sum[(int)b.size()-1]-sum[j]);
	  	ans=max(ans,cnt);
        cout << cnt << endl;
	}
	printf("%.3Lf\n",ans);
}
