#include <bits/stdc++.h>

constexpr int MOD = 998244353;

int main() {

  constexpr int BLOCK = 
#include "./block.hpp"
  ;

  int *inv = new int[MOD];

  inv[1] = 1;
  int sum = 1;
  for (int i=2; i<MOD; ++i) {
    inv[i] = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
    sum = (sum + inv[i]) % MOD;
    if (i % BLOCK == 0) printf("%d,\n", sum); }
  return 0;
}
