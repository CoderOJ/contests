#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 300005;

struct node_t
{
  int min = 0;
  int cnt = 1;
  int add = 0;  

  void push_add(int del)
  {
    add += del;
    min += del;
  }

  void push_up(const node_t &l, const node_t &r)
  {
    if (l.min < r.min) min = l.min, cnt = l.cnt;
    else if (l.min > r.min) min = r.min, cnt = r.cnt;
    else min = l.min, cnt = l.cnt + r.cnt;
  }

  void push_down(node_t &l, node_t &r)
  {
    l.push_add(add);
    r.push_add(add);
    add = 0;
  }
} p[N * 4];

int gl, gr;

void sgt_modify(int u, int l, int r, int ml, int mr, int del)
{
  if (ml <= l && r <= mr) { p[u].push_add(del); return; }
  p[u].push_down(p[u + u], p[u + u + 1]);
  int mid = (l + r) / 2;
  if (ml < mid) sgt_modify(u + u, l, mid, ml, mr, del);
  if (mr > mid) sgt_modify(u + u + 1, mid, r, ml, mr, del);
  p[u].push_up(p[u + u], p[u + u + 1]);
}

node_t sgt_query(int u, int l, int r, int ql, int qr)
{
  if (ql <= l && r <= qr) return p[u];
  p[u].push_down(p[u + u], p[u + u + 1]);
  int mid = (l + r) / 2;
  if (qr <= mid) return sgt_query(u + u, l, mid, ql, qr);
  if (ql >= mid) return sgt_query(u + u + 1, mid, r, ql, qr);
  auto al = sgt_query(u + u, l, mid, ql, qr);
  auto ar = sgt_query(u + u + 1, mid, r, ql, qr);
  node_t res; res.push_up(al, ar);
  return res;
}

int x2y[N], y2x[N], n;

int main()
{
  n = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    int x = sc.next_int() - 1;
    int y = sc.next_int() - 1;
    x2y[x] = y, y2x[y] = x;
  }
  gl = 0, gr = n;

  long long ans = 0;
  for (int i = 0; i < n; i++)
  {
    sgt_modify(1, gl, gr, gl, i + 1, 1);
    if (x2y[i] > 0 && y2x[x2y[i] - 1] < i) 
      sgt_modify(1, gl, gr, gl, y2x[x2y[i] - 1] + 1, -1);
    if (x2y[i] + 1 < n && y2x[x2y[i] + 1] < i) 
      sgt_modify(1, gl, gr, gl, y2x[x2y[i] + 1] + 1, -1);
    auto res = sgt_query(1, gl, gr, gl, i + 1);
    ans += res.cnt;
  }

  std::cout << ans << std::endl;
  return 0;
}

