#include <bits/stdc++.h>

#define rep(i,n) for (int i=0;i<n;++i)
#define repa(i,n) for (int i=1;i<=n;++i)

constexpr int N = 5000005;
std::vector<int> prime;
int isPrime[N];
int fac[N];
long long pre[N];

void euler() {
  rep (i,N) isPrime[i] = 1;
  for (int i=2; i<N; ++i) {
    if (isPrime[i]) {
      prime.push_back(i); }
    for (int j: prime) {
      int u = i*j;
      if (u >= N) break;
      isPrime[u] = 0;
      if (i % j == 0) { break; } } } } 

void init() {
  euler();
  for (int p: prime) {
    for (long long q = p; q < N; q *= p) {
      for (int k=q; k<N; k += q) { fac[k]++; } } }
  repa (i,N-1) pre[i] = pre[i-1] + fac[i]; }

int main() {
  init();
  int T; scanf("%d", &T);
  while (T--) {
    int x,y; scanf("%d%d", &x, &y);
    printf("%lld\n", pre[x] - pre[y]); }
  return 0;
}
