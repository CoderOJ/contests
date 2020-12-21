#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"

#include <bits/stdc++.h>

constexpr int N = 200005;
struct Path { int kd, pos, len, l; } a[N];

int n, q, col[N*2], c, dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1}, tot, sum[N], c2[N*2];
char s[3][N];
auto id = [](int x, int y) -> int { return (x - 1) * n + y; };
auto pos = [](int x) -> std::pair<int, int> { return {(x - 1) / n + 1, (x - 1) % n + 1}; };

void Bfs(int u) {
  std::queue<int> q;
  col[u] = c;
  q.emplace(u);
  while (!q.empty()) {
    int tmp = q.front(), x = pos(tmp).first, y = pos(tmp).second; q.pop();
    for (int i = 0; i < 4; i++) {
      int tx = x + dx[i], ty = y + dy[i];
      if (tx >= 1 && tx <= 2 && ty >= 1 && ty <= n && s[tx][ty] == '0' && !col[id(tx, ty)]) {
        col[id(tx, ty)] = c; q.emplace(id(tx, ty)); } } } }

int main(int argc, char const *argv[]) {
  scanf("%d%d%s%s", &n,&q,s[1]+1, s[2]+1);
  for (int i = 1; i <= 2; i++) {
    for (int j = 1; j <= n; j++) {
      if (s[i][j] == '0' && !col[id(i, j)]) {
        c++; Bfs(id(i, j)); } } }
  for (int i = 1; i <= n; i++) {
    if (s[1][i] == '0' && s[2][i] == '0') { 
      if (a[tot].kd == 2) { a[tot].len++; }
      else { tot++; a[tot].kd = 2; a[tot].len = 1; a[tot].l = i; }
      c2[i] = c2[i + n] = tot; }
    else if (s[1][i] == '0') {
      if (a[tot].kd == 1 && a[tot].pos == 1) { a[tot].len++; }
      else { tot++; a[tot].kd = a[tot].len = a[tot].pos = 1; a[tot].l = i; }
      c2[i] = tot; }
    else if (s[2][i] == '0') {
      if (a[tot].kd == 1 && a[tot].pos == 2) { a[tot].len++; }
      else { tot++; a[tot].kd = a[tot].len = 1; a[tot].pos = 2; a[tot].l = i; }
      c2[i + n] = tot; }
    else { tot++; } }
  for (int i = 1; i <= tot; i++) {
      sum[i] = sum[i - 1] + a[i].len;
      if (a[i].kd == 2) { sum[i] += a[i - 1].pos != a[i + 1].pos; } }
  while (q--) {
    int u, v; scanf("%d%d", &u,&v); std::pair<int, int> x = pos(u), y = pos(v);
    if (col[u] != col[v] || s[x.first][x.second] == '1' || s[y.first][y.second] == '1') { std::cout << "You have been confusional!\n"; continue; }
    if (c2[u] == c2[v]) { std::cout << abs(x.first - y.first) + abs(x.second - y.second) << '\n'; continue; }
    int ux = x.first, uy = x.second, vx = y.first, vy = y.second, ans = 0;
    if (uy > vy) { std::swap(u, v); std::swap(ux, vx); std::swap(uy, vy); }
    ans += a[c2[u]].len + a[c2[u]].l - uy - 1;
    if (a[c2[u]].kd == 2) { ans += ux != a[c2[u] + 1].pos; }
    ans += vy - a[c2[v]].l + 1;
    if (a[c2[v]].kd == 2) { ans += vx != a[c2[v] - 1].pos; }
    std::cout << ans + sum[c2[v] - 1] - sum[c2[u]] << '\n'; }
  return 0;
}
