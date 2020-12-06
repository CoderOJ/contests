#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for (int i=0;i<n;++i)
#define repa(i,n) for (int i=1;i<=n;++i)
template <class T> inline bool checkMin(T& a, T b) { return a>b ? a=b,1 : 0; }
template <class T> inline bool checkMax(T& a, T b) { return a<b ? a=b,1 : 0; }

void file() {
#ifndef __LOCALE__
	freopen("walk.in", "r", stdin);
	freopen("walk.out", "w", stdout);
#endif
}

const int MOD = int(1e9) + 7;
const int N = 500005;
const int K = 12;
int w[K], mv_id[N], mv_de[N], n, k, max_w;

namespace sub1 {

const int AFF = 2000005;
bool if_inf = false;
int bs[K];
int dp[AFF];
inline int get(int mask, int id) { return (mask % bs[id+1]) / bs[id]; }
int dfs(int mask) {
	int ori_mask = mask;
	if (dp[mask] != -1) { return dp[mask]; }
	rep (i, n) {
		int pos = get(mask, mv_id[i]) + mv_de[i];
		if (pos < 0 || pos >= w[mv_id[i]]) { return dp[ori_mask]=i+1; }
		mask += bs[mv_id[i]] * mv_de[i]; }
	if (ori_mask == mask) { if_inf = true; return dp[ori_mask] = -1; }
	else { return dp[ori_mask] = (n + dfs(mask)) % MOD;; }
}

bool valid_mask(int mask) {
	rep (i,k) {
		int u = get(mask, i);
		if (u < 0 || u >= w[i]) { return false; } }
	return true;
}

void go () {
	int ans = 0;
	bs[0] = 1; repa (i,k) { bs[i] = bs[i-1] * max_w; }
	memset(dp, -1, sizeof(dp));
	rep (mask, bs[k]) {
		if (!valid_mask(mask)) { continue; } 
		(ans += dfs(mask)) %= MOD; }
	if (if_inf) { puts("-1"); }
	else { printf("%d\n", ans); }
}

} /* sub1 */ 

namespace sub2 {

const int N = 100005;
int le[N], ri[N], pos[N];
int ans[N];

void go() {
	pos[0] = 0;
	rep (i,n) {
		pos[i+1] = pos[i] + mv_de[i];
		le[i+1] = le[i]; checkMin(le[i+1], pos[i+1]);
		ri[i+1] = ri[i]; checkMax(ri[i+1], pos[i+1]); }
	int st=0, ed=max_w, de=1;
	if (pos[n] > 0) { st=max_w-1; ed=-1; de=-1; }
	for (int i=st; i!=ed; i+=de) {
		int l=0, r=n;
		while (l<r) {
			int mid = (l+r+1)/2;
			if (i + le[mid] >= 0 && i + ri[mid] < max_w) { l = mid; }
			else { r = mid-1; } }
		if (l == n) {
			if (pos[n] == 0) { puts("-1"); return; }
			else { ans[i] = (n + ans[i+pos[n]]) % MOD; } }
		else { ans[i] = l + 1; } 
	}
	int res = 0;
	rep (i,max_w) { 
		(res += ans[i]) %= MOD; }
	printf("%d\n", res);
}

} /* sub2 */

int main() {
	file();
	scanf("%d%d", &n, &k);
	rep (i,k) { scanf("%d", &w[i]); checkMax(max_w, w[i]); }
	rep (i,n) { scanf("%d%d", &mv_id[i], &mv_de[i]); mv_id[i]--; }
	if (k == 1) { sub2::go(); return 0; }
	sub1::go();
	return 0;
}
