#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cinttypes>
#include <map>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 500005, 105)

struct st_t
{
  int  f[N][18], n, k;
  void init(int n)
  {
    this->n = n;

    for (int i = 1; i <= n; i++)
      f[i][0] = sc.next_int();

    for (k = 1; 1 << k <= n; k++)
      for (int i = 1; i + (1 << k) - 1 <= n; i++)
        f[i][k] = std::max(f[i][k - 1], f[i + (1 << (k - 1))][k - 1]);
  }

  std::pair<int, int> find(int x, int y)
  {
    int l = x, r = x;

    for (int i = k - 1; i >= 0; i--)
      if (l - (1 << i) >= 1 && f[l - (1 << i)][i] <= y)
        l -= 1 << i;

    for (int i = k - 1; i >= 0; i--)
      if (r + (1 << i) <= n && f[r + 1][i] <= y)
        r += 1 << i;

    return {l, r};
  }
};

st_t a, b;

int n, m;

std::map<int, int64_t> f[2][N];

int64_t solve(int x, int y, int op)
{
  if (x == 0 || y == 0 || x > n || y > m)
    return -1;

  if (f[op][x].count(y))
    return f[op][x][y];

  int64_t &v = f[op][x][y];

  if (op == 0)
  {
    auto [l, r] = a.find(x, b.f[y][0]);
    l--;
    r++;
    v = std::max(solve(r, y, 1) + std::abs(x - r),
                 solve(l, y, 1) + std::abs(x - l));
  }
  else
  {
    auto [l, r] = b.find(y, a.f[x][0]);
    l--;
    r++;
    v = std::max(solve(x, r, 0) + std::abs(y - r),
                 solve(x, l, 0) + std::abs(y - l));
  }

  return v;
}

int main()
{
  n     = sc.next_int();
  m     = sc.next_int();
  int q = sc.next_int();

  a.init(n);
  b.init(m);

  for (int i = 1; i <= q; i++)
  {
    int x = sc.next_int();
    int y = sc.next_int();
    printf("%" SCNi64 "\n", std::max(solve(x, y, 0), solve(x, y, 1)));
  }

  return 0;
}
