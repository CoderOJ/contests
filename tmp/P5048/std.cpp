#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#define Rint int
using namespace std;
template <typename T> inline void read(T &x) {
  x = 0; T w = 1, ch = getchar();
  while(!isdigit(ch) && ch != '-') ch = getchar();
  if(ch == '-') w = -1, ch = getchar();
  while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
  x *= w; }
template <typename T> inline void write_(T x) {
  if(x < 0) x = -x, putchar('-');
  if(x >= 10) write_(x / 10);
  putchar(x % 10 + '0'); }
const int maxn = 5e5 + 10;
const int siz = 708;
int ans = 0, sum[maxn], f[710][710], low[710], high[710], id[maxn], n, m,
    pos[maxn], a[maxn];
int cnt;
vector<int>s, val[maxn];
int main() {
  read(n); read(m);
  s.push_back(-1);
  for (Rint i = 1; i <= n; ++i) {
    read(a[i]);
    s.push_back(a[i]); }
  sort(s.begin(), s.end());
  s.erase(unique(s.begin(), s.end()), s.end());
  for (Rint i = 1; i <= n; ++i) {
    a[i] = lower_bound(s.begin(), s.end(), a[i]) - s.begin();
    val[a[i]].push_back(i);
    pos[i] = val[a[i]].size() - 1; }
  cnt = (n - 1) / siz + 1;
  for (Rint i = 1; i <= cnt; ++i) {
    low[i] = high[i - 1] + 1;
    high[i] = i * siz; }
  high[cnt] = n;
  for (Rint i = 1; i <= cnt; ++i) {
    memset(sum, 0, sizeof(sum));
    for (Rint j = low[i]; j <= high[i]; ++j) id[j] = i;
    for (Rint j = i; j <= cnt; ++j) {
      int&res = f[i][j];
      res = f[i][j - 1];
      for (Rint k = low[j]; k <= high[j]; ++k) {
        ++sum[a[k]];
        res = max(res, sum[a[k]]); } } }
  memset(sum, 0, sizeof(sum));
  while(m--) {
    int l, r;
    read(l); read(r);
    // l ^= ans; r ^= ans;
    ans = 0;
    if(id[l] == id[r]) {
      for (Rint i = l; i <= r; ++i) {
        ++sum[a[i]];
        ans = max(ans, sum[a[i]]); }
      for (Rint i = l; i <= r; ++i) sum[a[i]] = 0; }
    else {
      ans = f[id[l] + 1][id[r] - 1];
      for (Rint i = l; i <= high[id[l]]; ++i) {
        int res = pos[i];
        while((res + ans) < val[a[i]].size() && val[a[i]][res + ans] <= r) ++ans; }
      for (Rint i = low[id[r]]; i <= r; ++i) {
        int res = pos[i];
        while((res - ans) >= 0 && val[a[i]][res - ans] >= l) ++ans; } }
    write_(ans); putchar('\n'); }
  return 0; }
