#include <bits/stdc++.h>
using namespace std;

const int P = 1000000000 + 7, inv[4] = {0, 1, 500000004, 333333336};
int n, K, H, cnode, rt, pw[31], ch[3000003][2], sz[3000003];
int C(int x, int y)
{
  int res = 1;
  for (int i = 1; i <= y; ++i)
    res = 1ll * res * (x - i + 1) % P * inv[i] % P;
  return res;
}
void insert(int &k, int l, int r, int L, int R)
{
  if (!k)
    k = ++cnode;
  sz[k] += min(r, R) - max(l, L) + 1;
  if (L <= l && r <= R)
    return;
  int mid = (l + r) >> 1;
  if (L <= mid)
    insert(ch[k][0], l, mid, L, R);
  if (R > mid)
    insert(ch[k][1], mid + 1, r, L, R);
}

int solve(int x, int y, int d, int cnt)
{
  if (!x)
    return 0;
  if (!ch[x][0] && !ch[y][0] && !ch[x][1] && !ch[y][1])
    return 1ll * pw[d + 1] % P * C(cnt + (y ? (1 + (K & (pw[d + 1] - 1))) : 0), 2) % P;
  if (!ch[x][0] && !ch[x][1])
    sz[ch[x][0] = ++cnode] = sz[ch[x][1] = ++cnode] = pw[d];
  if (y && !ch[y][0] && !ch[y][1])
    sz[ch[y][0] = ++cnode] = sz[ch[y][1] = ++cnode] = pw[d];
  if (K >> d & 1)
    return (solve(ch[x][0], ch[y][1], d - 1, (cnt + sz[ch[y][0]]) % P) +
            solve(ch[x][1], ch[y][0], d - 1, (cnt + sz[ch[y][1]]) % P)) %
           P;
  return (solve(ch[x][0], ch[y][0], d - 1, cnt) + solve(ch[x][1], ch[y][1], d - 1, cnt)) % P;
}

int calc(int k, int d)
{
  if (!k)
    return 0;
  if (!ch[k][0] && !ch[k][1])
    return 1ll * pw[d - H + 1] % P * (C(pw[H], 3) + 1ll * pw[H] * C(K - (1 << H) + 1, 2) % P) % P;
  if (d > H)
    return (calc(ch[k][0], d - 1) + calc(ch[k][1], d - 1)) % P;
  return (1ll * C(sz[ch[k][0]], 3) + C(sz[ch[k][1]], 3) + solve(ch[k][0], ch[k][1], d - 1, 0) +
          solve(ch[k][1], ch[k][0], d - 1, 0)) %
         P;
}

int main()
{
  cin >> n >> K;
  for (int i = 1; i <= n; ++i)
  {
    int l, r;
    cin >> l >> r;
    insert(rt, 0, (1ll << 31) - 1, l, r);
  }
  H = 31 - __builtin_clz(K);
  for (int i = pw[0] = 1; i <= 30; ++i)
    pw[i] = 2 * pw[i - 1];
  cout << calc(1, 30);
  return 0;
}
