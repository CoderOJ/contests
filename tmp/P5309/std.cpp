#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MOD 1000000007

//#define int long long

const int MAXN = 200005;

int block, L[MAXN], R[MAXN], num, n, m, a[MAXN], sum[MAXN], pre[500][500],
    suf[500][500];

/* num：块的个数
 * pre，suf 前缀后缀和
 * block：每块的大小
 * L[i]：i这块左端点的位置
 * R[i]：i这块右端点的位置 */

inline int blockpos(int i) {
  return (i - 1) / block + 1; }

inline void update(int x, int y, int z) {
  if (x >= block) { // 跳的长度大于块长，复杂度也是sqrt(n)
    for (int i = y; i <= n; i += x) {
      int cur = blockpos(i);
      a[i] += z;
      a[i] %= MOD;
      sum[cur] += z;
      sum[cur] %= MOD; }
    return; }
  for (int i = y; i <= x; ++i) {
    pre[x][i] += z;
    pre[x][i] %= MOD; }
  for (int i = 1; i <= y; ++i) {
    suf[x][i] += z;
    suf[x][i] %= MOD; } }

inline int block_sum(int l, int r) {
  int Ll = blockpos(l), Rr = blockpos(r), ans = 0;
  if (Ll == Rr) {
    for (int i = l; i <= r; ++i) {
      ans += a[i];
      ans %= MOD; }
    return ans; }
  for (int i = l; i <= R[Ll]; ++i) {
    ans += a[i];
    ans %= MOD; }
  for (int i = L[Rr]; i <= r; ++i) {
    ans += a[i];
    ans %= MOD; }
  for (int i = Ll + 1; i < Rr; ++i) {
    ans += sum[i];
    ans %= MOD; }
  return ans; }

inline int query_sum(int l, int r) {
  int bsum = block_sum(l, r);
  for (int i = 1; i < block; ++i) {
    int Ll = (l - 1) / i + 1, Rr = (r - 1) / i + 1;
    if (Ll == Rr) {
      bsum -= pre[i][(l - 1) % i];
      bsum += pre[i][(r - 1) % i + 1];
      bsum %= MOD; }
    else {
      bsum = (bsum + 1LL * (Rr - Ll - 1) * pre[i][i] + pre[i][(r - 1) % i + 1] +
          suf[i][(l - 1) % i + 1]) % MOD; } }
  return (bsum + MOD) % MOD; }

void solve() {
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i]; }
  block = sqrt(n);
  num = n / block; //求块的个数
  if (n % block) num++;
  for (int i = 1; i <= num; ++i) L[i] = R[i - 1] + 1, R[i] = i * block;
  R[num] = n;
  for (int i = 1; i <= num; ++i) {
    for (int j = L[i]; j <= R[i]; ++j) {
      sum[i] += a[j];
      sum[i] %= MOD; } }
  while (m--) {
    int op;
    cin >> op;
    if (op == 1) {
      int x, y, z;
      cin >> x >> y >> z;
      update(x, y, z);
      /*for (int i = 1; i <= n; ++i) {
          cout << a[i] << ' ';
      }
      cout << "\n";*/
    }
    if (op == 2) {
      int l, r;
      cin >> l >> r;
      cout << query_sum(l, r) << '\n'; } } }

int main() {
  solve();
  return 0; }
