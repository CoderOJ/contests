#include <bits/stdc++.h>

#define see(x) std::cout << #x << " = " << x << std::endl;

template <class T, typename = typename T::iterator>
std::ostream &operator<<(std::ostream &out, const T &v)
{
  out << "{";
  bool is_first = true;
  for (const auto &x : v)
  {
    if (!is_first) out << ", ";
    else is_first = false;
    out << x;
  }
  out << "}";
  return out;
}

const uint64_t HMOD = 181003010090299;
const int N = 505;

auto chmp = []{
  const uint64_t R = std::numeric_limits<uint64_t>::max() / HMOD - 10;

  std::mt19937_64 rng(std::random_device{}());
  std::array<std::array<uint64_t, 26>, N * 2> res;
  for (int i = 0; i < N * 2; i++)
    for (int j = 0; j < 26; j++)
      res[i][j] = rng() % R;

  return res;
}();

struct graph_t
{
  using us_t = std::vector<uint64_t>;

  std::vector<std::pair<int, int>> e[N];
  int n, m;

  void read()
  {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
    {
      int u, v;
      char c;
      scanf("%d%d %c", &u, &v, &c);
      u--, v--;
      e[u].emplace_back(v, c - 'a');
    }
  }

  uint64_t hash[N * 2][N];
  void build_hash(int d)
  {
    for (int i = 0; i < n; i++)
      hash[0][i] = 1;
    for (int i = 0; i + 1 < d; i++)
      for (int u = 0; u < n; u++)
        for (const auto &[v, c] : e[u])
          hash[i + 1][u] = (hash[i + 1][u] + chmp[i][c] * hash[i][v]) % HMOD;
  }

  us_t us_id() const
  {
    us_t us(n, 0);
    for (int i = 0; i < n; i++)
      us[i] = 1;
    return us;
  }

  us_t us_forward(const us_t &us, int ec) const
  {
    us_t vs(n, 0);
    for (int u = 0; u < n; u++)
      for (const auto &[v, c] : e[u])
        if (c == ec)
          vs[v] = (vs[v] + us[u]) % HMOD;
    return vs;
  }

  uint64_t us_hash(const us_t &us, int d) const
  {
    uint64_t res = 0;
    for (int i = 0; i < n; i++)
      res = (res + (__uint128_t)(us[i]) * hash[d][i]) % HMOD;
    return res;
  }
};

graph_t g0, g1;

int main()
{
  g0.read();
  g1.read();
  g0.build_hash(g0.n + g1.n + 2);
  g1.build_hash(g0.n + g1.n + 2);

  int d = []{
    auto id0 = g0.us_id();
    auto id1 = g1.us_id();
    for (int i = 0; i <= g0.n + g1.n; i++)
      if (g0.us_hash(id0, i) != g1.us_hash(id1, i))
        return i;
    return -1;
  }();

  if (d == -1)
  {
    puts("Same");
  }
  else
  {
    auto us0 = g0.us_id();
    auto us1 = g1.us_id();
    for (int i = 0; i < d; i++)
    {
      for (int c = 0; c < 26; c++)
      {
        auto vs0 = g0.us_forward(us0, c);
        auto vs1 = g1.us_forward(us1, c);
        if (g0.us_hash(vs0, d - i - 1) != g1.us_hash(vs1, d - i - 1))
        {
          putchar('a' + c);
          us0 = std::move(vs0);
          us1 = std::move(vs1);
          break;
        }
      }
    }
    puts("");
  }

  return 0;
}
