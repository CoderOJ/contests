#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 1005;
std::vector<std::pair<int, int> > row[N], col[N];
struct position { int x, y; } a[N];
int fa[N], bel[N], cx[N], cy[N];
int n, block_cnt;

inline int find(int x) {
  return x == fa[x] ? x : fa[x] = find(fa[x]); }
inline void merge(int x, int y) {
  int fx = find(x), fy = find(y);
  if(fx != fy) { --block_cnt; fa[fy] = fx; } }

inline bool CheckPoint(int x1, int y1, int x2, int y2, int lim) {
  if(x1 == x2 && std::abs(y1 - y2) <= 2ll * lim) return true;
  if(y1 == y2 && std::abs(x1 - x2) <= 2ll * lim) return true;
  if(std::abs(x1 - x2) <= lim && std::abs(y1 - y2) <= lim) return true;
  return false; }

inline bool check(long long lim) {
  block_cnt = n;
  for( int i = 1; i <= n; ++i) fa[i] = i;
  for( int i = 1; i <= n; ++i) {
    for( int j = i + 1; j <= n; ++j) {
      if(a[i].x == a[j].x && std::abs(a[i].y - a[j].y) <= lim) merge(i, j);
      if(a[i].y == a[j].y && std::abs(a[i].x - a[j].x) <= lim) merge(i, j); } }
  for( int i = 1; i <= n; ++i) bel[i] = find(i);

  if(block_cnt > 4) return false;
  else if(block_cnt == 1) return true;

  else if(block_cnt == 2) { 
    for( int i = 1; i <= n; ++i) {
      for( int j = i + 1; j <= n; ++j) {
        if(bel[i] == bel[j]) continue;
        if(CheckPoint(a[i].x, a[i].y, a[j].x, a[j].y, lim)) return true; } } }

  else if(block_cnt == 3) {
    for( int i = 1; i <= cx[0]; ++i) {
      long long curx = cx[i];
      for( int j = 1; j < (int)row[i].size(); ++j) {
        int index_L = row[i][j - 1].second, index_R = row[i][j].second;
        long long yL = row[i][j - 1].first, yR = row[i][j].first;
        if(bel[index_L] != bel[index_R] && yR - yL <= 2ll * lim) {
          for( int k = 1; k <= n; ++k) {
            if(bel[index_L] == bel[k] || bel[index_R] == bel[k]) continue;
            if(!(yR - lim <= a[k].y && a[k].y <= yL + lim)) continue;
            if(std::abs(a[k].x - curx) <= lim) return 1; } } } }
    for( int i = 1; i <= cy[0]; ++i) {
      long long cury = cy[i];
      for( int j = 1; j < (int)col[i].size(); ++j) {
        int index_L = col[i][j - 1].second, index_R = col[i][j].second;
        long long xL = col[i][j - 1].first, xR = col[i][j].first;
        if(bel[index_L] != bel[index_R] && xR - xL <= 2ll * lim) {
          for( int k = 1; k <= n; ++k) {
            if(bel[index_L] == bel[k] || bel[index_R] == bel[k]) continue;
            if(!(xR - lim <= a[k].x && a[k].x <= xL + lim)) continue;
            if(std::abs(a[k].y - cury) <= lim) return true; } } } } }

  else {
    for( int i = 1; i <= cx[0]; ++i) {
      long long curx = cx[i];
      for( int j = 1; j < (int)row[i].size(); ++j) {
        int index_L_1 = row[i][j - 1].second, index_R_1 = row[i][j].second;
        long long yL = row[i][j - 1].first, yR = row[i][j].first;
        if(bel[index_L_1] == bel[index_R_1]) continue;
        for( int k = 1; k <= cy[0]; ++k) {
          long long cury = cy[k];
          for( int l = 1; l < (int)col[k].size(); ++l) {
            int index_L_2 = col[k][l - 1].second, index_R_2 = col[k][l].second;
            long long xL = col[k][l - 1].first, xR = col[k][l].first;
            if(bel[index_L_2] == bel[index_R_2]) continue;
            if(bel[index_L_2] == bel[index_L_1] || bel[index_L_2] == bel[index_R_1]) continue;
            if(bel[index_R_2] == bel[index_L_1] || bel[index_R_2] == bel[index_R_1]) continue;
            if(!(xR - lim <= curx && curx <= xL + lim)) continue;
            if(!(yR - lim <= cury && cury <= yR + lim)) continue;
            if(std::abs(curx - xL) > lim || std::abs(curx - xR) > lim) continue;
            if(std::abs(cury - yL) > lim || std::abs(cury - yR) > lim) continue;
            return true; } } } } }

  return false; }

void preInit() {}
void init() {
  n = sc.n();
  for( int i = 1; i <= n; ++i) {
    a[i].x = sc.nextInt(); a[i].y = sc.nextInt();
    cx[++cx[0]] = a[i].x; cy[++cy[0]] = a[i].y; }
  std::sort(cx + 1, cx + 1 + cx[0]); std::sort(cy + 1, cy + 1 + cy[0]);
  cx[0] = std::unique(cx + 1, cx + 1 + cx[0]) - cx - 1;
  cy[0] = std::unique(cy + 1, cy + 1 + cy[0]) - cy - 1; }

void solve() {
  for( int i = 1; i <= n; ++i) {
    int curx = std::lower_bound(cx + 1, cx + 1 + cx[0], a[i].x) - cx,
        cury = std::lower_bound(cy + 1, cy + 1 + cy[0], a[i].y) - cy;
    row[curx].push_back(std::make_pair(a[i].y, i));
    col[cury].push_back(std::make_pair(a[i].x, i)); }
  for( int i = 1; i <= cx[0]; ++i) std::sort(row[i].begin(), row[i].end());
  for( int i = 1; i <= cy[0]; ++i) std::sort(col[i].begin(), col[i].end());

  int l = 0, r = std::numeric_limits<int>::max();
  while(l < r) {
    int mid = ((long long)l + r) >> 1;
    if(check(mid)) r = mid;
    else l = mid + 1; }
  printf("%d\n", l == std::numeric_limits<int>::max() ? -1 : l); }
