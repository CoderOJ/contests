/*program by mangoyang*/
#include <bits/stdc++.h>
#define inf (0x7f7f7f7f)
#define Max(a, b) ((a) > (b) ? (a) : (b))
#define Min(a, b) ((a) < (b) ? (a) : (b))
typedef long long ll;
using namespace std;
template <class T>
inline void read(T &x){
	int ch = 0, f = 0; x = 0;
	for(; !isdigit(ch); ch = getchar()) if(ch == '-') f = 1;
	for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
	if(f) x = -x;
}
const int N = 505, mod = 998244353;
int vis[N], pw[N], a[N], f[N][N], h[N][N], c[N][N], n;
inline void up(int &x, int y){ x = x + y >= mod ? x + y - mod : x + y; }
inline int gao(vector<int> &A){
	if(!(int) A.size()) return 1;
	int m = A.size();
	for(int i = 0; i < m; i++)
		for(int j = i + 1; j < m; j++)
			c[i][j] = c[i][j-1] + (A[j] > A[i]);
	for(int i = 0; i < m; i++)
		for(int j = 0; j < m; j++) f[i][j] = 0;
	for(int i = 0; i < m; i++) f[i][i] = h[i][i] = 1;
	for(int i = m - 1; ~i; i--)
		for(int j = i + 1; j < m; j++){
			f[i][j] = h[i][j] = 1ll * f[i+1][j] * pw[c[i][j]] % mod;
			for(int k = i; k < j; k++) if(A[i] > A[k+1])
				up(f[i][j], 1ll * h[i][k] * f[k+1][j] % mod);
		}
	return f[0][m-1];
}
int main(){
	read(n), pw[0] = 1;
	for(int i = 1; i <= n; i++) read(a[i]);
	for(int i = 1; i <= n; i++) pw[i] = 2ll * pw[i-1] % mod;
	int ans = 1;
	for(int i = 1; i <= n; i++) if(!vis[i]){
		vector<int> A;
		vis[i] = 1;
		for(int p = a[i]; p != i; p = a[p])
			A.push_back(p), vis[p] = 1;
		ans = 1ll * ans * gao(A) % mod;	
	}
	cout << ans << endl;
}

