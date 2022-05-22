#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>
#include "treasure.h"
using namespace std;
namespace __Alice{
	inline int read(){
	int x = 0,y = 0,c = getchar();
		while(c < '0' || c > '9') y = c,c = getchar();
		while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = getchar();
		return y == '-' ? -x : x;
	}
	inline void print(int x){
		if(x >= 10) print(x / 10);
		putchar(x % 10 + '0');
	}
	inline void err(const char *c){
		printf("0\nERR: %s\n",c);
		exit(0);
	}
	inline int read(int l,int r){
		int x = read();
		if(x < l || x > r) err("The input is out of range!");
		return x;
	}
	int testid,n,m,x;
	struct edge{
		int to,nxt;
	}e[4000010];
	int cnt = 1,fir[1000010];
	int fr[2000010],to[2000010];
	bool dir[2000010];
	inline void ins(int u,int v){
		e[++cnt].to = v;e[cnt].nxt = fir[u];fir[u] = cnt;
		e[++cnt].to = u;e[cnt].nxt = fir[v];fir[v] = cnt;
	}
	int vis[1000010],tot;
	void dfs(int x,int lstv,int lste){
		for(int i = fir[x];i;i = e[i].nxt) if(i != (lste ^ 1)){
			int y = e[i].to;
			if(y == lstv || vis[x] == vis[y]) err("The graph is invalid!");
			if(vis[y]) continue;
			vis[y] = 3 - vis[x];++tot;
			dfs(y,x,i);
		}
	}
	int p[2000010];
	long long s1 = 19491001,s2 = 23333333,s3 = 998244853,srd;
	inline long long rd(){
		return srd = (srd * s1 + s2 + rand()) % s3;
	}
	#define pc putchar
	void main(){
		srand(time(0));rd();
		int i,u,v;
		testid = read();
		n = read(2,1000000);
		m = read(n - 1,2000000);
		x = read(0,n - 1);
		memset(fr,0,sizeof(fr));
		memset(to,0,sizeof(to));
		memset(dir,0,sizeof(dir));
		for(i = 0;i < m;++i){
			u = read(0,n - 1);v = read(0,n - 1);
			fr[i] = u;to[i] = v;
			ins(u,v);
		}
		tot = 1;vis[0] = 1;
		dfs(0,-1,-1); 
		if(tot != n) err("The graph is invalid!");
		Alice(testid,n,m,x,fr,to,dir);
		if(testid < 16 || testid > 18){
			for(i = 0;i < n;++i) p[i] = i;
			for(i = 0;i < n;++i) swap(p[i],p[rd() % (i + 1)]);
			x = p[x];
			for(i = 0;i < m;++i){
				fr[i] = p[fr[i]];to[i] = p[to[i]];
			}
		}
		for(i = 0;i < m;++i) p[i] = i;
		for(i = 0;i < m;++i) swap(p[i],p[rd() % (i + 1)]);
		printf("1\n");
		print(testid);pc(' ');print(n);pc(' ');print(m);pc(' ');print(x);pc('\n');
		for(i = 0;i < m;++i){
			print(fr[p[i]]);pc(' ');print(to[p[i]]);pc(' ');print(dir[p[i]]);pc('\n'); 
		}
		
	}
	#undef pc
}
vector<pair<int,bool>> discover(int pos){
	vector<pair<int,bool>> p;
	__Alice::err("Invalid discover!");
	return p;
}
int main(){
	__Alice::main();
	return 0;
}
