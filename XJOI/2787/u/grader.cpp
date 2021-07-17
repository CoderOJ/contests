#ifndef GRADER
#define GRADER
#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9')
	{
		t=c=='-'?-1:1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		r=r*10+c-48;
		c=getchar();
	}
	return r*t;
}
namespace grader
{
	const int N=100010,M=100000000;
	int n,m,a[N],b[N];
	void init()
	{
		n=read(); m=read();
		fr(i,1,n) a[i]=read();
		fr(i,1,m) b[i]=read();
		a[0]=b[0]=-4*M; a[n+1]=b[m+1]=4*M;
		std::sort(a+1,a+n+1); std::sort(b+1,b+m+1);
	}
  int cnt=0;
	int query(int x,int y)
	{
    cnt++;
//		printf("%d %d\n",x,y);
		assert(-M<=x&&x<=M&&-M<=y&&y<=M);
		int p1=std::lower_bound(a+1,a+n+1,x)-a,p2=std::lower_bound(b+1,b+m+1,y)-b;
		return std::min({a[p1]-x,x-a[p1-1],b[p2]-y,y-b[p2-1]});
	}
	void check(std::pair<std::vector<int>,std::vector<int> > a)
	{
		std::sort(a.first.begin(),a.first.end()); std::sort(a.second.begin(),a.second.end());
		assert(a.first.size()==n&&a.second.size()==m);
		fr(i,1,n) assert(a.first[i-1]==::grader::a[i]);
		fr(i,1,m) assert(a.second[i-1]==::grader::b[i]);
	}
}
int query(int x,int y){ return grader::query(x,y); }
std::pair<std::vector<int>,std::vector<int> > solve();
int main()
{
	grader::init(); grader::check(solve());
  std::cout << grader::cnt << std::endl;
	printf("Accepted!\n");
}
#endif
