#include <bits/stdc++.h>

constexpr int N = 2005;
int a[N], pre[N], n;

void rmain() {
  scanf ("%d", &n);
  for (int i = 0; i < n; ++i) scanf ("%d", &a[i]);
  for (int i = 0; i < n; ++i) pre[i + 1] = pre[i] ^ a[i];
  for (int i = 1; i < n; ++i)
    if (pre[i] == (pre[n] ^ pre[i]) ) {
      puts ("YES");
      return;
    }
  for (int i = 1; i < n; ++i)
    for (int j = i + 1; j < n; ++j) {
      if (pre[i] == (pre[j] ^ pre[i]) && (pre[j] ^ pre[i]) == (pre[n] ^ pre[j]) ) {
        puts ("YES");
        return;
      }
    }
  puts ("NO");
}

int main() {
  int T;
  scanf ("%d", &T);
  while (T--) rmain();
  return 0;
}
