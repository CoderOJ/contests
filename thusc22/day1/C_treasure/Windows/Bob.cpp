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
namespace __Bob{
	inline void err(const char *c){
		printf("ERR: %s\n",c);
		exit(0);
	}
	inline int read(){
		int x = 0,y = 0,c = getchar();
		if(c == EOF) err("Runtime error!");
		while(c < '0' || c > '9') y = c,c = getchar();
		while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = getchar();
		return y == '-' ? -x : x;
	}
	inline int read(int l,int r){
		int x = read();
		if(x < l || x > r) err("The input is out of range!");
		return x;
	}
	int testid,n,m,x;
	vector<pair<int,bool>> e[1000010];
	int cnt;
	bool vis[1000010];
	inline void ins(int u,int v,bool w){
		e[u].push_back(make_pair(v,w));
		e[v].push_back(make_pair(u,!w));
	}
	vector<pair<int,bool>> discover(int pos){
		if(++cnt > 500000) err("Too many discover!");
		if(pos < 0 || pos >= n || vis[pos]) err("Invalid discover!");
		vis[pos] = 1;
		return e[pos];
	}
	void main(){
		int i,j,u,v;
		bool w = read(0,1);
		if(!w){
			for(char ch = getchar();ch != EOF;ch = getchar()) putchar(ch);
			exit(0);
		}
		testid = read();
		n = read(2,1000000);
		m = read(n - 1,2000000);
		x = read(0,n - 1);
		for(i = 0;i < m;++i){
			u = read(0,n - 1);v = read(0,n - 1);w = read(0,1);
			ins(u,v,w);
		}
		memset(vis,0,sizeof(vis));
		int ans = Bob(testid,n);
		if(ans != x) err("Wrong answer!");
		printf("Correct.\ncnt = %d\n",cnt);
	}
}
vector<pair<int,bool>> discover(int pos){
	return __Bob::discover(pos);
}
int main(){
	__Bob::main();
	return 0;
}
