#include<bits/stdc++.h>
using namespace std;
const int inf=2147483647;
int a[2010],b[2010],n;
map<string,int>f[2010][10];
int abs(int x){return x>0?x:-x;}
int dfs(int x,int fl,string st)
{
	if(x>=n&&st=="0000")return 0;
	int&ans=f[x][fl][st],tim,xx;
	string s;
	if(ans)return ans;
	ans=inf;
	for(int i=1;i<=10;i++)
	{
		tim=0;s=st;xx=x;
		for(int j=0;j<4;j++)if(s[j]==i+'0'){s[j]='0';tim++;}
		for(int j=0;j<4;j++)if(s[j]=='0'&&a[xx+1]==i){s[j]=b[xx+1]+'0';tim++;xx++;}
		sort(s.begin(),s.end());
		if(xx!=x||st!=s)ans=min(ans,tim+abs(fl-i)+dfs(xx,i,s));
	}
	return ans;
}
int main()
{
	scanf("%d",&n); int dull; scanf("%d",&dull);
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i],&b[i]);
	printf("%d",dfs(0,1,"0000"));
	return 0;
}
