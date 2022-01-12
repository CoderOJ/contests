#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 200005;

int       n, q, d[N], f[N];
long long a[N], b[N], c[N], s[N];

std::multiset<long long> set[N], all;

void modify(int u, int sgn, int flag)
{
  int v = f[u];
  if (!set[v].empty())
  {
    if (flag || sgn < 0)
    {
      all.erase(all.find(*set[v].begin() + c[v]));
      all.erase(all.find(*set[v].rbegin() + c[v]));
    }
  }
  if (sgn == 1)
  {
    set[v].insert(b[u] + s[u]);
  }
  if (sgn == -1)
  {
    set[v].erase(set[v].find(b[u] + s[u]));
  }
  if (!set[v].empty())
  {
    if (flag || sgn > 0)
    {
      cm_assert(!set[v].empty());
      all.insert(*set[v].begin() + c[v]);
      all.insert(*set[v].rbegin() + c[v]);
    }
  }
}

int main()
{
  n = sc.next_int();
  q = sc.next_int();
  for (int u = 1; u <= n; u++)
  {
    a[u] = sc.next_long();
    d[u] = 1;
  }
  for (int u = 1; u <= n; u++)
  {
    f[u] = sc.next_int();
    d[f[u]]++;
  }

  for (int u = 1; u <= n; u++)
  {
    c[u] = a[u] / (d[u] + 1);
    b[u] = a[u] - c[u] * d[u];
    s[f[u]] += c[u];
  }
  for (int u = 1; u <= n; u++)
  {
    modify(u, 1, 1);
  }

  for (int i = 0; i < q; i++)
  {
    int opt = sc.next_int();
    if (opt == 1)
    {
      int u = sc.next_int();
      int v = sc.next_int();

      modify(u, -1, 0);
      modify(f[u], -1, 0);
      modify(f[f[u]], -1, 0);

      d[f[u]]--;
      s[f[u]] -= c[u];
      s[f[f[u]]] -= c[f[u]];
      c[f[u]] = a[f[u]] / (d[f[u]] + 1);
      b[f[u]] = a[f[u]] - c[f[u]] * d[f[u]];
      s[f[f[u]]] += c[f[u]];

      modify(u, 2, 0);
      modify(f[u], 1, 0);
      modify(f[f[u]], 1, 0);
      f[u] = v;

      modify(u, -2, 0);
      modify(f[u], -1, 0);
      modify(f[f[u]], -1, 0);
      d[f[u]]++;
      s[f[u]] += c[u];
      s[f[f[u]]] -= c[f[u]];
      c[f[u]] = a[f[u]] / (d[f[u]] + 1);
      b[f[u]] = a[f[u]] - c[f[u]] * d[f[u]];
      s[f[f[u]]] += c[f[u]];

      modify(u, 1, 0);
      modify(f[u], 1, 0);
      modify(f[f[u]], 1, 0);
    }
    else if (opt == 2)
    {
      int u = sc.next_int();
      printf("%lld\n", b[u] + c[f[u]] + s[u]);
    }
    else
    {
      printf("%lld %lld\n", *all.begin(), *all.rbegin());
    }
  }
  return 0;
}
