#include <bits/stdc++.h>

#define rep(i,n) for (int i=0;i<n;++i)
#define repa(i,n) for (int i=1;i<=n;++i)
template <class T> inline bool checkMin(T& a, T b) { return a>b ? a=b,1 : 0; }
template <class T> inline bool checkMax(T& a, T b) { return a<b ? a=b,1 : 0; }

void file() {
#ifndef __LOCALE__
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
#endif
}

void solve();
int main() {
	int T; scanf("%d", &T);
	while (T--) { solve(); }
	return 0;
}

typedef long long i64;
const int N = 1048600;
char s[N]; int n;

const i64 MOD1 = 999222737;
const i64 MOD2 = 999911357;
const i64 BS1 = 31;
const i64 BS2 = 31;
i64 bs1[N], bs2[N], hs1[N], hs2[N];
void initHash() {
		bs1[0] = 1; bs2[0] = 1;
		repa (i,n) { 
			bs1[i] = bs1[i-1] * BS1 % MOD1; 
			bs2[i] = bs2[i-1] * BS2 % MOD2; } 
	repa (i,n) { 
		hs1[i] = (hs1[i-1] + bs1[i] * (s[i]-'a'+1)) % MOD1;
		hs2[i] = (hs2[i-1] + bs2[i] * (s[i]-'a'+1)) % MOD2; }
}
bool equal(int l1, int r1, int l2, int r2) {
	int delta = l2 - l1;
	return (hs1[r1] - hs1[l1-1] + MOD1) * bs1[delta] % MOD1 == (hs1[r2] - hs1[l2-1] + MOD1) % MOD1 &&
	       (hs2[r1] - hs2[l1-1] + MOD2) * bs2[delta] % MOD2 == (hs2[r2] - hs2[l2-1] + MOD2) % MOD2;
}

inline int popCnt(int u) {
	int res = 0;
	for (;u;u>>=1) { res += (u&1); }
	return res; }
int mask[N], pre[N][28];
void initMask() {
	mask[0] = 0;
	memset(pre[0], 0, sizeof(pre[0]));
	repa (i,n) {
		mask[i] = mask[i-1] ^ (1<<(s[i]-'a'));
		memcpy(pre[i], pre[i-1], sizeof(pre[i])); 
		for (int j=popCnt(mask[i]); j<=26; ++j) pre[i][j]++; } }
inline int backCnt(int l) { 
	return popCnt(mask[n] ^ mask[l]); }

void solve() {
	scanf("%s", s+1); n = strlen(s+1);
	initHash(); 
	initMask();
	i64 ans = 0;
	for (int l=2; l<n; ++l) {
		ans += pre[l-1][backCnt(l)];
//		printf("l=%d, backCnt(l)=%d\n", l, backCnt(l));
		for (int st=l+1; st+l-1<n; st+=l) {
			int ed = st + l - 1;
			if (!equal(1,l,st,ed)) { break; }
			ans += pre[l-1][backCnt(ed)]; } 
//		printf("finish l=%d, ans=%lld\n", l, ans);
	}
	printf("%lld\n", ans);
}
