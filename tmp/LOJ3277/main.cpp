#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstdint>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 200005, 205)

int n, m;

std::vector<int>                 h[N];
std::vector<std::pair<int, int>> s[N];

struct dsu_t
{
  int p[N];
  int get(int x)
  {
    return p[x] == x ? x : p[x] = get(p[x]);
  }
};

dsu_t dl, dr;

int64_t t[N];
int64_t ans;

void modify(int x, int64_t v)
{
  for (; x < N; x += x & -x)
    t[x] += v;
}

int64_t query(int x, int64_t s = 0)
{
  for (; x; x ^= x & -x)
    s += t[x];
  return s;
}

int main()
{
  n = sc.next_int();

  for (int i = 1; i <= n + 1; ++i)
  {
    dl.p[i] = i;
    dr.p[i] = i;
  }

  for (int i = 1; i <= n; ++i)
    h[sc.next_int()].push_back(i);

  m = sc.next_int();
  for (int i = 0; i < m; i++)
  {
    int x = sc.next_int();
    int y = sc.next_int();
    int c = sc.next_int();
    s[y].emplace_back(x, c);
  }

  for (int i = 1; i <= n; ++i)
  {
    for (auto p : s[i])
    {
      int64_t v = query(p.first);
      if (p.second <= v)
        ans += p.second;
      else
      {
        ans += v;
        modify(dl.get(p.first) + 1, p.second - v);
        modify(dr.get(p.first), v - p.second);
      }
    }
    for (int p : h[i])
    {
      dl.p[p] = p - 1;
      dr.p[p] = p + 1;
    }
  }

  std::cout << ans << std::endl;

  return 0;
}
