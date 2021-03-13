#include <bits/stdc++.h>
#define setIO(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
#define closefile fclose(stdin), fclose(stdout)
#define m_p make_pair
#define sz(x) (int)x.size()
#define see(x) cerr << x << " "
#define seeln(x) cerr << x << endl
#define out(x) cerr << #x << " = " << x << " "
#define outln(x) cerr << #x << " = " << x << endl
#define outarr(x, l, r) {cerr<< #x"[" << l << " ~ " << r << "] = "; for (int _i = l; _i <= r; ++_i) cerr << x[_i] << " "; cerr << endl;}
using namespace std;

typedef long long ll;
typedef pair <int, int> pii;
#define gc() getchar()

char buf[1 << 21], *p1 = buf, *p2 = buf;
template <class T> void read(T &x) { x = 0; int c = gc(); int flag = 0; while (c < '0' || c > '9') flag |= (c == '-'), c = gc(); while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); if (flag) x = -x; }
template <class T> T _max(T a, T b) { return b < a ? a : b; }
template <class T> T _min(T a, T b) { return a < b ? a : b; }
template <class T> bool checkmax(T &a, T b) { return a < b ? a = b, 1 : 0; }
template <class T> bool checkmin(T &a, T b) { return b < a ? a = b, 1 : 0; }




const int N = 20005, inf = 0x3f3f3f3f;
int n, k, c, tote = 0;
int e = 0, first[N], nxt[N << 1], point[N << 1], value[N << 1];
void add_edge(int x, int y, int z) {
  nxt[++e] = first[x];
  first[x] = e;
  point[e] = y;
  value[e] = z; }

void init() {
  memset(first, -1, sizeof(int) * (n + 1));
  e = 0; tote = 0;
  for (int i = 1, u, v, w; i < n; ++i) {
    read(u); read(v); read(w);
    ++u; ++v; tote += w;
    add_edge(u, v, w);
    add_edge(v, u, w); } }

struct node {
  int tim; int used;
  node(int t = 0, int u = 0): tim(t), used(u) {}
  bool operator < (const node &rhs) const {
    return tim != rhs.tim ? tim < rhs.tim : used < rhs.used; }
  node operator + (const node &rhs) const {
    return node(tim + rhs.tim, used + rhs.used); }
  node operator - (const node &rhs) const {
    return node(tim - rhs.tim, used - rhs.used); } } up[N], fly[N];

void dfs(int x, int fa, int c) {
  fly[x] = node(c, 1);
  up[x] = node(0, 0);
  for (int i = first[x]; ~i; i = nxt[i]) {
    int to = point[i];
    if (to == fa) continue;
    dfs(to, x, c);
    node U = up[x] + up[to] + _min(node(value[i], 0), node(c, 1));
    node F = up[x] + up[to] + node(c, 1);
    checkmin(F, up[x] + fly[to]);
    checkmin(F, up[to] + fly[x] + node(value[i], 0));
    checkmin(F, fly[x] + fly[to]);
    checkmin(U, up[to] + fly[x]);
    checkmin(U, up[x] + fly[to]);
    checkmin(U, fly[x] + fly[to] - node(c, 1));
    up[x] = U; fly[x] = F; } }

bool check(int K) {
  dfs(1, 0, K);
  if (up[1].used <= k) return 1;
  else return 0; }

void solve() {
  dfs(1, 0, c);
  int ans = tote;
  int l = c, r = inf, mid, best = -1;
  while (l <= r) {
    mid = (l + r) >> 1;
    if (check(mid)) best = mid, r = mid - 1;
    else l = mid + 1; }
  dfs(1, 0, best);
  ans += up[1].tim;
  int delta = best - c;
  ans -= delta * k;
  printf("%d\n", ans); }

int main() {
  while (scanf("%d%d%d", &n, &k, &c) == 3) {
    init();
    solve(); }
  return 0; }
