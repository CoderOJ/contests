#include <iostream>
#include <cstdio>
#include <vector>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(u) for(int i=hd[u],v;v=e[i].v,i;i=e[i].n)
#define gc cl==cr && (cr=(cl=bu)+fread(bu,1,100000,stdin),cl==cr)?EOF:*cl++
using namespace std;
const int B = 21, N = 600600;
int n, x, L, I, fl;
int hd[N], a[N], d[N], s[N];
bool b[B + 1][N << 2];
char bu[N], *cl, *cr;
long long ans;
struct edge {
  int n, v; } e[N];
void add(int u, int v) {
  e[++fl] = (edge) {
    hd[u], v };
  hd[u] = fl; }
int read() {
  char ch = gc; int x = 0;
  for(; ch < '0' || '9' < ch; ch = gc);
  for(; '0' <= ch && ch <= '9'; ch = gc) x = x * 10 + (ch ^ 48);
  return x; }
void dfs(int u) {
  FOR(i, 0, B) b[i][(a[u] + d[u]) & ((1 << i) - 1)] ^= 1;
  FOR(i, 0, B) a[u] ^= b[i][d[u] & ((1 << i) - 1)] << i;
  REP(u) d[v] = d[u] + 1, dfs(v), a[u] ^= a[v];
  FOR(i, 0, B) a[u] ^= b[i][d[u] & ((1 << i) - 1)] << i;
  ans += a[u]; }
int main() {
  n = read();
  FOR(i, 1, n) a[i] = read();
  FOR(i, 2, n) x = read(), add(x, i);
  dfs(1);
  cout << ans << '\n'; }
