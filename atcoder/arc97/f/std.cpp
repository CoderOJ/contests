#include<bits/stdc++.h>
#define reg
#define maxn 200001
using namespace std;
int nt[maxn << 1], fi[maxn], go[maxn], d[maxn], rt;
int dp[maxn], n, sum, sumx, siz[maxn], ans, cnt;
char s[maxn];
vector<int> Q[maxn];
inline int  read() {
    reg int s = 0, t = 0; reg char ch = getchar();
    while(ch > '9' || ch < '0') t |= ch == '-', ch = getchar();
    while(ch >= '0' && ch <= '9') s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
    return t ? -s : s;
}
void add(int u, int v){
	nt[++cnt] = fi[u]; fi[u] = cnt; go[cnt] = v;
}
void dfs(int u, int fa){
	siz[u] = (s[u] == 'W'); 
	for(int i = fi[u]; i; i = nt[i]){
		int v = go[i]; if(v == fa) continue;
		dfs(v, u); siz[u] += siz[v];
		if(siz[v] != ans && siz[v] != 0){
			Q[u].push_back(v); Q[v].push_back(u);
		}
	}
}
void find(int x, int fa){
	sum += 2;  d[x] = 0;
	if(s[x] == 'W' && Q[x].size() % 2 == 0) sum += 1, d[x] = 2;
	if(s[x] == 'B' && Q[x].size() % 2 == 1) sum += 1, d[x] = 2;
	for(int i = 0; i < Q[x].size(); i++){
		int v = Q[x][i]; if(v == fa) continue;
		find(v, x);
	}
}
void solve(int x, int fa){
	dp[x] = d[x]; int maxx = 0, cmaxx = 0;
	for(int i = 0; i < Q[x].size(); i++){
		int v = Q[x][i]; if(v == fa) continue;
		solve(v, x); 
		if(dp[v] > maxx) cmaxx = maxx, maxx = dp[v];
		else if(dp[v] > cmaxx) cmaxx = dp[v];
		
	}
	sumx = max(sumx, maxx + cmaxx + d[x]);
	dp[x] += maxx;
}
int main()
{
	n = read();
	for(int i = 1; i < n; i++){
		int x = read(), y = read();
		add(x, y); add(y, x);
	}
	scanf("%s", s + 1);
	for(int i = 1; i <= n; i++) {
		ans += ((s[i] == 'W') ? 1 : 0);
		if(s[i] == 'W') rt = i;
	}
	if(ans == 0) {puts("0"); return 0;}
	if(ans == 1) {printf("1"); return 0;}
	dfs(1, 0);  find(rt, 0);
	sum = sum - 2; 	solve(rt, 0);
	cout << sum - sumx << endl;
	return 0;
}

