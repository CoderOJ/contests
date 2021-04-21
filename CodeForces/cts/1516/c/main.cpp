#include <bits/stdc++.h>

constexpr int N = 105;
constexpr int M = 2005;
int a[N], n;

bool is_all_2() {
  for (int i = 0; i < n; ++i) if (a[i] % 2 == 1) {
      return false;
    }
  return true;
}

std::bitset<N *M> dp;
void make_dp() {
  dp[0] = 1;
  for (int i = 0; i < n; ++i)
    dp |= (dp << a[i]);
}

int main() {
  scanf ("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf ("%d", &a[i]);
  while (is_all_2() ) {
    for (int i = 0; i < n; ++i) a[i] /= 2;
  }
  int sum = std::accumulate (a, a + n, 0);
  if (sum % 2 == 1) {
    puts ("0");
    return 0;
  }
  make_dp();
  if (dp[sum / 2] == 0) {
    puts ("0");
    return 0;
  }
  for (int i = 0; i < n; ++i) if (a[i] % 2 == 1) {
      printf ("1\n%d\n", i + 1);
      return 0;
    }
  return 0;
}
