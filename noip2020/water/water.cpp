#include <bits/stdc++.h>

#define rep(i,n) for (int i=0;i<n;++i)
#define repa(i,n) for (int i=1;i<=n;++i)
template <class T> inline bool checkMin(T& a, T b) { return a>b ? a=b,1 : 0; }
template <class T> inline bool checkMax(T& a, T b) { return a<b ? a=b,1 : 0; }

void file() {
#ifndef __LOCALE__
	freopen("water.in", "r", stdin);
	freopen("water.out", "w", stdout);
#endif
}

long long gcd(long long a, long long b) {
	return b == 0 ? a : gcd(b, a%b); }
struct Num {
	long long a, b;
	Num () { a=0; b=1; }
	void set(long long x) { a=x; b=1; }
	void add(const Num& B) {
		long long oa=a, ob=b;
		a = oa*B.b + ob*B.a;
		b = ob * B.b; 
		long long g = gcd(a,b); a /= g; b /= g;
	}
	void split(long long x) { b *= x; }
	void output() {
		long long g = gcd(a,b);
		printf("%lld %lld\n", a/g, b/g); }
};

const int N = 100005;
std::vector<int> e[N];
Num flow[N];
int in[N], n, m;

int main() {
	file();
	scanf("%d%d", &n, &m);
	repa (i,n) {
		int t; scanf("%d", &t);
		while (t--) { int v; scanf("%d", &v); e[i].push_back(v); in[v]++; } }
	std::queue<int> que;
	repa (i,m) { flow[i].set(1); que.push(i); }
	while (!que.empty()) {
		int u = que.front(); que.pop();
		if (e[u].size() == 0) { continue; }
		Num pos = flow[u]; pos.split( e[u].size() );
		for (int i=0; i<(int)(e[u].size()); ++i) {
			int v = e[u][i];
			flow[v].add(pos);
			// printf("v=%d, flow[v].a=%lld flow[v].b=%lld\n", v,flow[v].a,flow[v].b);
			in[v]--; if(in[v]==0) { que.push(v); }
		}
	}
	repa (i,n) { if (e[i].size() == 0) { flow[i].output(); } }
	return 0;
}
