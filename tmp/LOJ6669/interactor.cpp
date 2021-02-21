#include "/home/jack/include/testlib.h"
#include <iostream>
using namespace std;

const int N=3010;
const int MAXQUERY = 30000;

void add(int u,int v);
void dfs1(int u);
void dfs2(int u);

int head[N],nxt[N],to[N],cnt;
int n,fa[N],son[N],siz[N],dep[N],top[N],tot;

int main(int argc, char* argv[])
{
    registerInteraction(argc, argv);
	
    int i,u,v,x,y,lca;
    string s;
    
    n=inf.readInt();
    cout<<n<<endl;
    
    for (i=2;i<=n;++i)
    {
    	fa[i]=inf.readInt();
    	add(fa[i],i);
    }
	
    dfs1(1);
    top[1]=1;
    dfs2(1);
    
    while (1)
    {
    	s=ouf.readWord();
    	if (s=="?")
    	{
    		++tot;
    		x=u=ouf.readInt(1,n,"u");
    		y=v=ouf.readInt(1,n,"v");
    		while (top[x]!=top[y])
    		{
    			if (dep[top[x]]>dep[top[y]]) x=fa[top[x]];
    			else y=fa[top[y]];
    		}
    		lca=(dep[x]<dep[y]?x:y);
    		cout<<dep[u]+dep[v]-2*dep[lca]<<endl;
    	}
    	else if (s=="!")
    	{
    		for (i=2;i<=n;++i)
    		{
    			x=ouf.readInt(1,n,"p");
    			if (x != fa[i])
					quitf(_wa, "%d%s node's parent is incorrect, read %d, expected %d", i, englishEnding(i).c_str(), x, fa[i]);
    		}
			if (tot > MAXQUERY)
			{
				quitf(_wa, "too much queries: %d queries", tot);
			}
			else
			{
				quitf(_ok, "ok, %d queries", tot);
			}
    		break;
    	}
    	else
    	{
    		quitf(_wa, "invalid format");
    		break;
    	}
    }
    
    return 0;
}

void dfs1(int u)
{
	int i,v;
	siz[u]=1;
	for (i=head[u];i;i=nxt[i])
	{
		v=to[i];
		if (v!=fa[u])
		{
			dep[v]=dep[u]+1;
			dfs1(v);
			siz[u]+=siz[v];
			if (siz[son[u]]<siz[v])
			{
				son[u]=v;
			}
		}
	}
}

void dfs2(int u)
{
	int i,v;
	if (son[u])
	{
		top[son[u]]=top[u];
		dfs2(son[u]);
	}
	for (i=head[u];i;i=nxt[i])
	{
		v=to[i];
		if (v!=fa[u]&&v!=son[u])
		{
			top[v]=v;
			dfs2(v);
		}
	}
}

void add(int u,int v)
{
	nxt[++cnt]=head[u];
	head[u]=cnt;
	to[cnt]=v;
}
