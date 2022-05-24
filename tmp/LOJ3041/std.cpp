#include "minerals.h"
#include <bits/stdc++.h>

const int N = 43005;
const double p = (3 - std::sqrt(5)) / 2;
int A[N], B[N], T[N];

inline int Ask(int x) {
  static int Pre = 0;
  int Now = Query(x), Res = Pre != Now;
  return Pre = Now, Res;
}

void Divide(int l, int r, int o) {
  if (l == r)
    return;

  int Le = r - l + 1, Mid = l + std::max(int(p * Le) - 1, 0);

  for (int i = l; i <= Mid; ++i)
    Ask(A[i]);

  int C = l - 1, D = Mid;

  for (int i = l; i <= r; ++i)
    if (C == Mid)
      T[++D] = B[i];
    else if (D == r)
      T[++C] = B[i];
    else if (o ^ Ask(B[i]))
      T[++D] = B[i];
    else
      T[++C] = B[i];

  for (int i = l; i <= r; ++i)
    B[i] = T[i];

  Divide(l, Mid, o ^ 1), Divide(Mid + 1, r, o);
}

void Solve(int n) {
  int C = 0, D = 0;

  for (int i = 1; i <= 2 * n; ++i)
    (Ask(i) ? A[++C] : B[++D]) = i;

  Divide(1, n, 1);

  for (int i = 1; i <= n; ++i)
    Answer(A[i], B[i]);
}