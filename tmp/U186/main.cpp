#include <bits/stdc++.h>

int read_int()
{
  int c = getchar();
  while (!std::isdigit(c))
    c = getchar();
  int r = 0;
  while (std::isdigit(c))
  {
    r = r * 10 + (c - '0');
    c = getchar();
  }
  return r;
}

const int N = 1000005;
int a[N], ap[N], n, q;
char s[N];

struct dsu_t
{
  struct node_t
  {
    node_t *p = this;
    int size = 1;
    node_t() = default;
    node_t(node_t&) = delete;
    node_t(node_t&&) = delete;
    node_t operator=(node_t&) = delete;
    node_t operator=(node_t&&) = delete;

    node_t *get()
    {
      return p == this ? p : p = p->get();
    }
  };

  std::vector<node_t> p;
  dsu_t(int n) : p(n) {}

  void join(int u, int v)
  {
    // printf("join: %d %d\n", u, v);
    node_t *pu = p[u].get();
    node_t *pv = p[v].get();
    if (pu != pv)
    {
      pu->size += pv->size;
      pv->p = pu;
    }
  }
};

int main()
{
  n = read_int();
  for (int i = 0; i < n; i++)
  {
    a[i] = read_int() - 1;
    ap[a[i]] = i;
  }
  q = read_int();
  for (int i = 0; i < q; i++)
  {
    scanf("%s", s);

    dsu_t dsu(n);
    for (int i = 0; i < n; i++)
      if (s[i] == '0')
      {
        dsu.p[i].size = 0;
        if (i - 1 >= 0 && s[i - 1] == '0') 
          dsu.join(i - 1, i);
      }

    int ans = n;
    for (int i = n - 1; i >= 0; i--)
    {
      int p = ap[i];
      if (s[p] == '0')
      {
        int cur = ++dsu.p[p].get()->size;
        ans = std::min(ans, cur);
        // printf("%d: %d\n", i, cur);
      }
      else
      {
        if (p - 1 >= 0 && (s[p - 1] == '0' || a[p - 1] > i))
          dsu.join(p - 1, p);
        if (p + 1 < n && (s[p + 1] == '0' || a[p + 1] > i))
          dsu.join(p + 1, p);
      }
    }

    printf("%d\n", ans);
  }
  return 0;
}
