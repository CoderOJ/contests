#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

#define int long long
const int inf = 0x3f3f3f3f3f3f3f3f;
const int N = 50000, M = 50000;
int k, mod, n, s[N], m;
std::pair<int, int> v[M + 1];
std::vector<std::pair<int, std::pair<bool, int>>> v0;

struct matrix_t
{
  int a[2][2];
  const int *operator[](int x) const
  {
    return a[x];
  }
  int *operator[](int x)
  {
    return a[x];
  }
  matrix_t(int x = 0, int y = 0, int z = 0, int xx = 0)
  {
    a[0][0] = x, a[0][1] = y, a[1][0] = z, a[1][1] = xx;
  }
  friend matrix_t operator*(const matrix_t &lhs, const matrix_t &rhs)
  {
    return matrix_t{(lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0]) % mod,
                    (lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1]) % mod,
                    (lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0]) % mod,
                    (lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1]) % mod};
  }
};

matrix_t pow(matrix_t x, int y)
{
  matrix_t res(1, 0, 0, 1);
  while (y)
  {
    if (y & 1)
      res = res * x;
    x = x * x;
    y >>= 1;
  }
  return res;
}

struct sgt_t
{
  struct node_t
  {
    signed l, r;
    matrix_t v;
  };

  node_t p[N * 4];

  void push_up(int pos)
  {
    p[pos].v = p[pos * 2].v * p[pos * 2 + 1].v;
  }

  void build(signed l = 0, signed r = (signed)(n - 1), int pos = 1)
  {
    p[pos].l = l;
    p[pos].r = r;
    if (l == r)
    {
      p[pos].v = matrix_t(0, s[l], 1, s[(l + 1) % n]);
      return;
    }
    signed mid = (l + r) / 2;
    build(l, mid, pos * 2);
    build(mid + 1, r, pos * 2 + 1);
    push_up(pos);
  }

  void modify(int x, bool y, int v, int pos = 1)
  {
    if (p[pos].l == p[pos].r)
    {
      p[pos].v[y][1] = v;
      return;
    }
    signed mid = (p[pos].l + p[pos].r) / 2;
    modify(x, y, v, pos * 2 + (x > mid));
    push_up(pos);
  }
  matrix_t prod(int l = 0, int r = n - 1, int pos = 1)
  {
    if (l > r)
      return matrix_t(1, 0, 0, 1);
    if (l <= p[pos].l && r >= p[pos].r)
      return p[pos].v;
    signed mid = (p[pos].l + p[pos].r) / 2;
    matrix_t res(1, 0, 0, 1);
    if (l <= mid)
      res = prod(l, r, pos * 2);
    if (r > mid)
      res = res * prod(l, r, pos * 2 + 1);
    return res;
  }
} sgt;

signed main()
{
  k = sc.next_long();
  mod = sc.next_long();
  n = sc.next_long();
  for (int i = 0; i < n; i++)
    s[i] = sc.next_long();
  m = sc.next_long();
  for (int i = 1; i <= m; i++)
  {
    v[i].first = sc.next_long();
    v[i].second = sc.next_long();
  }

  v0.push_back(std::make_pair(-n, std::make_pair(0, 0)));
  v0.push_back(std::make_pair(inf, std::make_pair(0, 0)));
  for (int i = 1; i <= m; i++)
  {
    v0.push_back(std::make_pair(v[i].first, std::make_pair(0, v[i].second)));
    if (v[i].first)
      v0.push_back(
          std::make_pair(v[i].first - 1, std::make_pair(1, v[i].second)));
  }

  std::sort(v0.begin(), v0.end());
  sgt.build();
  matrix_t res(1, 0, 0, 1);
  int las = 0;
  for (size_t i = 1, ie; i < v0.size(); i = ie)
  {
    ie = i;
    while (ie < v0.size() && v0[ie].first / n == v0[i].first / n)
      ie++;
    if (v0[i].first / n >= k / n)
    {
      las = v0[i - 1].first / n;
      break;
    }
    res = res * pow(sgt.prod(), v0[i].first / n - 1 - v0[i - 1].first / n);
    for (size_t j = i; j < ie; j++)
      sgt.modify(v0[j].first % n, v0[j].second.first, v0[j].second.second);
    res = res * sgt.prod();
    for (size_t j = i; j < ie; j++)
      sgt.modify(v0[j].first % n, v0[j].second.first,
                 v0[j].second.first ? s[(v0[j].first + 1) % n]
                                    : s[v0[j].first % n]);
  }

  res = res * pow(sgt.prod(), k / n - 1 - las);
  for (size_t i = 0; i < v0.size(); i++)
    if (v0[i].first / n == k / n)
      sgt.modify(v0[i].first % n, v0[i].second.first, v0[i].second.second);
  res = res * sgt.prod(0, k % n - 1);
  std::cout << res[1][0] << std::endl;

  return 0;
}
