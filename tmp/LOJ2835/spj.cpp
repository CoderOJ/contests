#include <queue>
#include "testlib.h"
using namespace std;

struct Link
{
	int to,nxt;
};

Link e[5000];
int head[1010],cnt;
int n,k,w,w0,x,y,d[1010];
bool vis[1010];
double s,p;
priority_queue <pair<int,int> > q;

inline void add(int x,int y)
{
	e[cnt]=(Link){y,head[x]};head[x]=cnt++;
	e[cnt]=(Link){x,head[y]};head[y]=cnt++;
}

inline void Dijkstra(int S)
{
	memset(d,0x7f,sizeof d);q.push(make_pair(0,S));d[S]=0;
	while (!q.empty())
	{
		int x=q.top().second;q.pop();
		for (int i=head[x];~i;i=e[i].nxt)
			if (d[e[i].to]>d[x]+1)
			{
				d[e[i].to]=d[x]+1;
				q.push(make_pair(d[e[i].to],e[i].to));
			}
	}
	return ;
}

int main(int argc, char *argv[])
{
	memset(head,-1,sizeof head);
	registerTestlibCmd(argc, argv);
	n=inf.readInt();k=inf.readInt();w0=inf.readInt();
	for (int i=1;i<n;i++)
	{
		x=inf.readInt();y=inf.readInt();
		add(x,y);
	}
	for (int i=1;i<=k;i++)
	{
		x=ouf.readInt();y=ouf.readInt();
		add(x,y);
	}
	for (int i=1;i<=n;i++)
	{
		Dijkstra(i);
		for (int j=i;j<=n;j++) w+=d[j];
	}
	s=1.0-(double)w/(double)w0;
	if (n==20)
	{
		p=min(10.0,10.0*pow(20.0,s));p=round(p);
		p=p*10.0;
	}
	else
	{
		p=min(18.0,18.0*pow(20.0,s));p=round(p);
		p=p*100.0/18.0;
	}
	if (p==100.0)
		quitf(_ok,"Your solution is acceptable!^ ^\nYour total distance is %d, and s=%.10lf", w, s);
	else quitp(p,"Solution OK!\nYour total distance is %d, and s=%.10lf", w, s);
	return 0;
}